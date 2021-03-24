// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/containers/prioritized_job_dispatcher.h"

#include "base/logging.h"
#include "base/compiler_specific.h"

#include "testing/gtest/include/gtest/gtest.h"

#include <ctype.h>

#include <memory>
#include <string>

namespace basic {

namespace {

enum TestRequestPriority {
  THROTTLED = 0,  // Used to signal that resources
                  // should be reserved for following
                  // requests (i.e. that higher priority
                  // following requests are expected).
  MINIMUM_PRIORITY = THROTTLED,
  IDLE = 1,  // Default "as resources available" level.
  LOWEST = 2,
  DEFAULT_PRIORITY = LOWEST,
  LOW = 3,
  MEDIUM = 4,
  HIGHEST = 5,
  LARGE = 6,
  MAXIMUM_PRIORITY = HIGHEST,
};

enum TestRequestPrioritySize {
  NUM_PRIORITIES = LARGE + 1,
};

class PrioritizedJobDispatcherTest : public testing::Test {
 public:
  typedef PrioritizedJobDispatcher::Priority Priority;
  // A job that appends |tag| to |log| when started and '.' when finished.
  // This is intended to confirm the execution order of a sequence of jobs added
  // to the dispatcher. Note that finishing order of jobs does not matter.
  class TestJob : public PrioritizedJobDispatcher::Job {
   public:
    TestJob(PrioritizedJobDispatcher* dispatcher,
            char tag,
            Priority priority,
            std::string* log)
        : dispatcher_(dispatcher),
          tag_(tag),
          priority_(priority),
          running_(false),
          log_(log) {}

    bool running() const {
      return running_;
    }

    const PrioritizedJobDispatcher::Handle handle() const {
      return handle_;
    }

    void Add(bool at_head) {
      CHECK(handle_.is_null());
      CHECK(!running_);
      size_t num_queued = dispatcher_->num_queued_jobs();
      size_t num_running = dispatcher_->num_running_jobs();

      if (!at_head) {
        handle_ = dispatcher_->Add(this, priority_);
      } else {
        handle_ = dispatcher_->AddAtHead(this, priority_);
      }

      if (handle_.is_null()) {
        EXPECT_EQ(num_queued, dispatcher_->num_queued_jobs());
        EXPECT_TRUE(running_);
        EXPECT_EQ(num_running + 1, dispatcher_->num_running_jobs());
      } else {
        EXPECT_FALSE(running_);
        EXPECT_EQ(priority_, handle_.priority());
        EXPECT_EQ(tag_, reinterpret_cast<TestJob*>(handle_.value())->tag_);
        EXPECT_EQ(num_running, dispatcher_->num_running_jobs());
      }
    }

    void ChangePriority(Priority priority) {
      CHECK(!handle_.is_null());
      CHECK(!running_);
      size_t num_queued = dispatcher_->num_queued_jobs();
      size_t num_running = dispatcher_->num_running_jobs();

      handle_ = dispatcher_->ChangePriority(handle_, priority);

      if (handle_.is_null()) {
        EXPECT_TRUE(running_);
        EXPECT_EQ(num_queued - 1, dispatcher_->num_queued_jobs());
        EXPECT_EQ(num_running + 1, dispatcher_->num_running_jobs());
      } else {
        EXPECT_FALSE(running_);
        EXPECT_EQ(priority, handle_.priority());
        EXPECT_EQ(tag_, reinterpret_cast<TestJob*>(handle_.value())->tag_);
        EXPECT_EQ(num_queued, dispatcher_->num_queued_jobs());
        EXPECT_EQ(num_running, dispatcher_->num_running_jobs());
      }
    }

    void Cancel() {
      CHECK(!handle_.is_null());
      CHECK(!running_);
      size_t num_queued = dispatcher_->num_queued_jobs();

      dispatcher_->Cancel(handle_);

      EXPECT_EQ(num_queued - 1, dispatcher_->num_queued_jobs());
      handle_ = PrioritizedJobDispatcher::Handle();
    }

