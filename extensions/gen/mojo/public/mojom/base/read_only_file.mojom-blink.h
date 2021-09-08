// mojo/public/mojom/base/read_only_file.mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_READ_ONLY_FILE_MOJOM_BLINK_H_
#define MOJO_PUBLIC_MOJOM_BASE_READ_ONLY_FILE_MOJOM_BLINK_H_

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
#include "mojo/public/mojom/base/read_only_file.mojom-shared.h"
#include "mojo/public/mojom/base/read_only_file.mojom-blink-forward.h"

#include "mojo/public/cpp/bindings/lib/wtf_clone_equals_util.h"
#include "mojo/public/cpp/bindings/lib/wtf_hash_util.h"
#include "third_party/blink/renderer/platform/wtf/hash_functions.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

#include "mojo/public/cpp/bindings/associated_interface_ptr_info.h"
#include "mojo/public/cpp/bindings/associated_interface_request.h"
#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "mojo/public/cpp/bindings/interface_request.h"
#include "mojo/public/cpp/bindings/lib/control_message_handler.h"
#include "mojo/public/cpp/bindings/raw_ptr_impl_ref_traits.h"


#include "mojo/public/cpp/base/read_only_file_mojom_traits.h"
#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {
namespace blink {








// @generated_from: mojo_base.mojom.ReadOnlyFile
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) ReadOnlyFile {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<ReadOnlyFile, T>::value>;
  using DataView = ReadOnlyFileDataView;
  using Data_ = internal::ReadOnlyFile_Data;

  template <typename... Args>
  static ReadOnlyFilePtr New(Args&&... args) {
    return ReadOnlyFilePtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static ReadOnlyFilePtr From(const U& u) {
    return mojo::TypeConverter<ReadOnlyFilePtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, ReadOnlyFile>::Convert(*this);
  }


  ReadOnlyFile();

  ReadOnlyFile(
      ::mojo::PlatformHandle fd,
      bool async);

  ~ReadOnlyFile();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = ReadOnlyFilePtr>
  ReadOnlyFilePtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, ReadOnlyFile::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, ReadOnlyFile::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        ReadOnlyFile::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::ReadOnlyFile_UnserializedMessageContext<
            UserType, ReadOnlyFile::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<ReadOnlyFile::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return ReadOnlyFile::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::ReadOnlyFile_UnserializedMessageContext<
            UserType, ReadOnlyFile::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<ReadOnlyFile::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.ReadOnlyFile.fd
  ::mojo::PlatformHandle fd;
  
// @generated_from: mojo_base.mojom.ReadOnlyFile.async
  bool async;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(ReadOnlyFile);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, ReadOnlyFile::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, ReadOnlyFile::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, ReadOnlyFile::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, ReadOnlyFile::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
ReadOnlyFilePtr ReadOnlyFile::Clone() const {
  return New(
      mojo::Clone(fd),
      mojo::Clone(async)
  );
}

template <typename T, ReadOnlyFile::EnableIfSame<T>*>
bool ReadOnlyFile::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->fd, other_struct.fd))
    return false;
  if (!mojo::Equals(this->async, other_struct.async))
    return false;
  return true;
}

template <typename T, ReadOnlyFile::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.fd < rhs.fd)
    return true;
  if (rhs.fd < lhs.fd)
    return false;
  if (lhs.async < rhs.async)
    return true;
  if (rhs.async < lhs.async)
    return false;
  return false;
}


}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) StructTraits<::mojo_base::mojom::blink::ReadOnlyFile::DataView,
                                         ::mojo_base::mojom::blink::ReadOnlyFilePtr> {
  static bool IsNull(const ::mojo_base::mojom::blink::ReadOnlyFilePtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::blink::ReadOnlyFilePtr* output) { output->reset(); }

  static  decltype(::mojo_base::mojom::blink::ReadOnlyFile::fd)& fd(
       ::mojo_base::mojom::blink::ReadOnlyFilePtr& input) {
    return input->fd;
  }

  static decltype(::mojo_base::mojom::blink::ReadOnlyFile::async) async(
      const ::mojo_base::mojom::blink::ReadOnlyFilePtr& input) {
    return input->async;
  }

  static bool Read(::mojo_base::mojom::blink::ReadOnlyFile::DataView input, ::mojo_base::mojom::blink::ReadOnlyFilePtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_MOJOM_BASE_READ_ONLY_FILE_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjA4MCwgImJlZ2luIjogMjA2OCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5SZWFkT25seUZpbGUifX0s
IHsiZW5kIjogNTUwNiwgImJlZ2luIjogNTUwNCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVy
YXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hy
b21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20i
LCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5SZWFkT25seUZpbGUuZmQifX0sIHsiZW5k
IjogNTU3OCwgImJlZ2luIjogNTU3MywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5SZWFkT25seUZpbGUuYXN5bmMifX1dLCAidHlwZSI6
ICJreXRoZTAifQ==
*/