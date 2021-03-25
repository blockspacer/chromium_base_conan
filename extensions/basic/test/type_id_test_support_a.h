// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include "base/component_export.h"
#include "basic/type_id.h"

namespace basic {

struct COMPONENT_EXPORT(BASE_TEST) TestType {};

// This is here to help test basic::TypeId.
struct COMPONENT_EXPORT(BASE_TEST) TypeIdTestSupportA {
  static TypeId GetTypeIdForTypeInAnonymousNameSpace();
  static TypeId GetTypeIdForUniquePtrInt();
  static TypeId GetTypeIdForUniquePtrTestType();
};

}  // namespace basic
