// mojo/public/interfaces/bindings/tests/test_associated_interfaces.mojom-shared-internal.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_SHARED_INTERNAL_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_SHARED_INTERNAL_H_

#include "mojo/public/cpp/bindings/lib/array_internal.h"
#include "mojo/public/cpp/bindings/lib/bindings_internal.h"
#include "mojo/public/cpp/bindings/lib/map_data_internal.h"
#include "mojo/public/cpp/bindings/lib/buffer.h"
#include "mojo/public/interfaces/bindings/tests/ping_service.mojom-shared-internal.h"
#include "mojo/public/cpp/bindings/lib/native_enum_data.h"
#include "mojo/public/interfaces/bindings/native_struct.mojom-shared-internal.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif

namespace mojo {
namespace internal {
class ValidationContext;
}
}
namespace mojo {
namespace test {
namespace internal {
class StructContainsAssociated_Data;
class UnionContainsAssociated_Data;

#pragma pack(push, 1)


class  UnionContainsAssociated_Data {
 public:
  // Used to identify Mojom Union Data Classes.
  typedef void MojomUnionDataType;

  UnionContainsAssociated_Data() {}
  // Do nothing in the destructor since it won't be called when it is a
  // non-inlined union.
  ~UnionContainsAssociated_Data() {}

  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context,
                       bool inlined);

  bool is_null() const { return size == 0; }

  void set_null() {
    size = 0U;
    tag = static_cast<UnionContainsAssociated_Tag>(0);
    data.unknown = 0U;
  }

  // TODO(crbug.com/1148486): SHOUTY_CASE values are being deprecated per C++ code style
  // guidelines (https://google.github.io/styleguide/cppguide.html#Enumerator_Names),
  // please use kCamelCase values instead.  Cleanup NULL_VALUE, BOOL_VALUE, INT_VALUE, etc.
  // generation once codebase is transitioned to kNullValue, kBoolValue, kIntValue, etc.
  enum class UnionContainsAssociated_Tag : uint32_t {

    
// @generated_from: mojo.test.UnionContainsAssociated.foo_remote
    FOO_REMOTE,
    
// @generated_from: mojo.test.UnionContainsAssociated.foo_remote
    kFooRemote = FOO_REMOTE,
    
// @generated_from: mojo.test.UnionContainsAssociated.foo_receiver
    FOO_RECEIVER,
    
// @generated_from: mojo.test.UnionContainsAssociated.foo_receiver
    kFooReceiver = FOO_RECEIVER,
    
// @generated_from: mojo.test.UnionContainsAssociated.foo_remotes
    FOO_REMOTES,
    
// @generated_from: mojo.test.UnionContainsAssociated.foo_remotes
    kFooRemotes = FOO_REMOTES,
    
// @generated_from: mojo.test.UnionContainsAssociated.foo_receivers
    FOO_RECEIVERS,
    
// @generated_from: mojo.test.UnionContainsAssociated.foo_receivers
    kFooReceivers = FOO_RECEIVERS,
  };

  // A note on layout:
  // "Each non-static data member is allocated as if it were the sole member of
  // a struct." - Section 9.5.2 ISO/IEC 14882:2011 (The C++ Spec)
  union MOJO_ALIGNAS(8) Union_ {
    Union_() : unknown(0) {}
    mojo::internal::AssociatedInterface_Data f_foo_remote;
    mojo::internal::AssociatedEndpointHandle_Data f_foo_receiver;
    mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::AssociatedInterface_Data>> f_foo_remotes;
    mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::AssociatedEndpointHandle_Data>> f_foo_receivers;
    uint64_t unknown;
  };

  uint32_t size;
  UnionContainsAssociated_Tag tag;
  Union_ data;
};
static_assert(sizeof(UnionContainsAssociated_Data) == mojo::internal::kUnionDataSize,
              "Bad sizeof(UnionContainsAssociated_Data)");
class  StructContainsAssociated_Data {
 public:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  mojo::internal::StructHeader header_;
  mojo::internal::AssociatedInterface_Data foo_remote;
  mojo::internal::AssociatedEndpointHandle_Data foo_receiver;
  uint8_t pad1_[4];
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::AssociatedInterface_Data>> foo_remotes;
  mojo::internal::Pointer<mojo::internal::Array_Data<mojo::internal::AssociatedEndpointHandle_Data>> foo_receivers;

