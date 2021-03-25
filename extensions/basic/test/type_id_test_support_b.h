// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "base/component_export.h"
#include "basic/type_id.h"

namespace basic {

// This is here to help test basic::TypeId.
struct COMPONENT_EXPORT(BASE_TEST) TypeIdTestSupportB {
  static TypeId GetTypeIdForTypeInAnonymousNameSpace();
  static TypeId GetTypeIdForUniquePtrInt();
};

}  // namespace basic