    void Finish() {
      CHECK(running_);
      running_ = false;
      log_->append(1u, '.');

      dispatcher_->OnJobFinished();
    }

    // PrioritizedJobDispatcher::Job interface
    void Start() override {
      EXPECT_FALSE(running_);
      handle_ = PrioritizedJobDispatcher::Handle();
      running_ = true;
      log_->append(1u, tag_);
    }

   private:
    PrioritizedJobDispatcher* dispatcher_;

    char tag_;
    Priority priority_;

    PrioritizedJobDispatcher::Handle handle_;
    bool running_;

    std::string* log_;
  };

 protected:
  void Prepare(const PrioritizedJobDispatcher::Limits& limits) {
    dispatcher_.reset(new PrioritizedJobDispatcher(limits));
  }

  std::unique_ptr<TestJob> AddJob(char data, Priority priority) {
    std::unique_ptr<TestJob> job(
        new TestJob(dispatcher_.get(), data, priority, &log_));
    job->Add(false);
    return job;
  }

  std::unique_ptr<TestJob> AddJobAtHead(char data, Priority priority) {
    std::unique_ptr<TestJob> job(
        new TestJob(dispatcher_.get(), data, priority, &log_));
    job->Add(true);
    return job;
  }

  void Expect(const std::string& log) {
    EXPECT_EQ(0u, dispatcher_->num_queued_jobs());
    EXPECT_EQ(0u, dispatcher_->num_running_jobs());
    EXPECT_EQ(log, log_);
    log_.clear();
  }

  std::string log_;
  std::unique_ptr<PrioritizedJobDispatcher> dispatcher_;
};

TEST_F(PrioritizedJobDispatcherTest, GetLimits) {
  // Set non-trivial initial limits.
  PrioritizedJobDispatcher::Limits original_limits(NUM_PRIORITIES, 5);
  original_limits.reserved_slots[HIGHEST] = 1;
  original_limits.reserved_slots[LOW] = 2;
  Prepare(original_limits);

  // Get current limits, make sure the original limits are returned.
  PrioritizedJobDispatcher::Limits retrieved_limits = dispatcher_->GetLimits();
  ASSERT_EQ(original_limits.total_jobs, retrieved_limits.total_jobs);
  ASSERT_EQ(static_cast<size_t>(NUM_PRIORITIES),
            retrieved_limits.reserved_slots.size());
  for (size_t priority = MINIMUM_PRIORITY; priority <= MAXIMUM_PRIORITY;
       ++priority) {
    EXPECT_EQ(original_limits.reserved_slots[priority],
              retrieved_limits.reserved_slots[priority]);
  }

  // Set new limits.
  PrioritizedJobDispatcher::Limits new_limits(NUM_PRIORITIES, 6);
  new_limits.reserved_slots[MEDIUM] = 3;
  new_limits.reserved_slots[LOWEST] = 1;
  Prepare(new_limits);

  // Get current limits, make sure the new limits are returned.
  retrieved_limits = dispatcher_->GetLimits();
  ASSERT_EQ(new_limits.total_jobs, retrieved_limits.total_jobs);
  ASSERT_EQ(static_cast<size_t>(NUM_PRIORITIES),
            retrieved_limits.reserved_slots.size());
  for (size_t priority = MINIMUM_PRIORITY; priority <= MAXIMUM_PRIORITY;
       ++priority) {
    EXPECT_EQ(new_limits.reserved_slots[priority],
              retrieved_limits.reserved_slots[priority]);
  }
}

TEST_F(PrioritizedJobDispatcherTest, AddAFIFO) {
  // Allow only one running job.
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', IDLE);
  std::unique_ptr<TestJob> job_c = AddJob('c', IDLE);
  std::unique_ptr<TestJob> job_d = AddJob('d', IDLE);

  ASSERT_TRUE(job_a->running());
  job_a->Finish();
  ASSERT_TRUE(job_b->running());
  job_b->Finish();
  ASSERT_TRUE(job_c->running());
  job_c->Finish();
  ASSERT_TRUE(job_d->running());
  job_d->Finish();

  Expect("a.b.c.d.");
}

TEST_F(PrioritizedJobDispatcherTest, AddPriority) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', MEDIUM);
  std::unique_ptr<TestJob> job_c = AddJob('c', HIGHEST);
  std::unique_ptr<TestJob> job_d = AddJob('d', HIGHEST);
  std::unique_ptr<TestJob> job_e = AddJob('e', MEDIUM);

