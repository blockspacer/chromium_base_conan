// Copyright 2015 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <base/callback.h>
#include <base/time/time.h>
#include <base/run_loop.h>

namespace basic {

/// \note Uses RunUntilIdle i.e. may run forever if queue has tasks
// Run the RunLoop until the condition passed in |terminate| returns true
// or the timeout expires.
BASE_EXPORT void RunLoopRunUntil(
    base::TimeDelta timeout,
    base::RepeatingCallback<bool()> terminate);

/// \note Uses RunUntilIdle i.e. may run forever if queue has tasks
// Run the RunLoop |loop| for up to |iterations| times
// until the condition passed in |terminate| returns true.
// Return the number of iterations.
BASE_EXPORT int RunLoopRunUntilIterations(int iterations,
                                          base::RepeatingCallback<bool()> terminate);

} // namespace basic
