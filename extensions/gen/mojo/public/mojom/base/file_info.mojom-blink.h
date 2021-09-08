// mojo/public/mojom/base/file_info.mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_FILE_INFO_MOJOM_BLINK_H_
#define MOJO_PUBLIC_MOJOM_BASE_FILE_INFO_MOJOM_BLINK_H_

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
#include "mojo/public/mojom/base/file_info.mojom-shared.h"
#include "mojo/public/mojom/base/file_info.mojom-blink-forward.h"
#include "mojo/public/mojom/base/time.mojom-blink.h"

#include "mojo/public/cpp/bindings/lib/wtf_clone_equals_util.h"
#include "mojo/public/cpp/bindings/lib/wtf_hash_util.h"
#include "third_party/blink/renderer/platform/wtf/hash_functions.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"




#include "mojo/public/cpp/base/file_info_mojom_traits.h"
#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {
namespace blink {








// @generated_from: mojo_base.mojom.FileInfo
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) FileInfo {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<FileInfo, T>::value>;
  using DataView = FileInfoDataView;
  using Data_ = internal::FileInfo_Data;

  template <typename... Args>
  static FileInfoPtr New(Args&&... args) {
    return FileInfoPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static FileInfoPtr From(const U& u) {
    return mojo::TypeConverter<FileInfoPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, FileInfo>::Convert(*this);
  }


  FileInfo();

  FileInfo(
      int64_t size,
      bool is_directory,
      bool is_symbolic_link,
      ::base::Time last_modified,
      ::base::Time last_accessed,
      ::base::Time creation_time);

  ~FileInfo();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = FileInfoPtr>
  FileInfoPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, FileInfo::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, FileInfo::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  template <typename UserType>
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        FileInfo::DataView, WTF::Vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        FileInfo::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::FileInfo_UnserializedMessageContext<
            UserType, FileInfo::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<FileInfo::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return FileInfo::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::FileInfo_UnserializedMessageContext<
            UserType, FileInfo::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<FileInfo::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.FileInfo.size
  int64_t size;
  
// @generated_from: mojo_base.mojom.FileInfo.is_directory
  bool is_directory;
  
// @generated_from: mojo_base.mojom.FileInfo.is_symbolic_link
  bool is_symbolic_link;
  
// @generated_from: mojo_base.mojom.FileInfo.last_modified
  ::base::Time last_modified;
  
// @generated_from: mojo_base.mojom.FileInfo.last_accessed
  ::base::Time last_accessed;
  
// @generated_from: mojo_base.mojom.FileInfo.creation_time
  ::base::Time creation_time;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, FileInfo::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, FileInfo::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, FileInfo::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, FileInfo::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename StructPtrType>
FileInfoPtr FileInfo::Clone() const {
  return New(
      mojo::Clone(size),
      mojo::Clone(is_directory),
      mojo::Clone(is_symbolic_link),
      mojo::Clone(last_modified),
      mojo::Clone(last_accessed),
      mojo::Clone(creation_time)
  );
}

template <typename T, FileInfo::EnableIfSame<T>*>
bool FileInfo::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->size, other_struct.size))
    return false;
  if (!mojo::Equals(this->is_directory, other_struct.is_directory))
    return false;
  if (!mojo::Equals(this->is_symbolic_link, other_struct.is_symbolic_link))
    return false;
  if (!mojo::Equals(this->last_modified, other_struct.last_modified))
    return false;
  if (!mojo::Equals(this->last_accessed, other_struct.last_accessed))
    return false;
  if (!mojo::Equals(this->creation_time, other_struct.creation_time))
    return false;
  return true;
}

