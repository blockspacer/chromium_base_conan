// Copyright 2014 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <map>
#include <string>
#include <any>

#include <base/base_export.h>

namespace basic {

using AnyDictionary = std::map<std::string, std::any>;

// GetValuePtr tries to retrieve the named key from the dictionary
// and convert it to the type T.  If the value does not exist, or the type
// conversion fails, the nullptr is returned.
template <typename T>
const T* GetValuePtr(const AnyDictionary& dictionary,
                     const std::string& key,
                     std::optional<T> default_value = std::nullopt) {
  AnyDictionary::const_iterator it = dictionary.find(key);
  if (it == dictionary.end()) {
    return nullptr;
  }
  const std::any& val = it->second;
  if (!val.has_value()) {
    return nullptr;
  }
  const T* ptr = std::any_cast<T>(&it->second);
  return ptr;
}

}  // namespace basic
