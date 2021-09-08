// mojo/public/mojom/base/shared_memory.mojom.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_SHARED_MEMORY_MOJOM_H_
#define MOJO_PUBLIC_MOJOM_BASE_SHARED_MEMORY_MOJOM_H_

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
#include "mojo/public/mojom/base/shared_memory.mojom-shared.h"
#include "mojo/public/mojom/base/shared_memory.mojom-forward.h"
#include <string>
#include <vector>

#include "mojo/public/cpp/bindings/associated_interface_ptr_info.h"
#include "mojo/public/cpp/bindings/associated_interface_request.h"
#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "mojo/public/cpp/bindings/interface_request.h"
#include "mojo/public/cpp/bindings/lib/control_message_handler.h"
#include "mojo/public/cpp/bindings/raw_ptr_impl_ref_traits.h"


#include "mojo/public/cpp/base/shared_memory_mojom_traits.h"
#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {










// @generated_from: mojo_base.mojom.ReadOnlySharedMemoryRegion
class COMPONENT_EXPORT(MOJO_BASE_MOJOM) ReadOnlySharedMemoryRegion {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<ReadOnlySharedMemoryRegion, T>::value>;
  using DataView = ReadOnlySharedMemoryRegionDataView;
  using Data_ = internal::ReadOnlySharedMemoryRegion_Data;

  template <typename... Args>
  static ReadOnlySharedMemoryRegionPtr New(Args&&... args) {
    return ReadOnlySharedMemoryRegionPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static ReadOnlySharedMemoryRegionPtr From(const U& u) {
    return mojo::TypeConverter<ReadOnlySharedMemoryRegionPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, ReadOnlySharedMemoryRegion>::Convert(*this);
  }


  ReadOnlySharedMemoryRegion();

  explicit ReadOnlySharedMemoryRegion(
      ::mojo::ScopedSharedBufferHandle buffer);

  ~ReadOnlySharedMemoryRegion();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = ReadOnlySharedMemoryRegionPtr>
  ReadOnlySharedMemoryRegionPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        ReadOnlySharedMemoryRegion::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::ReadOnlySharedMemoryRegion_UnserializedMessageContext<
            UserType, ReadOnlySharedMemoryRegion::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<ReadOnlySharedMemoryRegion::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return ReadOnlySharedMemoryRegion::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::ReadOnlySharedMemoryRegion_UnserializedMessageContext<
            UserType, ReadOnlySharedMemoryRegion::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<ReadOnlySharedMemoryRegion::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.ReadOnlySharedMemoryRegion.buffer
  ::mojo::ScopedSharedBufferHandle buffer;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(ReadOnlySharedMemoryRegion);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}





// @generated_from: mojo_base.mojom.WritableSharedMemoryRegion
class COMPONENT_EXPORT(MOJO_BASE_MOJOM) WritableSharedMemoryRegion {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<WritableSharedMemoryRegion, T>::value>;
  using DataView = WritableSharedMemoryRegionDataView;
  using Data_ = internal::WritableSharedMemoryRegion_Data;

  template <typename... Args>
  static WritableSharedMemoryRegionPtr New(Args&&... args) {
    return WritableSharedMemoryRegionPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static WritableSharedMemoryRegionPtr From(const U& u) {
    return mojo::TypeConverter<WritableSharedMemoryRegionPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, WritableSharedMemoryRegion>::Convert(*this);
  }


  WritableSharedMemoryRegion();

  explicit WritableSharedMemoryRegion(
      ::mojo::ScopedSharedBufferHandle buffer);

  ~WritableSharedMemoryRegion();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = WritableSharedMemoryRegionPtr>
  WritableSharedMemoryRegionPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        WritableSharedMemoryRegion::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::WritableSharedMemoryRegion_UnserializedMessageContext<
            UserType, WritableSharedMemoryRegion::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<WritableSharedMemoryRegion::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return WritableSharedMemoryRegion::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::WritableSharedMemoryRegion_UnserializedMessageContext<
            UserType, WritableSharedMemoryRegion::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<WritableSharedMemoryRegion::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.WritableSharedMemoryRegion.buffer
  ::mojo::ScopedSharedBufferHandle buffer;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(WritableSharedMemoryRegion);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}





// @generated_from: mojo_base.mojom.UnsafeSharedMemoryRegion
class COMPONENT_EXPORT(MOJO_BASE_MOJOM) UnsafeSharedMemoryRegion {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<UnsafeSharedMemoryRegion, T>::value>;
  using DataView = UnsafeSharedMemoryRegionDataView;
  using Data_ = internal::UnsafeSharedMemoryRegion_Data;