  ASSERT_TRUE(job_a->running());
  job_a->Finish();
  ASSERT_TRUE(job_c->running());
  job_c->Finish();
  ASSERT_TRUE(job_d->running());
  job_d->Finish();
  ASSERT_TRUE(job_b->running());
  job_b->Finish();
  ASSERT_TRUE(job_e->running());
  job_e->Finish();

  Expect("a.c.d.b.e.");
}

TEST_F(PrioritizedJobDispatcherTest, AddAtHead) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', MEDIUM);
  std::unique_ptr<TestJob> job_b = AddJobAtHead('b', MEDIUM);
  std::unique_ptr<TestJob> job_c = AddJobAtHead('c', HIGHEST);
  std::unique_ptr<TestJob> job_d = AddJobAtHead('d', HIGHEST);
  std::unique_ptr<TestJob> job_e = AddJobAtHead('e', MEDIUM);
  std::unique_ptr<TestJob> job_f = AddJob('f', MEDIUM);

  ASSERT_TRUE(job_a->running());
  job_a->Finish();
  ASSERT_TRUE(job_d->running());
  job_d->Finish();
  ASSERT_TRUE(job_c->running());
  job_c->Finish();
  ASSERT_TRUE(job_e->running());
  job_e->Finish();
  ASSERT_TRUE(job_b->running());
  job_b->Finish();
  ASSERT_TRUE(job_f->running());
  job_f->Finish();

  Expect("a.d.c.e.b.f.");
}

TEST_F(PrioritizedJobDispatcherTest, EnforceLimits) {
  // Reserve 2 for HIGHEST and 1 for LOW or higher.
  // This leaves 2 for LOWEST or lower.
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 5);
  limits.reserved_slots[HIGHEST] = 2;
  limits.reserved_slots[LOW] = 1;
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);  // Uses unreserved slot.
  std::unique_ptr<TestJob> job_b = AddJob('b', IDLE);  // Uses unreserved slot.
  std::unique_ptr<TestJob> job_c = AddJob('c', LOWEST);   // Must wait.
  std::unique_ptr<TestJob> job_d = AddJob('d', LOW);      // Uses reserved slot.
  std::unique_ptr<TestJob> job_e = AddJob('e', MEDIUM);   // Must wait.
  std::unique_ptr<TestJob> job_f = AddJob('f', HIGHEST);  // Uses reserved slot.
  std::unique_ptr<TestJob> job_g = AddJob('g', HIGHEST);  // Uses reserved slot.
  std::unique_ptr<TestJob> job_h = AddJob('h', HIGHEST);  // Must wait.

  EXPECT_EQ(5u, dispatcher_->num_running_jobs());
  EXPECT_EQ(3u, dispatcher_->num_queued_jobs());

  ASSERT_TRUE(job_a->running());
  ASSERT_TRUE(job_b->running());
  ASSERT_TRUE(job_d->running());
  ASSERT_TRUE(job_f->running());
  ASSERT_TRUE(job_g->running());
  // a, b, d, f, g are running. Finish them in any order.
  job_b->Finish();  // Releases h.
  job_f->Finish();
  job_a->Finish();
  job_g->Finish();  // Releases e.
  job_d->Finish();
  ASSERT_TRUE(job_e->running());
  ASSERT_TRUE(job_h->running());
  // h, e are running.
  job_e->Finish();  // Releases c.
  ASSERT_TRUE(job_c->running());
  job_c->Finish();
  job_h->Finish();

  Expect("abdfg.h...e..c..");
}