 private:
  friend class mojo::internal::MessageFragment<StructContainsAssociated_Data>;

  StructContainsAssociated_Data();
  ~StructContainsAssociated_Data() = delete;
};
static_assert(sizeof(StructContainsAssociated_Data) == 40,
              "Bad sizeof(StructContainsAssociated_Data)");
// Used by StructContainsAssociated::WrapAsMessage to lazily serialize the struct.
template <typename UserType, typename DataView>
struct StructContainsAssociated_UnserializedMessageContext
    : public mojo::internal::UnserializedMessageContext {
 public:
  static const mojo::internal::UnserializedMessageContext::Tag kMessageTag;

  StructContainsAssociated_UnserializedMessageContext(
    uint32_t message_name,
    uint32_t message_flags,
    UserType input)
      : mojo::internal::UnserializedMessageContext(&kMessageTag, message_name, message_flags)
      , user_data_(std::move(input)) {}
  ~StructContainsAssociated_UnserializedMessageContext() override = default;

  UserType TakeData() {
    return std::move(user_data_);
  }

 private:
  // mojo::internal::UnserializedMessageContext:
  void Serialize(mojo::Message& message) override {
    mojo::internal::MessageFragment<StructContainsAssociated_Data> fragment(message);
    mojo::internal::Serialize<DataView>(user_data_, fragment);
  }

  UserType user_data_;
};

template <typename UserType, typename DataView>
const mojo::internal::UnserializedMessageContext::Tag
    StructContainsAssociated_UnserializedMessageContext<UserType, DataView>::kMessageTag = {};

#pragma pack(pop)

}  // namespace internal
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_SHARED_INTERNAL_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMjM5MCwgImJlZ2luIjogMjM4MCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5VbmlvbkNvbnRhaW5zQXNzb2NpYXRl
ZC5mb29fcmVtb3RlIn19LCB7ImVuZCI6IDI0ODksICJiZWdpbiI6IDI0NzksICJlZGdlIjogIiUv
a3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6
IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxh
bmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuVW5pb25Db250YWluc0Fz
c29jaWF0ZWQuZm9vX3JlbW90ZSJ9fSwgeyJlbmQiOiAyNTc5LCAiYmVnaW4iOiAyNTY3LCAiZWRn
ZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAi
dm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3Ny
YyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LlVuaW9uQ29u
dGFpbnNBc3NvY2lhdGVkLmZvb19yZWNlaXZlciJ9fSwgeyJlbmQiOiAyNjg0LCAiYmVnaW4iOiAy
NjcyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2Rl
ZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2No
cm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0
LlVuaW9uQ29udGFpbnNBc3NvY2lhdGVkLmZvb19yZWNlaXZlciJ9fSwgeyJlbmQiOiAyNzcyLCAi
YmVnaW4iOiAyNzYxLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAi
YW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3Vy
Y2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAi
bW9qby50ZXN0LlVuaW9uQ29udGFpbnNBc3NvY2lhdGVkLmZvb19yZW1vdGVzIn19LCB7ImVuZCI6
IDI4NzQsICJiZWdpbiI6IDI4NjMsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2pvLnRlc3QuVW5pb25Db250YWluc0Fzc29jaWF0ZWQuZm9vX3JlbW90ZXMifX0s
IHsiZW5kIjogMjk2NiwgImJlZ2luIjogMjk1MywgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVy
YXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hy
b21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20i
LCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5VbmlvbkNvbnRhaW5zQXNzb2NpYXRlZC5mb29fcmVj
ZWl2ZXJzIn19LCB7ImVuZCI6IDMwNzQsICJiZWdpbiI6IDMwNjEsICJlZGdlIjogIiUva3l0aGUv
ZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29y
cHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdl
IjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuVW5pb25Db250YWluc0Fzc29jaWF0
ZWQuZm9vX3JlY2VpdmVycyJ9fV0sICJ0eXBlIjogImt5dGhlMCJ9
*/