template <typename T, FileInfo::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.size < rhs.size)
    return true;
  if (rhs.size < lhs.size)
    return false;
  if (lhs.is_directory < rhs.is_directory)
    return true;
  if (rhs.is_directory < lhs.is_directory)
    return false;
  if (lhs.is_symbolic_link < rhs.is_symbolic_link)
    return true;
  if (rhs.is_symbolic_link < lhs.is_symbolic_link)
    return false;
  if (lhs.last_modified < rhs.last_modified)
    return true;
  if (rhs.last_modified < lhs.last_modified)
    return false;
  if (lhs.last_accessed < rhs.last_accessed)
    return true;
  if (rhs.last_accessed < lhs.last_accessed)
    return false;
  if (lhs.creation_time < rhs.creation_time)
    return true;
  if (rhs.creation_time < lhs.creation_time)
    return false;
  return false;
}


}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) StructTraits<::mojo_base::mojom::blink::FileInfo::DataView,
                                         ::mojo_base::mojom::blink::FileInfoPtr> {
  static bool IsNull(const ::mojo_base::mojom::blink::FileInfoPtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::blink::FileInfoPtr* output) { output->reset(); }

  static decltype(::mojo_base::mojom::blink::FileInfo::size) size(
      const ::mojo_base::mojom::blink::FileInfoPtr& input) {
    return input->size;
  }

  static decltype(::mojo_base::mojom::blink::FileInfo::is_directory) is_directory(
      const ::mojo_base::mojom::blink::FileInfoPtr& input) {
    return input->is_directory;
  }

  static decltype(::mojo_base::mojom::blink::FileInfo::is_symbolic_link) is_symbolic_link(
      const ::mojo_base::mojom::blink::FileInfoPtr& input) {
    return input->is_symbolic_link;
  }

  static const decltype(::mojo_base::mojom::blink::FileInfo::last_modified)& last_modified(
      const ::mojo_base::mojom::blink::FileInfoPtr& input) {
    return input->last_modified;
  }

  static const decltype(::mojo_base::mojom::blink::FileInfo::last_accessed)& last_accessed(
      const ::mojo_base::mojom::blink::FileInfoPtr& input) {
    return input->last_accessed;
  }

  static const decltype(::mojo_base::mojom::blink::FileInfo::creation_time)& creation_time(
      const ::mojo_base::mojom::blink::FileInfoPtr& input) {
    return input->creation_time;
  }

  static bool Read(::mojo_base::mojom::blink::FileInfo::DataView input, ::mojo_base::mojom::blink::FileInfoPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_MOJOM_BASE_FILE_INFO_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTcyNSwgImJlZ2luIjogMTcxNywgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5GaWxlSW5mbyJ9fSwgeyJl
bmQiOiA1MzYzLCAiYmVnaW4iOiA1MzU5LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9qb19iYXNlLm1vam9tLkZpbGVJbmZvLnNpemUifX0sIHsiZW5kIjogNTQ0
NSwgImJlZ2luIjogNTQzMywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBl
IjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xl
c291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJl
IjogIm1vam9fYmFzZS5tb2pvbS5GaWxlSW5mby5pc19kaXJlY3RvcnkifX0sIHsiZW5kIjogNTUz
NSwgImJlZ2luIjogNTUxOSwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBl
IjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xl
c291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJl
IjogIm1vam9fYmFzZS5tb2pvbS5GaWxlSW5mby5pc19zeW1ib2xpY19saW5rIn19LCB7ImVuZCI6
IDU2MjcsICJiZWdpbiI6IDU2MTQsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2pvX2Jhc2UubW9qb20uRmlsZUluZm8ubGFzdF9tb2RpZmllZCJ9fSwgeyJlbmQi
OiA1NzE5LCAiYmVnaW4iOiA1NzA2LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwg
InR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5n
b29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWdu
YXR1cmUiOiAibW9qb19iYXNlLm1vam9tLkZpbGVJbmZvLmxhc3RfYWNjZXNzZWQifX0sIHsiZW5k
IjogNTgxMSwgImJlZ2luIjogNTc5OCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIs
ICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0u
Z29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2ln
bmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5GaWxlSW5mby5jcmVhdGlvbl90aW1lIn19XSwgInR5
cGUiOiAia3l0aGUwIn0=
*/