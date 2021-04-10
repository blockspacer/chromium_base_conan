/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <basic/test/deterministic_schedule.h>

#include "build/build_config.h"

#include <algorithm>
#include <list>
#include <mutex>
#include <random>
#include <unordered_map>
#include <utility>

#include "base/run_loop.h"
#include "base/threading/platform_thread.h"
#include "base/threading/thread_local.h"
#include "base/no_destructor.h"
#include "base/rand_util.h"
#include "base/check_op.h"
#include "base/memory/ptr_util.h"

#include <basic/random/random.h>

namespace basic {
namespace test {

DSchedThreadWrapper::DSchedThreadWrapper(base::OnceClosure to_run)
  : thread_id_(base::kInvalidThreadId),
    to_run_(std::move(to_run)) {
  CHECK(base::PlatformThread::Create(0, this, &thread_handle_));
}

DSchedThreadWrapper::~DSchedThreadWrapper() = default;

void DSchedThreadWrapper::ThreadMain() {
  thread_id_ = base::PlatformThread::CurrentId();
  CHECK_NE(thread_id_, base::kInvalidThreadId);

  // Make sure that the thread ID is the same across calls.
  CHECK_EQ(thread_id_, base::PlatformThread::CurrentId());

  event.Signal();

  std::move(to_run_).Run();
}

using Sem = DeterministicSchedule::Sem;

AuxChk DeterministicSchedule::aux_chk;

// access is protected by futexLock
static std::unordered_map<
    const detail::Futex<DeterministicAtomic>*,
    std::list<std::pair<uint32_t, bool*>>>
    futexQueues;

static std::mutex futexLock;

void ThreadTimestamps::sync(const ThreadTimestamps& src) {
  if (src.timestamps_.size() > timestamps_.size()) {
    timestamps_.resize(src.timestamps_.size());
  }
  for (size_t i = 0; i < src.timestamps_.size(); i++) {
    timestamps_[i].sync(src.timestamps_[i]);
  }
}

DSchedTimestamp ThreadTimestamps::advance(DSchedThreadId tid) {
  DCHECK(timestamps_.size() > tid.val);
  return timestamps_[tid.val].advance();
}

void ThreadTimestamps::setIfNotPresent(DSchedThreadId tid, DSchedTimestamp ts) {
  DCHECK(ts.initialized());
  if (tid.val >= timestamps_.size()) {
    timestamps_.resize(tid.val + 1);
  }
  if (!timestamps_[tid.val].initialized()) {
    timestamps_[tid.val].sync(ts);
  }
}

void ThreadTimestamps::clear() {
  timestamps_.clear();
}

bool ThreadTimestamps::atLeastAsRecentAs(DSchedThreadId tid, DSchedTimestamp ts)
    const {
  // It is not meaningful learn whether any instance is at least
  // as recent as timestamp 0.
  DCHECK(ts.initialized());
  if (tid.val >= timestamps_.size()) {
    return false;
  }
  return timestamps_[tid.val].atLeastAsRecentAs(ts);
}

bool ThreadTimestamps::atLeastAsRecentAsAny(const ThreadTimestamps& src) const {
  size_t min = timestamps_.size() < src.timestamps_.size()
      ? timestamps_.size()
      : src.timestamps_.size();
  for (size_t i = 0; i < min; i++) {
    if (src.timestamps_[i].initialized() &&
        timestamps_[i].atLeastAsRecentAs(src.timestamps_[i])) {
      return true;
    }
  }
  return false;
}

void ThreadSyncVar::acquire() {
  ThreadInfo& threadInfo = DeterministicSchedule::getCurrentThreadInfo();
  DSchedThreadId tid = DeterministicSchedule::getThreadId();
  threadInfo.acqRelOrder_.advance(tid);
  threadInfo.acqRelOrder_.sync(order_);
}

void ThreadSyncVar::release() {
  ThreadInfo& threadInfo = DeterministicSchedule::getCurrentThreadInfo();
  DSchedThreadId tid = DeterministicSchedule::getThreadId();
  threadInfo.acqRelOrder_.advance(tid);
  order_.sync(threadInfo.acqRelOrder_);
}

void ThreadSyncVar::acq_rel() {
  ThreadInfo& threadInfo = DeterministicSchedule::getCurrentThreadInfo();
  DSchedThreadId tid = DeterministicSchedule::getThreadId();
  threadInfo.acqRelOrder_.advance(tid);
  threadInfo.acqRelOrder_.sync(order_);
  order_.sync(threadInfo.acqRelOrder_);
}

struct PerThreadState {
  // delete the constructors and assignment operators for sanity
  //
  // but... we can't delete the move constructor and assignment operators
  // because those are required before C++17 in the implementation of
  // SingletonThreadLocal
  PerThreadState(const PerThreadState&) = delete;
  PerThreadState& operator=(const PerThreadState&) = delete;
  PerThreadState(PerThreadState&&) = default;
  PerThreadState& operator=(PerThreadState&&) = default;
  PerThreadState() = default;

