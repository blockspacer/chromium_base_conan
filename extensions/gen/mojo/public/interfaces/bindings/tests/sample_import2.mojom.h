// mojo/public/interfaces/bindings/tests/sample_import2.mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT2_MOJOM_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT2_MOJOM_H_

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
#include "mojo/public/interfaces/bindings/tests/sample_import2.mojom-shared.h"
#include "mojo/public/interfaces/bindings/tests/sample_import2.mojom-forward.h"
#include "mojo/public/interfaces/bindings/tests/sample_import.mojom.h"
#include <string>
#include <vector>





#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace imported {





// @generated_from: imported.Size
class  Size {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Size, T>::value>;
  using DataView = SizeDataView;
  using Data_ = internal::Size_Data;

  template <typename... Args>
  static SizePtr New(Args&&... args) {
    return SizePtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static SizePtr From(const U& u) {
    return mojo::TypeConverter<SizePtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Size>::Convert(*this);
  }


  Size();

  Size(
      int32_t width,
      int32_t height);

  ~Size();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = SizePtr>
  SizePtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Size::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Size::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        Size::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Size::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Size_UnserializedMessageContext<
            UserType, Size::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Size::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return Size::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Size_UnserializedMessageContext<
            UserType, Size::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Size::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: imported.Size.width
  int32_t width;
  
// @generated_from: imported.Size.height
  int32_t height;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Size::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Size::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Size::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Size::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}









// @generated_from: imported.Thing
class  Thing {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Thing, T>::value>;
  using DataView = ThingDataView;
  using Data_ = internal::Thing_Data;

  template <typename... Args>
  static ThingPtr New(Args&&... args) {
    return ThingPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static ThingPtr From(const U& u) {
    return mojo::TypeConverter<ThingPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Thing>::Convert(*this);
  }


  Thing();

  Thing(
      ::imported::Shape shape,
      Color color,
      ::imported::PointPtr location,
      SizePtr size);

  ~Thing();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = ThingPtr>
  ThingPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Thing::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Thing::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static std::vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        Thing::DataView, std::vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Thing::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Thing_UnserializedMessageContext<
            UserType, Thing::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Thing::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return Thing::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Thing_UnserializedMessageContext<
            UserType, Thing::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Thing::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: imported.Thing.shape
  ::imported::Shape shape;
  
// @generated_from: imported.Thing.color
  Color color;
  
// @generated_from: imported.Thing.location
  ::imported::PointPtr location;
  
// @generated_from: imported.Thing.size
  SizePtr size;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(Thing);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Thing::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Thing::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Thing::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Thing::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
SizePtr Size::Clone() const {
  return New(
      mojo::Clone(width),
      mojo::Clone(height)
  );
}

template <typename T, Size::EnableIfSame<T>*>
bool Size::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->width, other_struct.width))
    return false;
  if (!mojo::Equals(this->height, other_struct.height))
    return false;
  return true;
}

template <typename T, Size::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.width < rhs.width)
    return true;
  if (rhs.width < lhs.width)
    return false;
  if (lhs.height < rhs.height)
    return true;
  if (rhs.height < lhs.height)
    return false;
  return false;
}
template <typename StructPtrType>
ThingPtr Thing::Clone() const {
  return New(
      mojo::Clone(shape),
      mojo::Clone(color),
      mojo::Clone(location),
      mojo::Clone(size)
  );
}

template <typename T, Thing::EnableIfSame<T>*>
bool Thing::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->shape, other_struct.shape))
    return false;
  if (!mojo::Equals(this->color, other_struct.color))
    return false;
  if (!mojo::Equals(this->location, other_struct.location))
    return false;
  if (!mojo::Equals(this->size, other_struct.size))
    return false;
  return true;
}

template <typename T, Thing::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.shape < rhs.shape)
    return true;
  if (rhs.shape < lhs.shape)
    return false;
  if (lhs.color < rhs.color)
    return true;
  if (rhs.color < lhs.color)
    return false;
  if (lhs.location < rhs.location)
    return true;
  if (rhs.location < lhs.location)
    return false;
  if (lhs.size < rhs.size)
    return true;
  if (rhs.size < lhs.size)
    return false;
  return false;
}


}  // namespace imported

namespace mojo {


template <>
struct  StructTraits<::imported::Size::DataView,
                                         ::imported::SizePtr> {
  static bool IsNull(const ::imported::SizePtr& input) { return !input; }
  static void SetToNull(::imported::SizePtr* output) { output->reset(); }

  static decltype(::imported::Size::width) width(
      const ::imported::SizePtr& input) {
    return input->width;
  }

  static decltype(::imported::Size::height) height(
      const ::imported::SizePtr& input) {
    return input->height;
  }

  static bool Read(::imported::Size::DataView input, ::imported::SizePtr* output);
};


template <>
struct  StructTraits<::imported::Thing::DataView,
                                         ::imported::ThingPtr> {
  static bool IsNull(const ::imported::ThingPtr& input) { return !input; }
  static void SetToNull(::imported::ThingPtr* output) { output->reset(); }

  static decltype(::imported::Thing::shape) shape(
      const ::imported::ThingPtr& input) {
    return input->shape;
  }

  static decltype(::imported::Thing::color) color(
      const ::imported::ThingPtr& input) {
    return input->color;
  }

  static const decltype(::imported::Thing::location)& location(
      const ::imported::ThingPtr& input) {
    return input->location;
  }

  static const decltype(::imported::Thing::size)& size(
      const ::imported::ThingPtr& input) {
    return input->size;
  }

  static bool Read(::imported::Thing::DataView input, ::imported::ThingPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT2_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTQxMSwgImJlZ2luIjogMTQwNywgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogImltcG9ydGVkLlNpemUifX0sIHsiZW5kIjogNDg0NSwg
ImJlZ2luIjogNDg0MCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjog
ImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291
cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjog
ImltcG9ydGVkLlNpemUud2lkdGgifX0sIHsiZW5kIjogNDkwNywgImJlZ2luIjogNDkwMSwgImVk
Z2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwg
InZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9z
cmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogImltcG9ydGVkLlNpemUuaGVp
Z2h0In19LCB7ImVuZCI6IDU4OTIsICJiZWdpbiI6IDU4ODcsICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJpbXBvcnRlZC5UaGluZyJ9fSwgeyJlbmQiOiA5NDE5LCAi
YmVnaW4iOiA5NDE0LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAi
YW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3Vy
Y2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAi
aW1wb3J0ZWQuVGhpbmcuc2hhcGUifX0sIHsiZW5kIjogOTQ3OCwgImJlZ2luIjogOTQ3MywgImVk
Z2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwg
InZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9z
cmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogImltcG9ydGVkLlRoaW5nLmNv
bG9yIn19LCB7ImVuZCI6IDk1NjQsICJiZWdpbiI6IDk1NTYsICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJpbXBvcnRlZC5UaGluZy5sb2NhdGlvbiJ9fSwgeyJlbmQi
OiA5NjE4LCAiYmVnaW4iOiA5NjExLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwg
InR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5n
b29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWdu
YXR1cmUiOiAiaW1wb3J0ZWQuVGhpbmcuc2l6ZSJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/