// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/system/sys_info.h"

#include <algorithm>

#include "base/base_switches.h"
#include "base/bind.h"
#include "base/callback.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/lazy_instance.h"
#include "base/location.h"
#include "base/logging.h"
#include "base/metrics/field_trial_params.h"
#include "base/system/sys_info_internal.h"
#include "base/task/post_task.h"
#include "base/task/task_traits.h"
#include "base/task_runner_util.h"
#include "base/time/time.h"
#include "build/build_config.h"

#if defined(OS_EMSCRIPTEN)
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct s_mallinfo {
    int arena;    /* non-mmapped space allocated from system */
    int ordblks;  /* number of free chunks */
    int smblks;   /* always 0 */
    int hblks;    /* always 0 */
    int hblkhd;   /* space in mmapped regions */
    int usmblks;  /* maximum total allocated space */
    int fsmblks;  /* always 0 */
    int uordblks; /* total allocated space */
    int fordblks; /* total free space */
    int keepcost; /* releasable (via malloc_trim) space */
};

extern "C" {
extern s_mallinfo mallinfo();
}
#endif

namespace base {
namespace {

// Feature used to control the heuristics used to categorize a device as low
// end.
const base::Feature kLowEndDeviceDetectionFeature{
    "LowEndDeviceDetection", base::FEATURE_DISABLED_BY_DEFAULT};

static const int kLowMemoryDeviceThresholdMBDefault = 512;

int GetLowMemoryDeviceThresholdMB() {
  static constexpr base::FeatureParam<int> kLowEndDeviceMemoryThresholdMB{
      &kLowEndDeviceDetectionFeature, "LowEndDeviceMemoryThresholdMB",
      kLowMemoryDeviceThresholdMBDefault};
  // If the feature is disabled then |Get| will return the default value.
  return kLowEndDeviceMemoryThresholdMB.Get();
}
}  // namespace

#if defined(OS_EMSCRIPTEN)
int64_t SysInfo::AmountOfPhysicalMemoryImpl() {
    //int resTOTAL_MEMORY = EM_ASM_INT(return TOTAL_MEMORY);
    int resHEAP8 = EM_ASM_INT(return HEAP8.length);
    //DCHECK(resHEAP8 == resTOTAL_MEMORY);
    return static_cast<int64_t>(resHEAP8);
}

// static
SysInfo::HardwareInfo SysInfo::GetHardwareInfoSync() {
    static const size_t kMaxStringSize = 100u;
    HardwareInfo info;
    info.model = "emscripten";
    info.manufacturer = "emscripten";
    info.serial_number = "emscripten";
    return info;
}

// static
int64_t SysInfo::AmountOfAvailablePhysicalMemoryImpl() {
    s_mallinfo i = mallinfo();
    unsigned int totalMemory = AmountOfPhysicalMemoryImpl();
    unsigned int dynamicTop = EM_ASM_INT(return HEAPU32[DYNAMICTOP_PTR>>2]);
    return static_cast<int64_t>( totalMemory - dynamicTop + i.fordblks);
}

// static
std::string SysInfo::CPUModelName() {
    return std::string("emscripten");
}
#endif

// static
int64_t SysInfo::AmountOfPhysicalMemory() {
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kEnableLowEndDeviceMode)) {
    return GetLowMemoryDeviceThresholdMB() * 1024 * 1024;
  }

  return AmountOfPhysicalMemoryImpl();
}

// static
int64_t SysInfo::AmountOfAvailablePhysicalMemory() {
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kEnableLowEndDeviceMode)) {
    // Estimate the available memory by subtracting our memory used estimate
    // from the fake |GetLowMemoryDeviceThresholdMB()| limit.
    size_t memory_used =
        AmountOfPhysicalMemoryImpl() - AmountOfAvailablePhysicalMemoryImpl();
    size_t memory_limit = GetLowMemoryDeviceThresholdMB() * 1024 * 1024;
    // std::min ensures no underflow, as |memory_used| can be > |memory_limit|.
    return memory_limit - std::min(memory_used, memory_limit);
  }

  return AmountOfAvailablePhysicalMemoryImpl();
}

bool SysInfo::IsLowEndDevice() {
  if (base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kEnableLowEndDeviceMode)) {
    return true;
  }

  return IsLowEndDeviceImpl();
}

#if !defined(OS_ANDROID)

bool DetectLowEndDevice() {
  CommandLine* command_line = CommandLine::ForCurrentProcess();
  if (command_line->HasSwitch(switches::kEnableLowEndDeviceMode))
    return true;
  if (command_line->HasSwitch(switches::kDisableLowEndDeviceMode))
    return false;

  int ram_size_mb = SysInfo::AmountOfPhysicalMemoryMB();
  return (ram_size_mb > 0 && ram_size_mb <= GetLowMemoryDeviceThresholdMB());
}

static LazyInstance<internal::LazySysInfoValue<bool, DetectLowEndDevice>>::Leaky
    g_lazy_low_end_device = LAZY_INSTANCE_INITIALIZER;

// static
bool SysInfo::IsLowEndDeviceImpl() {
  return g_lazy_low_end_device.Get().value();
}
#endif

#if !defined(OS_MACOSX) && !defined(OS_ANDROID)
std::string SysInfo::HardwareModelName() {
  return std::string();
}
#endif

void SysInfo::GetHardwareInfo(base::OnceCallback<void(HardwareInfo)> callback) {
#if defined(OS_WIN)
  base::PostTaskAndReplyWithResult(
      base::CreateCOMSTATaskRunnerWithTraits({}).get(), FROM_HERE,
      base::BindOnce(&GetHardwareInfoSync), std::move(callback));
#elif defined(OS_ANDROID) || defined(OS_MACOSX)
  base::PostTaskAndReplyWithResult(
      FROM_HERE, base::BindOnce(&GetHardwareInfoSync), std::move(callback));
#elif defined(OS_LINUX)
  base::PostTaskWithTraitsAndReplyWithResult(
      FROM_HERE, {base::MayBlock()}, base::BindOnce(&GetHardwareInfoSync),
      std::move(callback));
#else
  NOTIMPLEMENTED();
  base::PostTask(FROM_HERE,
                 base::BindOnce(std::move(callback), HardwareInfo()));
#endif
}

// static
base::TimeDelta SysInfo::Uptime() {
  // This code relies on an implementation detail of TimeTicks::Now() - that
  // its return value happens to coincide with the system uptime value in
  // microseconds, on Win/Mac/iOS/Linux/ChromeOS and Android.
  int64_t uptime_in_microseconds = TimeTicks::Now().ToInternalValue();
  return base::TimeDelta::FromMicroseconds(uptime_in_microseconds);
}

}  // namespace base