  template <typename... Args>
  static UnsafeSharedMemoryRegionPtr New(Args&&... args) {
    return UnsafeSharedMemoryRegionPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static UnsafeSharedMemoryRegionPtr From(const U& u) {
    return mojo::TypeConverter<UnsafeSharedMemoryRegionPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, UnsafeSharedMemoryRegion>::Convert(*this);
  }


  UnsafeSharedMemoryRegion();

  explicit UnsafeSharedMemoryRegion(
      ::mojo::ScopedSharedBufferHandle buffer);

  ~UnsafeSharedMemoryRegion();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = UnsafeSharedMemoryRegionPtr>
  UnsafeSharedMemoryRegionPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        UnsafeSharedMemoryRegion::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::UnsafeSharedMemoryRegion_UnserializedMessageContext<
            UserType, UnsafeSharedMemoryRegion::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<UnsafeSharedMemoryRegion::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const std::vector<uint8_t>& input,
                          UserType* output) {
    return UnsafeSharedMemoryRegion::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::UnsafeSharedMemoryRegion_UnserializedMessageContext<
            UserType, UnsafeSharedMemoryRegion::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<UnsafeSharedMemoryRegion::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.UnsafeSharedMemoryRegion.buffer
  ::mojo::ScopedSharedBufferHandle buffer;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(UnsafeSharedMemoryRegion);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
ReadOnlySharedMemoryRegionPtr ReadOnlySharedMemoryRegion::Clone() const {
  return New(
      mojo::Clone(buffer)
  );
}

template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>*>
bool ReadOnlySharedMemoryRegion::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->buffer, other_struct.buffer))
    return false;
  return true;
}

template <typename T, ReadOnlySharedMemoryRegion::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.buffer < rhs.buffer)
    return true;
  if (rhs.buffer < lhs.buffer)
    return false;
  return false;
}
template <typename StructPtrType>
WritableSharedMemoryRegionPtr WritableSharedMemoryRegion::Clone() const {
  return New(
      mojo::Clone(buffer)
  );
}

template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>*>
bool WritableSharedMemoryRegion::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->buffer, other_struct.buffer))
    return false;
  return true;
}

template <typename T, WritableSharedMemoryRegion::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.buffer < rhs.buffer)
    return true;
  if (rhs.buffer < lhs.buffer)
    return false;
  return false;
}
template <typename StructPtrType>
UnsafeSharedMemoryRegionPtr UnsafeSharedMemoryRegion::Clone() const {
  return New(
      mojo::Clone(buffer)
  );
}

template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>*>
bool UnsafeSharedMemoryRegion::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->buffer, other_struct.buffer))
    return false;
  return true;
}