  Sem* sem{nullptr};
  DeterministicSchedule* sched{nullptr};
  bool exiting{false};
  DSchedThreadId threadId{};
  AuxAct aux_act{};
};

static PerThreadState* GetTLSForPerThreadState() {
  static base::NoDestructor<base::ThreadLocalOwnedPointer<PerThreadState>> instance;
  if (!instance->Get())
    instance->Set(base::WrapUnique(new PerThreadState));
  return instance->Get();
}

DeterministicSchedule::DeterministicSchedule(
    std::function<size_t(size_t)> scheduler)
    : scheduler_(std::move(scheduler)), nextThreadId_(0), step_(0) {
  DCHECK(GetTLSForPerThreadState());
  auto& tls = *GetTLSForPerThreadState();
  DCHECK(tls.sem == nullptr);
  DCHECK(tls.sched == nullptr);
  DCHECK(tls.aux_act == nullptr);

  tls.exiting = false;
  tls.sem = new Sem(true);
  sems_.push_back(tls.sem);

  tls.threadId = nextThreadId_++;
  threadInfoMap_.emplace_back(tls.threadId);
  tls.sched = this;
}

DeterministicSchedule::~DeterministicSchedule() {
  auto& tls = *GetTLSForPerThreadState();
  static_cast<void>(tls);
  DCHECK(tls.sched == this);
  DCHECK(sems_.size() == 1);
  DCHECK(sems_[0] == tls.sem);
  delete tls.sem;
  tls = PerThreadState();
}

std::function<size_t(size_t)> DeterministicSchedule::uniform(uint64_t seed) {
  auto rand = std::make_shared<std::ranlux48>(seed);
  return [rand](size_t numActive) {
    auto dist = std::uniform_int_distribution<size_t>(0, numActive - 1);
    return dist(*rand);
  };
}

struct UniformSubset {
  UniformSubset(uint64_t seed, size_t subsetSize, size_t stepsBetweenSelect)
      : uniform_(DeterministicSchedule::uniform(seed)),
        subsetSize_(subsetSize),
        stepsBetweenSelect_(stepsBetweenSelect),
        stepsLeft_(0) {}

  size_t operator()(size_t numActive) {
    adjustPermSize(numActive);
    if (stepsLeft_-- == 0) {
      stepsLeft_ = stepsBetweenSelect_ - 1;
      shufflePrefix();
    }
    return perm_[uniform_(std::min(numActive, subsetSize_))];
  }

 private:
  std::function<size_t(size_t)> uniform_;
  const size_t subsetSize_;
  const size_t stepsBetweenSelect_;

  size_t stepsLeft_;
  // only the first subsetSize_ is properly randomized
  std::vector<size_t> perm_;

  void adjustPermSize(size_t numActive) {
    if (perm_.size() > numActive) {
      perm_.erase(
          std::remove_if(
              perm_.begin(),
              perm_.end(),
              [=](size_t x) { return x >= numActive; }),
          perm_.end());
    } else {
      while (perm_.size() < numActive) {
        perm_.push_back(perm_.size());
      }
    }
    DCHECK(perm_.size() == numActive);
  }

