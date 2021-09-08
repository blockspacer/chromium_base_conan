// mojo/public/interfaces/bindings/tests/test_name_generator.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_NAME_GENERATOR_MOJOM_SHARED_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_NAME_GENERATOR_MOJOM_SHARED_H_

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
#include "mojo/public/interfaces/bindings/tests/test_name_generator.mojom-shared-internal.h"




#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace sample {


}  // namespace sample

namespace mojo {
namespace internal {

}  // namespace internal
}  // namespace mojo


namespace sample {


// @generated_from: sample.SupportedCases
enum class SupportedCases : int32_t {
  
// @generated_from: sample.SupportedCases.lowerCamelCase
  lowerCamelCase = 0,
  
// @generated_from: sample.SupportedCases.UpperCamelCase
  UpperCamelCase = 1,
  
// @generated_from: sample.SupportedCases.snake_case
  snake_case = 2,
  
// @generated_from: sample.SupportedCases.MACRO_CASE
  MACRO_CASE = 3,
  
// @generated_from: sample.SupportedCases.kHungarianNotation
  kHungarianNotation = 4,
  
// @generated_from: sample.SupportedCases.upperACRONYMCase
  upperACRONYMCase = 5,
  kMinValue = 0,
  kMaxValue = 5,
};

 std::ostream& operator<<(std::ostream& os, SupportedCases value);
inline bool IsKnownEnumValue(SupportedCases value) {
  return internal::SupportedCases_Data::IsKnownValue(
      static_cast<int32_t>(value));
}


}  // namespace sample

namespace std {

template <>
struct hash<::sample::SupportedCases>
    : public mojo::internal::EnumHashImpl<::sample::SupportedCases> {};

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::sample::SupportedCases, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = EnumTraits<::sample::SupportedCases, UserType>;

  static void Serialize(UserType input, int32_t* output) {
    *output = static_cast<int32_t>(Traits::ToMojom(input));
  }

  static bool Deserialize(int32_t input, UserType* output) {
    return Traits::FromMojom(::mojo::internal::ToKnownEnumValueHelper(
        static_cast<::sample::SupportedCases>(input)), output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace sample {


}  // namespace sample

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

namespace perfetto {

template <>
struct  TraceFormatTraits<::sample::SupportedCases> {
 static void WriteIntoTracedValue(perfetto::TracedValue context, ::sample::SupportedCases value);
};

} // namespace perfetto

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_NAME_GENERATOR_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTUxMywgImJlZ2luIjogMTQ5OSwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogInNhbXBsZS5TdXBwb3J0ZWRDYXNlcyJ9fSwgeyJlbmQi
OiAxNjAyLCAiYmVnaW4iOiAxNTg4LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwg
InR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5n
b29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWdu
YXR1cmUiOiAic2FtcGxlLlN1cHBvcnRlZENhc2VzLmxvd2VyQ2FtZWxDYXNlIn19LCB7ImVuZCI6
IDE2ODQsICJiZWdpbiI6IDE2NzAsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJzYW1wbGUuU3VwcG9ydGVkQ2FzZXMuVXBwZXJDYW1lbENhc2UifX0sIHsiZW5kIjog
MTc1OCwgImJlZ2luIjogMTc0OCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0
eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29v
Z2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0
dXJlIjogInNhbXBsZS5TdXBwb3J0ZWRDYXNlcy5zbmFrZV9jYXNlIn19LCB7ImVuZCI6IDE4MzIs
ICJiZWdpbiI6IDE4MjIsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6
ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNv
dXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6
ICJzYW1wbGUuU3VwcG9ydGVkQ2FzZXMuTUFDUk9fQ0FTRSJ9fSwgeyJlbmQiOiAxOTIyLCAiYmVn
aW4iOiAxOTA0LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5j
aG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2Uu
Y29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAic2Ft
cGxlLlN1cHBvcnRlZENhc2VzLmtIdW5nYXJpYW5Ob3RhdGlvbiJ9fSwgeyJlbmQiOiAyMDA4LCAi
YmVnaW4iOiAxOTkyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAi
YW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3Vy
Y2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAi
c2FtcGxlLlN1cHBvcnRlZENhc2VzLnVwcGVyQUNST05ZTUNhc2UifX1dLCAidHlwZSI6ICJreXRo
ZTAifQ==
*/