TEST_F(PrioritizedJobDispatcherTest, ChangePriority) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 2);
  // Reserve one slot only for HIGHEST priority requests.
  limits.reserved_slots[HIGHEST] = 1;
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', LOW);
  std::unique_ptr<TestJob> job_c = AddJob('c', MEDIUM);
  std::unique_ptr<TestJob> job_d = AddJob('d', MEDIUM);
  std::unique_ptr<TestJob> job_e = AddJob('e', IDLE);

  ASSERT_FALSE(job_b->running());
  ASSERT_FALSE(job_c->running());
  job_b->ChangePriority(MEDIUM);
  job_c->ChangePriority(LOW);

  ASSERT_TRUE(job_a->running());
  job_a->Finish();
  ASSERT_TRUE(job_d->running());
  job_d->Finish();

  EXPECT_FALSE(job_e->running());
  // Increasing |job_e|'s priority to HIGHEST should result in it being
  // started immediately.
  job_e->ChangePriority(HIGHEST);
  ASSERT_TRUE(job_e->running());
  job_e->Finish();

  ASSERT_TRUE(job_b->running());
  job_b->Finish();
  ASSERT_TRUE(job_c->running());
  job_c->Finish();

  Expect("a.d.be..c.");
}

TEST_F(PrioritizedJobDispatcherTest, Cancel) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', IDLE);
  std::unique_ptr<TestJob> job_c = AddJob('c', IDLE);
  std::unique_ptr<TestJob> job_d = AddJob('d', IDLE);
  std::unique_ptr<TestJob> job_e = AddJob('e', IDLE);

  ASSERT_FALSE(job_b->running());
  ASSERT_FALSE(job_d->running());
  job_b->Cancel();
  job_d->Cancel();

  ASSERT_TRUE(job_a->running());
  job_a->Finish();
  ASSERT_TRUE(job_c->running());
  job_c->Finish();
  ASSERT_TRUE(job_e->running());
  job_e->Finish();

  Expect("a.c.e.");
}

TEST_F(PrioritizedJobDispatcherTest, Evict) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', LOW);
  std::unique_ptr<TestJob> job_c = AddJob('c', HIGHEST);
  std::unique_ptr<TestJob> job_d = AddJob('d', LOW);
  std::unique_ptr<TestJob> job_e = AddJob('e', HIGHEST);

  EXPECT_EQ(job_b.get(), dispatcher_->EvictOldestLowest());
  EXPECT_EQ(job_d.get(), dispatcher_->EvictOldestLowest());

  ASSERT_TRUE(job_a->running());
  job_a->Finish();
  ASSERT_TRUE(job_c->running());
  job_c->Finish();
  ASSERT_TRUE(job_e->running());
  job_e->Finish();

  Expect("a.c.e.");
}

TEST_F(PrioritizedJobDispatcherTest, EvictFromEmpty) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);
  EXPECT_TRUE(dispatcher_->EvictOldestLowest() == nullptr);
}

TEST_F(PrioritizedJobDispatcherTest, AddWhileZeroLimits) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 2);
  Prepare(limits);

  dispatcher_->SetLimitsToZero();
  std::unique_ptr<TestJob> job_a = AddJob('a', LOW);
  std::unique_ptr<TestJob> job_b = AddJob('b', MEDIUM);
  std::unique_ptr<TestJob> job_c = AddJobAtHead('c', MEDIUM);

  EXPECT_EQ(0u, dispatcher_->num_running_jobs());
  EXPECT_EQ(3u, dispatcher_->num_queued_jobs());

  dispatcher_->SetLimits(limits);
  EXPECT_EQ(2u, dispatcher_->num_running_jobs());
  EXPECT_EQ(1u, dispatcher_->num_queued_jobs());

  ASSERT_TRUE(job_b->running());
  job_b->Finish();

  ASSERT_TRUE(job_c->running());
  job_c->Finish();

  ASSERT_TRUE(job_a->running());
  job_a->Finish();

  Expect("cb.a..");
}