  void shufflePrefix() {
    for (size_t i = 0; i < std::min(perm_.size() - 1, subsetSize_); ++i) {
      size_t j = uniform_(perm_.size() - i) + i;
      std::swap(perm_[i], perm_[j]);
    }
  }
};

bool DeterministicSchedule::isCurrentThreadExiting() {
  auto& tls = *GetTLSForPerThreadState();
  return tls.exiting;
}

bool DeterministicSchedule::isActive() {
  auto& tls = *GetTLSForPerThreadState();
  return tls.sched != nullptr;
}

DSchedThreadId DeterministicSchedule::getThreadId() {
  auto& tls = *GetTLSForPerThreadState();
  DCHECK(tls.sched != nullptr);
  return tls.threadId;
}

DeterministicSchedule* DeterministicSchedule::getCurrentSchedule() {
  DCHECK(GetTLSForPerThreadState());
  auto& tls = *GetTLSForPerThreadState();
  return tls.sched;
}

std::function<size_t(size_t)>
DeterministicSchedule::uniformSubset(uint64_t seed, size_t n, size_t m) {
  auto gen = std::make_shared<UniformSubset>(seed, n, m);
  return [=](size_t numActive) { return (*gen)(numActive); };
}

void DeterministicSchedule::beforeSharedAccess() {
  auto& tls = *GetTLSForPerThreadState();
  if (tls.sem) {
    tls.sem->wait();
  }
}

void DeterministicSchedule::afterSharedAccess() {
  auto& tls = *GetTLSForPerThreadState();
  auto sched = tls.sched;
  if (!sched) {
    return;
  }
  sched->sems_[sched->scheduler_(sched->sems_.size())]->post();
}

void DeterministicSchedule::afterSharedAccess(bool success) {
  auto& tls = *GetTLSForPerThreadState();
  auto sched = tls.sched;
  if (!sched) {
    return;
  }
  sched->callAux(success);
  sched->sems_[sched->scheduler_(sched->sems_.size())]->post();
}

size_t DeterministicSchedule::getRandNumber(size_t n) {
  auto& tls = *GetTLSForPerThreadState();
  if (tls.sched) {
    return tls.sched->scheduler_(n);
  }
  return base::RandomValue() % n;
}

int DeterministicSchedule::getcpu(
    unsigned* cpu,
    unsigned* node,
    void* /* unused */) {
  auto& tls = *GetTLSForPerThreadState();
  if (cpu) {
    *cpu = tls.threadId.val;
  }
  if (node) {
    *node = tls.threadId.val;
  }
  return 0;
}

void DeterministicSchedule::setAuxAct(AuxAct& aux) {
  auto& tls = *GetTLSForPerThreadState();
  tls.aux_act = aux;
}

void DeterministicSchedule::setAuxChk(AuxChk& aux) {
  aux_chk = aux;
}

void DeterministicSchedule::clearAuxChk() {
  aux_chk = nullptr;
}

void DeterministicSchedule::reschedule(Sem* sem) {
  auto& tls = *GetTLSForPerThreadState();
  auto sched = tls.sched;
  if (sched) {
    sched->sems_.push_back(sem);
  }
}

Sem* DeterministicSchedule::descheduleCurrentThread() {
  auto& tls = *GetTLSForPerThreadState();
  auto sched = tls.sched;
  if (sched) {
    sched->sems_.erase(
        std::find(sched->sems_.begin(), sched->sems_.end(), tls.sem));
  }
  return tls.sem;
}

Sem* DeterministicSchedule::beforeThreadCreate() {
  Sem* s = new Sem(false);
  beforeSharedAccess();
  sems_.push_back(s);
  afterSharedAccess();
  return s;
}

void DeterministicSchedule::afterThreadCreate(Sem* sem) {
  auto& tls = *GetTLSForPerThreadState();
  DCHECK(tls.sem == nullptr);
  DCHECK(tls.sched == nullptr);
  tls.exiting = false;
  tls.sem = sem;
  tls.sched = this;
  bool started = false;
  while (!started) {
    beforeSharedAccess();
    if (active_.count(base::PlatformThread::CurrentId()) == 1) {
      started = true;
      tls.threadId = nextThreadId_++;
      DCHECK(tls.threadId.val == threadInfoMap_.size());
      threadInfoMap_.emplace_back(tls.threadId);
    }
    afterSharedAccess();
  }
  atomic_thread_fence(std::memory_order_seq_cst);
}

void DeterministicSchedule::beforeThreadExit() {
  auto& tls = *GetTLSForPerThreadState();
  DCHECK(tls.sched == this);

  atomic_thread_fence(std::memory_order_seq_cst);
  beforeSharedAccess();
  auto parent = joins_.find(base::PlatformThread::CurrentId());
  if (parent != joins_.end()) {
    reschedule(parent->second);
    joins_.erase(parent);
  }
  descheduleCurrentThread();
  active_.erase(base::PlatformThread::CurrentId());

  BASIC_TEST_DSCHED_VLOG("exiting");
  exitingSems_[base::PlatformThread::CurrentId()] = tls.sem;
  afterSharedAccess();
  // Wait for the parent thread to allow us to run thread-local destructors.
  tls.sem->wait();
  delete tls.sem;
  tls = PerThreadState();
}

void DeterministicSchedule::waitForBeforeThreadExit(basic::test::DSchedThreadWrapper& child) {
  auto& tls = *GetTLSForPerThreadState();
  DCHECK(tls.sched == this);
  beforeSharedAccess();
  DCHECK(tls.sched->joins_.count(child.GetThreadId()) == 0);
  if (tls.sched->active_.count(child.GetThreadId())) {
    Sem* sem = descheduleCurrentThread();
    tls.sched->joins_.insert({child.GetThreadId(), sem});
    afterSharedAccess();
    // Wait to be scheduled by exiting child thread
    beforeSharedAccess();
    DCHECK(!tls.sched->active_.count(child.GetThreadId()));
  }
  afterSharedAccess();
}

void DeterministicSchedule::joinAll(std::vector<std::unique_ptr<basic::test::DSchedThreadWrapper>>& children) {
  auto& tls = *GetTLSForPerThreadState();
  auto sched = tls.sched;
  if (sched) {
    // Wait until all children are about to exit
    for (size_t i = 0; i < children.size(); i++) {
      auto& child = children[i];
      sched->waitForBeforeThreadExit(*child);
    }
  }
  atomic_thread_fence(std::memory_order_seq_cst);
  /* Let each child thread proceed one at a time to protect
   * shared access during thread local destructors.*/
  for (size_t i = 0; i < children.size(); i++) {
    auto& child = children[i];
    //auto& handle = thread_handles[i];
    if (sched) {
      beforeSharedAccess();
      sched->exitingSems_[child->GetThreadId()]->post();
    }
    //base::PlatformThread::Join(handle);
    child->Join();
    if (sched) {
      afterSharedAccess();
    }
  }
}

void DeterministicSchedule::join(basic::test::DSchedThreadWrapper& child) {
  auto& tls = *GetTLSForPerThreadState();
  auto sched = tls.sched;
  if (sched) {
    sched->waitForBeforeThreadExit(child);
  }
  atomic_thread_fence(std::memory_order_seq_cst);
  BASIC_TEST_DSCHED_VLOG("joined " << std::hex << child.GetThreadId());
  if (sched) {
    beforeSharedAccess();
    sched->exitingSems_[child.GetThreadId()]->post();
  }
  child.Join();
  if (sched) {
    afterSharedAccess();
  }
}

void DeterministicSchedule::callAux(bool success) {
  auto& tls = *GetTLSForPerThreadState();
  ++step_;
  if (tls.aux_act) {
    tls.aux_act(success);
    tls.aux_act = nullptr;
  }
  if (aux_chk) {
    aux_chk(step_);
  }
}

static std::unordered_map<Sem*, std::unique_ptr<ThreadSyncVar>> semSyncVar;

void DeterministicSchedule::post(Sem* sem) {
  beforeSharedAccess();
  if (semSyncVar.count(sem) == 0) {
    semSyncVar[sem] = std::make_unique<ThreadSyncVar>();
  }
  semSyncVar[sem]->release();
  sem->post();
  BASIC_TEST_DSCHED_VLOG("sem->post() [sem=" << sem << "]");
  afterSharedAccess();
}

bool DeterministicSchedule::tryWait(Sem* sem) {
  beforeSharedAccess();
  if (semSyncVar.count(sem) == 0) {
    semSyncVar[sem] = std::make_unique<ThreadSyncVar>();
  }

  bool acquired = sem->try_wait();
  bool acquired_s = acquired ? "true" : "false";
  BASIC_TEST_DSCHED_VLOG(
      "sem->try_wait() [sem=" << sem << "] -> " << acquired_s);
  if (acquired) {
    semSyncVar[sem]->acq_rel();
  } else {
    semSyncVar[sem]->acquire();
  }

  afterSharedAccess();
  return acquired;
}

void DeterministicSchedule::wait(Sem* sem) {
  while (!tryWait(sem)) {
    // we're not busy waiting because this is a deterministic schedule
  }
}

ThreadInfo& DeterministicSchedule::getCurrentThreadInfo() {
  auto& tls = *GetTLSForPerThreadState();
  auto sched = tls.sched;
  DCHECK(sched);
  DCHECK(tls.threadId.val < sched->threadInfoMap_.size());
  return sched->threadInfoMap_[tls.threadId.val];
}

void DeterministicSchedule::atomic_thread_fence(std::memory_order mo) {
  auto& tls = *GetTLSForPerThreadState();
  if (!tls.sched) {
    std::atomic_thread_fence(mo);
    return;
  }
  beforeSharedAccess();
  ThreadInfo& threadInfo = getCurrentThreadInfo();
  switch (mo) {
    case std::memory_order_relaxed:
      DCHECK(false);
      break;
    case std::memory_order_consume:
    case std::memory_order_acquire:
      threadInfo.acqRelOrder_.sync(threadInfo.acqFenceOrder_);
      break;
    case std::memory_order_release:
      threadInfo.relFenceOrder_.sync(threadInfo.acqRelOrder_);
      break;
    case std::memory_order_acq_rel:
      threadInfo.acqRelOrder_.sync(threadInfo.acqFenceOrder_);
      threadInfo.relFenceOrder_.sync(threadInfo.acqRelOrder_);
      break;
    case std::memory_order_seq_cst:
      threadInfo.acqRelOrder_.sync(threadInfo.acqFenceOrder_);
      threadInfo.acqRelOrder_.sync(tls.sched->seqCstFenceOrder_);
      tls.sched->seqCstFenceOrder_ = threadInfo.acqRelOrder_;
      threadInfo.relFenceOrder_.sync(threadInfo.acqRelOrder_);
      break;
  }
  BASIC_TEST_DSCHED_VLOG("fence: " << basic::detail::memory_order_to_str(mo));
  afterSharedAccess();
}

detail::FutexResult futexWaitImpl(
    const detail::Futex<DeterministicAtomic>* futex,
    uint32_t expected,
    std::chrono::system_clock::time_point const* absSystemTimeout,
    std::chrono::steady_clock::time_point const* absSteadyTimeout,
    uint32_t waitMask) {
  return deterministicFutexWaitImpl<DeterministicAtomic>(
      futex,
      futexLock,
      futexQueues,
      expected,
      absSystemTimeout,
      absSteadyTimeout,
      waitMask);
}

int futexWakeImpl(
    const detail::Futex<DeterministicAtomic>* futex,
    int count,
    uint32_t wakeMask) {
  return deterministicFutexWakeImpl<DeterministicAtomic>(
      futex, futexLock, futexQueues, count, wakeMask);
}

} // namespace test
} // namespace basic

namespace basic {

template <>
CacheLocality const& CacheLocality::system<test::DeterministicAtomic>() {
  static CacheLocality cache(CacheLocality::uniform(16));
  return cache;
}

template <>
Getcpu::Func AccessSpreader<test::DeterministicAtomic>::pickGetcpuFunc() {
  return &test::DeterministicSchedule::getcpu;
}
} // namespace basic