template <typename T, UnsafeSharedMemoryRegion::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.buffer < rhs.buffer)
    return true;
  if (rhs.buffer < lhs.buffer)
    return false;
  return false;
}


}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM) StructTraits<::mojo_base::mojom::ReadOnlySharedMemoryRegion::DataView,
                                         ::mojo_base::mojom::ReadOnlySharedMemoryRegionPtr> {
  static bool IsNull(const ::mojo_base::mojom::ReadOnlySharedMemoryRegionPtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::ReadOnlySharedMemoryRegionPtr* output) { output->reset(); }

  static  decltype(::mojo_base::mojom::ReadOnlySharedMemoryRegion::buffer)& buffer(
       ::mojo_base::mojom::ReadOnlySharedMemoryRegionPtr& input) {
    return input->buffer;
  }

  static bool Read(::mojo_base::mojom::ReadOnlySharedMemoryRegion::DataView input, ::mojo_base::mojom::ReadOnlySharedMemoryRegionPtr* output);
};


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM) StructTraits<::mojo_base::mojom::WritableSharedMemoryRegion::DataView,
                                         ::mojo_base::mojom::WritableSharedMemoryRegionPtr> {
  static bool IsNull(const ::mojo_base::mojom::WritableSharedMemoryRegionPtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::WritableSharedMemoryRegionPtr* output) { output->reset(); }

  static  decltype(::mojo_base::mojom::WritableSharedMemoryRegion::buffer)& buffer(
       ::mojo_base::mojom::WritableSharedMemoryRegionPtr& input) {
    return input->buffer;
  }

  static bool Read(::mojo_base::mojom::WritableSharedMemoryRegion::DataView input, ::mojo_base::mojom::WritableSharedMemoryRegionPtr* output);
};


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM) StructTraits<::mojo_base::mojom::UnsafeSharedMemoryRegion::DataView,
                                         ::mojo_base::mojom::UnsafeSharedMemoryRegionPtr> {
  static bool IsNull(const ::mojo_base::mojom::UnsafeSharedMemoryRegionPtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::UnsafeSharedMemoryRegionPtr* output) { output->reset(); }

  static  decltype(::mojo_base::mojom::UnsafeSharedMemoryRegion::buffer)& buffer(
       ::mojo_base::mojom::UnsafeSharedMemoryRegionPtr& input) {
    return input->buffer;
  }

  static bool Read(::mojo_base::mojom::UnsafeSharedMemoryRegion::DataView input, ::mojo_base::mojom::UnsafeSharedMemoryRegionPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_MOJOM_BASE_SHARED_MEMORY_MOJOM_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTgzNCwgImJlZ2luIjogMTgwOCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5SZWFkT25seVNoYXJlZE1l
bW9yeVJlZ2lvbiJ9fSwgeyJlbmQiOiA1NjE5LCAiYmVnaW4iOiA1NjEzLCAiZWRnZSI6ICIlL2t5
dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7
ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5n
dWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qb19iYXNlLm1vam9tLlJlYWRPbmx5U2hh
cmVkTWVtb3J5UmVnaW9uLmJ1ZmZlciJ9fSwgeyJlbmQiOiA2ODI2LCAiYmVnaW4iOiA2ODAwLCAi
ZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMi
LCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVt
L3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qb19iYXNlLm1vam9t
LldyaXRhYmxlU2hhcmVkTWVtb3J5UmVnaW9uIn19LCB7ImVuZCI6IDEwNjExLCAiYmVnaW4iOiAx
MDYwNSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9k
ZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9j
aHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFz
ZS5tb2pvbS5Xcml0YWJsZVNoYXJlZE1lbW9yeVJlZ2lvbi5idWZmZXIifX0sIHsiZW5kIjogMTE4
MTQsICJiZWdpbiI6IDExNzkwLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5
cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29n
bGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1
cmUiOiAibW9qb19iYXNlLm1vam9tLlVuc2FmZVNoYXJlZE1lbW9yeVJlZ2lvbiJ9fSwgeyJlbmQi
OiAxNTU1MSwgImJlZ2luIjogMTU1NDUsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMi
LCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVt
Lmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNp
Z25hdHVyZSI6ICJtb2pvX2Jhc2UubW9qb20uVW5zYWZlU2hhcmVkTWVtb3J5UmVnaW9uLmJ1ZmZl
ciJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/