TEST_F(PrioritizedJobDispatcherTest, ReduceLimitsWhileJobQueued) {
  PrioritizedJobDispatcher::Limits initial_limits(NUM_PRIORITIES, 2);
  Prepare(initial_limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', MEDIUM);
  std::unique_ptr<TestJob> job_b = AddJob('b', MEDIUM);
  std::unique_ptr<TestJob> job_c = AddJob('c', MEDIUM);
  std::unique_ptr<TestJob> job_d = AddJob('d', MEDIUM);
  std::unique_ptr<TestJob> job_e = AddJob('e', MEDIUM);

  EXPECT_EQ(2u, dispatcher_->num_running_jobs());
  EXPECT_EQ(3u, dispatcher_->num_queued_jobs());

  // Reduce limits to just allow one job at a time.  Running jobs should not
  // be affected.
  dispatcher_->SetLimits(PrioritizedJobDispatcher::Limits(NUM_PRIORITIES, 1));

  EXPECT_EQ(2u, dispatcher_->num_running_jobs());
  EXPECT_EQ(3u, dispatcher_->num_queued_jobs());

  // Finishing a job should not result in another job starting.
  ASSERT_TRUE(job_a->running());
  job_a->Finish();
  EXPECT_EQ(1u, dispatcher_->num_running_jobs());
  EXPECT_EQ(3u, dispatcher_->num_queued_jobs());

  ASSERT_TRUE(job_b->running());
  job_b->Finish();
  EXPECT_EQ(1u, dispatcher_->num_running_jobs());
  EXPECT_EQ(2u, dispatcher_->num_queued_jobs());

  // Increasing the limits again should let c start.
  dispatcher_->SetLimits(initial_limits);

  ASSERT_TRUE(job_c->running());
  job_c->Finish();
  ASSERT_TRUE(job_d->running());
  job_d->Finish();
  ASSERT_TRUE(job_e->running());
  job_e->Finish();

  Expect("ab..cd.e..");
}

TEST_F(PrioritizedJobDispatcherTest, ZeroLimitsThenCancel) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', IDLE);
  std::unique_ptr<TestJob> job_c = AddJob('c', IDLE);
  dispatcher_->SetLimitsToZero();

  ASSERT_TRUE(job_a->running());
  EXPECT_FALSE(job_b->running());
  EXPECT_FALSE(job_c->running());
  job_a->Finish();

  EXPECT_FALSE(job_b->running());
  EXPECT_FALSE(job_c->running());

  // Cancelling b shouldn't start job c.
  job_b->Cancel();
  EXPECT_FALSE(job_c->running());

  // Restoring the limits should start c.
  dispatcher_->SetLimits(limits);
  ASSERT_TRUE(job_c->running());
  job_c->Finish();

  Expect("a.c.");
}

TEST_F(PrioritizedJobDispatcherTest, ZeroLimitsThenIncreasePriority) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 2);
  limits.reserved_slots[HIGHEST] = 1;
  Prepare(limits);

  std::unique_ptr<TestJob> job_a = AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', IDLE);
  EXPECT_TRUE(job_a->running());
  EXPECT_FALSE(job_b->running());
  dispatcher_->SetLimitsToZero();

  job_b->ChangePriority(HIGHEST);
  EXPECT_FALSE(job_b->running());
  job_a->Finish();
  EXPECT_FALSE(job_b->running());

  job_b->Cancel();
  Expect("a.");
}

#if GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
TEST_F(PrioritizedJobDispatcherTest, CancelNull) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);
  EXPECT_DEBUG_DEATH(dispatcher_->Cancel(PrioritizedJobDispatcher::Handle()), "");
}

TEST_F(PrioritizedJobDispatcherTest, CancelMissing) {
  PrioritizedJobDispatcher::Limits limits(NUM_PRIORITIES, 1);
  Prepare(limits);
  AddJob('a', IDLE);
  std::unique_ptr<TestJob> job_b = AddJob('b', IDLE);
  PrioritizedJobDispatcher::Handle handle = job_b->handle();
  ASSERT_FALSE(handle.is_null());
  dispatcher_->Cancel(handle);
  EXPECT_DEBUG_DEATH(dispatcher_->Cancel(handle), "");
}
#endif  // GTEST_HAS_DEATH_TEST && !defined(NDEBUG)

}  // namespace

}  // namespace basic
