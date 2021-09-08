// mojo/public/mojom/base/thread_priority.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_THREAD_PRIORITY_MOJOM_SHARED_H_
#define MOJO_PUBLIC_MOJOM_BASE_THREAD_PRIORITY_MOJOM_SHARED_H_

#include <stdint.h>

#include <functional>
#include <ostream>
#include <type_traits>
#include <utility>

#include "base/compiler_specific.h"
#include "base/containers/flat_map.h"
#include "mojo/public/cpp/bindings/array_data_view.h"
#include "mojo/public/cpp/bindings/enum_traits.h"
#include "mojo/public/cpp/bindings/interface_data_view.h"
#include "mojo/public/cpp/bindings/lib/bindings_internal.h"
#include "mojo/public/cpp/bindings/lib/serialization.h"
#include "mojo/public/cpp/bindings/map_data_view.h"
#include "mojo/public/cpp/bindings/string_data_view.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value_forward.h"
#include "mojo/public/mojom/base/thread_priority.mojom-shared-internal.h"



#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {


}  // namespace mojom
}  // namespace mojo_base

namespace mojo {
namespace internal {

}  // namespace internal
}  // namespace mojo


namespace mojo_base {
namespace mojom {


// @generated_from: mojo_base.mojom.ThreadPriority
enum class ThreadPriority : int32_t {
  
// @generated_from: mojo_base.mojom.ThreadPriority.BACKGROUND
  BACKGROUND = 0,
  
// @generated_from: mojo_base.mojom.ThreadPriority.NORMAL
  NORMAL = 1,
  
// @generated_from: mojo_base.mojom.ThreadPriority.DISPLAY
  DISPLAY = 2,
  
// @generated_from: mojo_base.mojom.ThreadPriority.REALTIME_AUDIO
  REALTIME_AUDIO = 3,
  kMinValue = 0,
  kMaxValue = 3,
};

COMPONENT_EXPORT(MOJO_BASE_MOJOM_SHARED) std::ostream& operator<<(std::ostream& os, ThreadPriority value);
inline bool IsKnownEnumValue(ThreadPriority value) {
  return internal::ThreadPriority_Data::IsKnownValue(
      static_cast<int32_t>(value));
}


}  // namespace mojom
}  // namespace mojo_base

namespace std {

template <>
struct hash<::mojo_base::mojom::ThreadPriority>
    : public mojo::internal::EnumHashImpl<::mojo_base::mojom::ThreadPriority> {};

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::mojo_base::mojom::ThreadPriority, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = EnumTraits<::mojo_base::mojom::ThreadPriority, UserType>;

  static void Serialize(UserType input, int32_t* output) {
    *output = static_cast<int32_t>(Traits::ToMojom(input));
  }

  static bool Deserialize(int32_t input, UserType* output) {
    return Traits::FromMojom(::mojo::internal::ToKnownEnumValueHelper(
        static_cast<::mojo_base::mojom::ThreadPriority>(input)), output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace mojo_base {
namespace mojom {


}  // namespace mojom
}  // namespace mojo_base

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

namespace perfetto {

template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_SHARED) TraceFormatTraits<::mojo_base::mojom::ThreadPriority> {
 static void WriteIntoTracedValue(perfetto::TracedValue context, ::mojo_base::mojom::ThreadPriority value);
};

} // namespace perfetto

#endif  // MOJO_PUBLIC_MOJOM_BASE_THREAD_PRIORITY_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTU0OCwgImJlZ2luIjogMTUzNCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5UaHJlYWRQcmlvcml0eSJ9
fSwgeyJlbmQiOiAxNjM4LCAiYmVnaW4iOiAxNjI4LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2Vu
ZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJj
aHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pv
bSIsICJzaWduYXR1cmUiOiAibW9qb19iYXNlLm1vam9tLlRocmVhZFByaW9yaXR5LkJBQ0tHUk9V
TkQifX0sIHsiZW5kIjogMTcxMywgImJlZ2luIjogMTcwNywgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5UaHJlYWRQcmlvcml0eS5OT1JN
QUwifX0sIHsiZW5kIjogMTc5MCwgImJlZ2luIjogMTc4MywgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5UaHJlYWRQcmlvcml0eS5ESVNQ
TEFZIn19LCB7ImVuZCI6IDE4ODEsICJiZWdpbiI6IDE4NjcsICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvX2Jhc2UubW9qb20uVGhyZWFkUHJpb3JpdHkuUkVB
TFRJTUVfQVVESU8ifX1dLCAidHlwZSI6ICJreXRoZTAifQ==
*/