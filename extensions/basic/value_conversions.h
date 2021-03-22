// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

// This file contains methods to convert things to a |Value| and back.

#include <memory>

#include "base/base_export.h"
#include "base/compiler_specific.h"

namespace base {

class FilePath;
class Time;
class TimeDelta;
class UnguessableToken;
class Value;

} // namespace base

namespace basic {

// In GetValueAs*() functions, the caller owns the object pointed by the output
// parameter, e.g. |file_path|. If false is returned, the value of the object
// pointed by the output parameter is not changed. It is okay to pass nullptr to
// the output parameter.

// Warning: The Values involved could be stored on persistent storage like files
// on disks. Therefore, changes in implementation could lead to data corruption
// and must be done with caution.

BASE_EXPORT base::Value CreateFilePathValue(const base::FilePath& in_value);
BASE_EXPORT bool GetValueAsFilePath(const base::Value& value,
                                    base::FilePath* file_path) WARN_UNUSED_RESULT;

BASE_EXPORT base::Value CreateTimeValue(const base::Time& time);
BASE_EXPORT bool GetValueAsTime(const base::Value& value,
                                base::Time* time) WARN_UNUSED_RESULT;

BASE_EXPORT base::Value CreateTimeDeltaValue(const base::TimeDelta& time_delta);
BASE_EXPORT bool GetValueAsTimeDelta(const base::Value& value,
                                     base::TimeDelta* time_delta) WARN_UNUSED_RESULT;

BASE_EXPORT base::Value CreateUnguessableTokenValue(const base::UnguessableToken& token);
BASE_EXPORT bool GetValueAsUnguessableToken(const base::Value& value,
                                            base::UnguessableToken* token)
    WARN_UNUSED_RESULT;

}  // namespace basic
