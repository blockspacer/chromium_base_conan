// mojo/public/interfaces/bindings/tests/echo_import/echo_import.mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_IMPORT_ECHO_IMPORT_MOJOM_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_IMPORT_ECHO_IMPORT_MOJOM_H_

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
#include "mojo/public/interfaces/bindings/tests/echo_import/echo_import.mojom-shared.h"
#include "mojo/public/interfaces/bindings/tests/echo_import/echo_import.mojom-forward.h"
#include <string>
#include <vector>





#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace test {
namespace echo_import {
namespace mojom {





// @generated_from: test.echo_import.mojom.Point
class  Point {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Point, T>::value>;
  using DataView = PointDataView;
  using Data_ = internal::Point_Data;

  template <typename... Args>
  static PointPtr New(Args&&... args) {
    return PointPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static PointPtr From(const U& u) {
    return mojo::TypeConverter<PointPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Point>::Convert(*this);
  }


  Point();

  Point(
      int32_t x,
      int32_t y);

  ~Point();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = PointPtr>
  PointPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Point::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Point::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        Point::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Point::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Point_UnserializedMessageContext<
            UserType, Point::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Point::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return Point::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Point_UnserializedMessageContext<
            UserType, Point::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Point::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: test.echo_import.mojom.Point.x
  int32_t x;
  
// @generated_from: test.echo_import.mojom.Point.y
  int32_t y;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Point::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Point::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Point::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Point::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}




template <typename StructPtrType>
PointPtr Point::Clone() const {
  return New(
      mojo::Clone(x),
      mojo::Clone(y)
  );
}

template <typename T, Point::EnableIfSame<T>*>
bool Point::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->x, other_struct.x))
    return false;
  if (!mojo::Equals(this->y, other_struct.y))
    return false;
  return true;
}

template <typename T, Point::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.x < rhs.x)
    return true;
  if (rhs.x < lhs.x)
    return false;
  if (lhs.y < rhs.y)
    return true;
  if (rhs.y < lhs.y)
    return false;
  return false;
}


}  // namespace mojom
}  // namespace echo_import
}  // namespace test

namespace mojo {


template <>
struct  StructTraits<::test::echo_import::mojom::Point::DataView,
                                         ::test::echo_import::mojom::PointPtr> {
  static bool IsNull(const ::test::echo_import::mojom::PointPtr& input) { return !input; }
  static void SetToNull(::test::echo_import::mojom::PointPtr* output) { output->reset(); }

  static decltype(::test::echo_import::mojom::Point::x) x(
      const ::test::echo_import::mojom::PointPtr& input) {
    return input->x;
  }

  static decltype(::test::echo_import::mojom::Point::y) y(
      const ::test::echo_import::mojom::PointPtr& input) {
    return input->y;
  }

  static bool Read(::test::echo_import::mojom::Point::DataView input, ::test::echo_import::mojom::PointPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_ECHO_IMPORT_ECHO_IMPORT_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTQzOSwgImJlZ2luIjogMTQzNCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogInRlc3QuZWNob19pbXBvcnQubW9qb20uUG9pbnQifX0s
IHsiZW5kIjogNDg5NSwgImJlZ2luIjogNDg5NCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVy
YXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hy
b21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20i
LCAic2lnbmF0dXJlIjogInRlc3QuZWNob19pbXBvcnQubW9qb20uUG9pbnQueCJ9fSwgeyJlbmQi
OiA0OTYyLCAiYmVnaW4iOiA0OTYxLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwg
InR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5n
b29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWdu
YXR1cmUiOiAidGVzdC5lY2hvX2ltcG9ydC5tb2pvbS5Qb2ludC55In19XSwgInR5cGUiOiAia3l0
aGUwIn0=
*/