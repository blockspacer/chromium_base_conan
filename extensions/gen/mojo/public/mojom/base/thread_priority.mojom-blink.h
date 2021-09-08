// mojo/public/mojom/base/thread_priority.mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_THREAD_PRIORITY_MOJOM_BLINK_H_
#define MOJO_PUBLIC_MOJOM_BASE_THREAD_PRIORITY_MOJOM_BLINK_H_

#include <stdint.h>

#include <limits>
#include <type_traits>
#include <utility>

#include "base/callback.h"
#include "base/macros.h"
#include "base/optional.h"

#include "mojo/public/cpp/bindings/clone_traits.h"
#include "mojo/public/cpp/bindings/equals_traits.h"
#include "mojo/public/cpp/bindings/lib/serialization.h"
#include "mojo/public/cpp/bindings/struct_ptr.h"
#include "mojo/public/cpp/bindings/struct_traits.h"
#include "mojo/public/cpp/bindings/union_traits.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value_forward.h"
#include "mojo/public/mojom/base/thread_priority.mojom-shared.h"
#include "mojo/public/mojom/base/thread_priority.mojom-blink-forward.h"

#include "mojo/public/cpp/bindings/lib/wtf_clone_equals_util.h"
#include "mojo/public/cpp/bindings/lib/wtf_hash_util.h"
#include "third_party/blink/renderer/platform/wtf/hash_functions.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"




#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace WTF {
struct mojo_base_mojom_internal_ThreadPriority_DataHashFn {
  static unsigned GetHash(const ::mojo_base::mojom::ThreadPriority& value) {
    using utype = std::underlying_type<::mojo_base::mojom::ThreadPriority>::type;
    return DefaultHash<utype>::Hash().GetHash(static_cast<utype>(value));
  }
  static bool Equal(const ::mojo_base::mojom::ThreadPriority& left, const ::mojo_base::mojom::ThreadPriority& right) {
    return left == right;
  }
  static const bool safe_to_compare_to_empty_or_deleted = true;
};

template <>
struct HashTraits<::mojo_base::mojom::ThreadPriority>
    : public GenericHashTraits<::mojo_base::mojom::ThreadPriority> {
  static_assert(true,
                "-1000000 is a reserved enum value");
  static_assert(true,
                "-1000001 is a reserved enum value");
  static const bool hasIsEmptyValueFunction = true;
  static bool IsEmptyValue(const ::mojo_base::mojom::ThreadPriority& value) {
    return value == static_cast<::mojo_base::mojom::ThreadPriority>(-1000000);
  }
  static void ConstructDeletedValue(::mojo_base::mojom::ThreadPriority& slot, bool) {
    slot = static_cast<::mojo_base::mojom::ThreadPriority>(-1000001);
  }
  static bool IsDeletedValue(const ::mojo_base::mojom::ThreadPriority& value) {
    return value == static_cast<::mojo_base::mojom::ThreadPriority>(-1000001);
  }
};
}  // namespace WTF


namespace mojo_base {
namespace mojom {
namespace blink {





}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {

}  // namespace mojo

#endif  // MOJO_PUBLIC_MOJOM_BASE_THREAD_PRIORITY_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/