// mojo/public/interfaces/bindings/tests/test_data_view.mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_DATA_VIEW_MOJOM_BLINK_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_DATA_VIEW_MOJOM_BLINK_H_

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
#include "mojo/public/interfaces/bindings/tests/test_data_view.mojom-shared.h"
#include "mojo/public/interfaces/bindings/tests/test_data_view.mojom-blink-forward.h"

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


#include "mojo/public/cpp/bindings/lib/native_enum_serialization.h"
#include "mojo/public/cpp/bindings/lib/native_struct_serialization.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace WTF {
struct mojo_test_data_view_internal_TestEnum_DataHashFn {
  static unsigned GetHash(const ::mojo::test::data_view::TestEnum& value) {
    using utype = std::underlying_type<::mojo::test::data_view::TestEnum>::type;
    return DefaultHash<utype>::Hash().GetHash(static_cast<utype>(value));
  }
  static bool Equal(const ::mojo::test::data_view::TestEnum& left, const ::mojo::test::data_view::TestEnum& right) {
    return left == right;
  }
  static const bool safe_to_compare_to_empty_or_deleted = true;
};

template <>
struct HashTraits<::mojo::test::data_view::TestEnum>
    : public GenericHashTraits<::mojo::test::data_view::TestEnum> {
  static_assert(true,
                "-1000000 is a reserved enum value");
  static_assert(true,
                "-1000001 is a reserved enum value");
  static const bool hasIsEmptyValueFunction = true;
  static bool IsEmptyValue(const ::mojo::test::data_view::TestEnum& value) {
    return value == static_cast<::mojo::test::data_view::TestEnum>(-1000000);
  }
  static void ConstructDeletedValue(::mojo::test::data_view::TestEnum& slot, bool) {
    slot = static_cast<::mojo::test::data_view::TestEnum>(-1000001);
  }
  static bool IsDeletedValue(const ::mojo::test::data_view::TestEnum& value) {
    return value == static_cast<::mojo::test::data_view::TestEnum>(-1000001);
  }
};
}  // namespace WTF


namespace mojo {
namespace test {
namespace data_view {
namespace blink {

class TestInterfaceProxy;

template <typename ImplRefTraits>
class TestInterfaceStub;

class TestInterfaceRequestValidator;
class TestInterfaceResponseValidator;


// @generated_from: mojo.test.data_view.TestInterface
class  TestInterface
    : public TestInterfaceInterfaceBase {
 public:
  static const char Name_[];
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasSyncMethods_ = true;

  using Base_ = TestInterfaceInterfaceBase;
  using Proxy_ = TestInterfaceProxy;

  template <typename ImplRefTraits>
  using Stub_ = TestInterfaceStub<ImplRefTraits>;

  using RequestValidator_ = TestInterfaceRequestValidator;
  using ResponseValidator_ = TestInterfaceResponseValidator;
  enum MethodMinVersions : uint32_t {
    kEchoMinVersion = 0,
  };
  virtual ~TestInterface() {}

  // Sync method. This signature is used by the client side; the service side
  // should implement the signature with callback below.
  
// @generated_from: mojo.test.data_view.TestInterface.Echo
  virtual bool Echo(int32_t value, int32_t* out_out_value);

  using EchoCallback = base::OnceCallback<void(int32_t)>;
  
// @generated_from: mojo.test.data_view.TestInterface.Echo
  virtual void Echo(int32_t value, EchoCallback callback) = 0;
};



// @generated_from: mojo.test.data_view.TestInterface
class  TestInterfaceProxy
    : public TestInterface {
 public:
  using InterfaceType = TestInterface;

  explicit TestInterfaceProxy(mojo::MessageReceiverWithResponder* receiver);
  
// @generated_from: mojo.test.data_view.TestInterface.Echo
  bool Echo(int32_t value, int32_t* out_out_value) final;
  
// @generated_from: mojo.test.data_view.TestInterface.Echo
  void Echo(int32_t value, EchoCallback callback) final;

 private:
  mojo::MessageReceiverWithResponder* receiver_;
};
class  TestInterfaceStubDispatch {
 public:
  static bool Accept(TestInterface* impl, mojo::Message* message);
  static bool AcceptWithResponder(
      TestInterface* impl,
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder);
};

template <typename ImplRefTraits =
              mojo::RawPtrImplRefTraits<TestInterface>>
class TestInterfaceStub
    : public mojo::MessageReceiverWithResponderStatus {
 public:
  using ImplPointerType = typename ImplRefTraits::PointerType;

  TestInterfaceStub() {}
  ~TestInterfaceStub() override {}

  void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
  ImplPointerType& sink() { return sink_; }

  bool Accept(mojo::Message* message) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return TestInterfaceStubDispatch::Accept(
        ImplRefTraits::GetRawPointer(&sink_), message);
  }

  bool AcceptWithResponder(
      mojo::Message* message,
      std::unique_ptr<mojo::MessageReceiverWithStatus> responder) override {
    if (ImplRefTraits::IsNull(sink_))
      return false;
    return TestInterfaceStubDispatch::AcceptWithResponder(
        ImplRefTraits::GetRawPointer(&sink_), message, std::move(responder));
  }

 private:
  ImplPointerType sink_;
};
class  TestInterfaceRequestValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};
class  TestInterfaceResponseValidator : public mojo::MessageReceiver {
 public:
  bool Accept(mojo::Message* message) override;
};





// @generated_from: mojo.test.data_view.NestedStruct
class  NestedStruct {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<NestedStruct, T>::value>;
  using DataView = NestedStructDataView;
  using Data_ = internal::NestedStruct_Data;

  template <typename... Args>
  static NestedStructPtr New(Args&&... args) {
    return NestedStructPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static NestedStructPtr From(const U& u) {
    return mojo::TypeConverter<NestedStructPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, NestedStruct>::Convert(*this);
  }


  NestedStruct();

  explicit NestedStruct(
      int32_t f_int32);

  ~NestedStruct();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = NestedStructPtr>
  NestedStructPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, NestedStruct::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, NestedStruct::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;
  template <typename UserType>
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        NestedStruct::DataView, WTF::Vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        NestedStruct::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::NestedStruct_UnserializedMessageContext<
            UserType, NestedStruct::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<NestedStruct::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return NestedStruct::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::NestedStruct_UnserializedMessageContext<
            UserType, NestedStruct::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<NestedStruct::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo.test.data_view.NestedStruct.f_int32
  int32_t f_int32;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, NestedStruct::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, NestedStruct::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, NestedStruct::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, NestedStruct::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}







// @generated_from: mojo.test.data_view.TestUnion
class  TestUnion {
 public:
  using DataView = TestUnionDataView;
  using Data_ = internal::TestUnion_Data;
  using Tag = Data_::TestUnion_Tag;

  static TestUnionPtr New() {
    return TestUnionPtr(base::in_place);
  }
  // Construct an instance holding |f_bool|.
  static TestUnionPtr
  NewFBool(
      bool f_bool) {
    auto result = TestUnionPtr(base::in_place);
    result->set_f_bool(std::move(f_bool));
    return result;
  }
  // Construct an instance holding |f_int32|.
  static TestUnionPtr
  NewFInt32(
      int32_t f_int32) {
    auto result = TestUnionPtr(base::in_place);
    result->set_f_int32(std::move(f_int32));
    return result;
  }

  template <typename U>
  static TestUnionPtr From(const U& u) {
    return mojo::TypeConverter<TestUnionPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TestUnion>::Convert(*this);
  }

  TestUnion();
  ~TestUnion();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename UnionPtrType = TestUnionPtr>
  TestUnionPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T,
            typename std::enable_if<std::is_same<
                T, TestUnion>::value>::type* = nullptr>
  bool Equals(const T& other) const;

  template <typename T,
            typename std::enable_if<std::is_same<
                T, TestUnion>::value>::type* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  size_t Hash(size_t seed) const;

  Tag which() const {
    return tag_;
  }


  
// @generated_from: mojo.test.data_view.TestUnion.f_bool
  bool is_f_bool() const { return tag_ == Tag::F_BOOL; }

  
// @generated_from: mojo.test.data_view.TestUnion.f_bool
  bool get_f_bool() const {
    DCHECK(tag_ == Tag::F_BOOL);
    return data_.f_bool;
  }

  
// @generated_from: mojo.test.data_view.TestUnion.f_bool
  void set_f_bool(
      bool f_bool);
  
// @generated_from: mojo.test.data_view.TestUnion.f_int32
  bool is_f_int32() const { return tag_ == Tag::F_INT32; }

  
// @generated_from: mojo.test.data_view.TestUnion.f_int32
  int32_t get_f_int32() const {
    DCHECK(tag_ == Tag::F_INT32);
    return data_.f_int32;
  }

  
// @generated_from: mojo.test.data_view.TestUnion.f_int32
  void set_f_int32(
      int32_t f_int32);

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TestUnion::DataView>(input);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    return mojo::internal::DeserializeImpl<TestUnion::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

 private:
  union Union_ {
    Union_() {}
    ~Union_() {}
    bool f_bool;
    int32_t f_int32;
  };

  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);

  void DestroyActive();
  Tag tag_;
  Union_ data_;
};







// @generated_from: mojo.test.data_view.TestStruct
class  TestStruct {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<TestStruct, T>::value>;
  using DataView = TestStructDataView;
  using Data_ = internal::TestStruct_Data;

  template <typename... Args>
  static TestStructPtr New(Args&&... args) {
    return TestStructPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TestStructPtr From(const U& u) {
    return mojo::TypeConverter<TestStructPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TestStruct>::Convert(*this);
  }


  TestStruct();

  TestStruct(
      const WTF::String& f_string,
      NestedStructPtr f_struct,
      TestNativeStructPtr f_native_struct,
      WTF::Vector<bool> f_bool_array,
      WTF::Vector<int32_t> f_int32_array,
      WTF::Vector<TestEnum> f_enum_array,
      WTF::Vector<::mojo::PendingRemote<TestInterface>> f_interface_array,
      WTF::Vector<WTF::Vector<int32_t>> f_nested_array,
      WTF::Vector<NestedStructPtr> f_struct_array,
      WTF::Vector<TestUnionPtr> f_union_array,
      const WTF::HashMap<WTF::String, int32_t>& f_map);

  ~TestStruct();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TestStructPtr>
  TestStructPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TestStruct::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::TestStruct_UnserializedMessageContext<
            UserType, TestStruct::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<TestStruct::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return TestStruct::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::TestStruct_UnserializedMessageContext<
            UserType, TestStruct::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<TestStruct::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo.test.data_view.TestStruct.f_string
  WTF::String f_string;
  
// @generated_from: mojo.test.data_view.TestStruct.f_struct
  NestedStructPtr f_struct;
  
// @generated_from: mojo.test.data_view.TestStruct.f_native_struct
  TestNativeStructPtr f_native_struct;
  
// @generated_from: mojo.test.data_view.TestStruct.f_bool_array
  WTF::Vector<bool> f_bool_array;
  
// @generated_from: mojo.test.data_view.TestStruct.f_int32_array
  WTF::Vector<int32_t> f_int32_array;
  
// @generated_from: mojo.test.data_view.TestStruct.f_enum_array
  WTF::Vector<TestEnum> f_enum_array;
  
// @generated_from: mojo.test.data_view.TestStruct.f_interface_array
  WTF::Vector<::mojo::PendingRemote<TestInterface>> f_interface_array;
  
// @generated_from: mojo.test.data_view.TestStruct.f_nested_array
  WTF::Vector<WTF::Vector<int32_t>> f_nested_array;
  
// @generated_from: mojo.test.data_view.TestStruct.f_struct_array
  WTF::Vector<NestedStructPtr> f_struct_array;
  
// @generated_from: mojo.test.data_view.TestStruct.f_union_array
  WTF::Vector<TestUnionPtr> f_union_array;
  
// @generated_from: mojo.test.data_view.TestStruct.f_map
  WTF::HashMap<WTF::String, int32_t> f_map;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
  DISALLOW_COPY_AND_ASSIGN(TestStruct);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, TestStruct::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}

template <typename UnionPtrType>
TestUnionPtr TestUnion::Clone() const {
  // Use UnionPtrType to prevent the compiler from trying to compile this
  // without being asked.
  UnionPtrType rv(New());
  switch (tag_) {
    case Tag::F_BOOL:
      rv->set_f_bool(mojo::Clone(data_.f_bool));
      break;
    case Tag::F_INT32:
      rv->set_f_int32(mojo::Clone(data_.f_int32));
      break;
  }
  return rv;
}

template <typename T,
          typename std::enable_if<std::is_same<
              T, TestUnion>::value>::type*>
bool TestUnion::Equals(const T& other) const {
  if (tag_ != other.which())
    return false;

  switch (tag_) {
    case Tag::F_BOOL:
      return mojo::Equals(data_.f_bool, other.data_.f_bool);
    case Tag::F_INT32:
      return mojo::Equals(data_.f_int32, other.data_.f_int32);
  }

  return false;
}
template <typename StructPtrType>
NestedStructPtr NestedStruct::Clone() const {
  return New(
      mojo::Clone(f_int32)
  );
}

template <typename T, NestedStruct::EnableIfSame<T>*>
bool NestedStruct::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->f_int32, other_struct.f_int32))
    return false;
  return true;
}

template <typename T, NestedStruct::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.f_int32 < rhs.f_int32)
    return true;
  if (rhs.f_int32 < lhs.f_int32)
    return false;
  return false;
}
template <typename StructPtrType>
TestStructPtr TestStruct::Clone() const {
  return New(
      mojo::Clone(f_string),
      mojo::Clone(f_struct),
      mojo::Clone(f_native_struct),
      mojo::Clone(f_bool_array),
      mojo::Clone(f_int32_array),
      mojo::Clone(f_enum_array),
      mojo::Clone(f_interface_array),
      mojo::Clone(f_nested_array),
      mojo::Clone(f_struct_array),
      mojo::Clone(f_union_array),
      mojo::Clone(f_map)
  );
}

template <typename T, TestStruct::EnableIfSame<T>*>
bool TestStruct::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->f_string, other_struct.f_string))
    return false;
  if (!mojo::Equals(this->f_struct, other_struct.f_struct))
    return false;
  if (!mojo::Equals(this->f_native_struct, other_struct.f_native_struct))
    return false;
  if (!mojo::Equals(this->f_bool_array, other_struct.f_bool_array))
    return false;
  if (!mojo::Equals(this->f_int32_array, other_struct.f_int32_array))
    return false;
  if (!mojo::Equals(this->f_enum_array, other_struct.f_enum_array))
    return false;
  if (!mojo::Equals(this->f_interface_array, other_struct.f_interface_array))
    return false;
  if (!mojo::Equals(this->f_nested_array, other_struct.f_nested_array))
    return false;
  if (!mojo::Equals(this->f_struct_array, other_struct.f_struct_array))
    return false;
  if (!mojo::Equals(this->f_union_array, other_struct.f_union_array))
    return false;
  if (!mojo::Equals(this->f_map, other_struct.f_map))
    return false;
  return true;
}

template <typename T, TestStruct::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.f_string < rhs.f_string)
    return true;
  if (rhs.f_string < lhs.f_string)
    return false;
  if (lhs.f_struct < rhs.f_struct)
    return true;
  if (rhs.f_struct < lhs.f_struct)
    return false;
  if (lhs.f_native_struct < rhs.f_native_struct)
    return true;
  if (rhs.f_native_struct < lhs.f_native_struct)
    return false;
  if (lhs.f_bool_array < rhs.f_bool_array)
    return true;
  if (rhs.f_bool_array < lhs.f_bool_array)
    return false;
  if (lhs.f_int32_array < rhs.f_int32_array)
    return true;
  if (rhs.f_int32_array < lhs.f_int32_array)
    return false;
  if (lhs.f_enum_array < rhs.f_enum_array)
    return true;
  if (rhs.f_enum_array < lhs.f_enum_array)
    return false;
  if (lhs.f_interface_array < rhs.f_interface_array)
    return true;
  if (rhs.f_interface_array < lhs.f_interface_array)
    return false;
  if (lhs.f_nested_array < rhs.f_nested_array)
    return true;
  if (rhs.f_nested_array < lhs.f_nested_array)
    return false;
  if (lhs.f_struct_array < rhs.f_struct_array)
    return true;
  if (rhs.f_struct_array < lhs.f_struct_array)
    return false;
  if (lhs.f_union_array < rhs.f_union_array)
    return true;
  if (rhs.f_union_array < lhs.f_union_array)
    return false;
  if (lhs.f_map < rhs.f_map)
    return true;
  if (rhs.f_map < lhs.f_map)
    return false;
  return false;
}


}  // namespace blink
}  // namespace data_view
}  // namespace test
}  // namespace mojo

namespace mojo {


template <>
struct  StructTraits<::mojo::test::data_view::blink::NestedStruct::DataView,
                                         ::mojo::test::data_view::blink::NestedStructPtr> {
  static bool IsNull(const ::mojo::test::data_view::blink::NestedStructPtr& input) { return !input; }
  static void SetToNull(::mojo::test::data_view::blink::NestedStructPtr* output) { output->reset(); }

  static decltype(::mojo::test::data_view::blink::NestedStruct::f_int32) f_int32(
      const ::mojo::test::data_view::blink::NestedStructPtr& input) {
    return input->f_int32;
  }

  static bool Read(::mojo::test::data_view::blink::NestedStruct::DataView input, ::mojo::test::data_view::blink::NestedStructPtr* output);
};


template <>
struct  StructTraits<::mojo::test::data_view::blink::TestStruct::DataView,
                                         ::mojo::test::data_view::blink::TestStructPtr> {
  static bool IsNull(const ::mojo::test::data_view::blink::TestStructPtr& input) { return !input; }
  static void SetToNull(::mojo::test::data_view::blink::TestStructPtr* output) { output->reset(); }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_string)& f_string(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_string;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_struct)& f_struct(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_struct;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_native_struct)& f_native_struct(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_native_struct;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_bool_array)& f_bool_array(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_bool_array;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_int32_array)& f_int32_array(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_int32_array;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_enum_array)& f_enum_array(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_enum_array;
  }

  static  decltype(::mojo::test::data_view::blink::TestStruct::f_interface_array)& f_interface_array(
       ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_interface_array;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_nested_array)& f_nested_array(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_nested_array;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_struct_array)& f_struct_array(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_struct_array;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_union_array)& f_union_array(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_union_array;
  }

  static const decltype(::mojo::test::data_view::blink::TestStruct::f_map)& f_map(
      const ::mojo::test::data_view::blink::TestStructPtr& input) {
    return input->f_map;
  }

  static bool Read(::mojo::test::data_view::blink::TestStruct::DataView input, ::mojo::test::data_view::blink::TestStructPtr* output);
};


template <>
struct  UnionTraits<::mojo::test::data_view::blink::TestUnion::DataView,
                                        ::mojo::test::data_view::blink::TestUnionPtr> {
  static bool IsNull(const ::mojo::test::data_view::blink::TestUnionPtr& input) { return !input; }
  static void SetToNull(::mojo::test::data_view::blink::TestUnionPtr* output) { output->reset(); }

  static ::mojo::test::data_view::blink::TestUnion::Tag GetTag(const ::mojo::test::data_view::blink::TestUnionPtr& input) {
    return input->which();
  }

  static  bool f_bool(const ::mojo::test::data_view::blink::TestUnionPtr& input) {
    return input->get_f_bool();
  }

  static  int32_t f_int32(const ::mojo::test::data_view::blink::TestUnionPtr& input) {
    return input->get_f_int32();
  }

  static bool Read(::mojo::test::data_view::blink::TestUnion::DataView input, ::mojo::test::data_view::blink::TestUnionPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_DATA_VIEW_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMzcwMCwgImJlZ2luIjogMzY4NywgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdEludGVyZmFj
ZSJ9fSwgeyJlbmQiOiA0NTMyLCAiYmVnaW4iOiA0NTI4LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2Uv
Z2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6
ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJt
b2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0SW50ZXJmYWNlLkVj
aG8ifX0sIHsiZW5kIjogNDcxMywgImJlZ2luIjogNDcwOSwgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdEludGVyZmFjZS5F
Y2hvIn19LCB7ImVuZCI6IDUwNzEsICJiZWdpbiI6IDUwNjcsICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0YV92aWV3LlRlc3RJbnRlcmZhY2Uu
RWNobyJ9fSwgeyJlbmQiOiA1MTkxLCAiYmVnaW4iOiA1MTg3LCAiZWRnZSI6ICIlL2t5dGhlL2Vk
Z2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1
cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6
ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0SW50ZXJmYWNl
LkVjaG8ifX0sIHsiZW5kIjogNjkxNiwgImJlZ2luIjogNjkwNCwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuTmVzdGVkU3RydWN0
In19LCB7ImVuZCI6IDEwNTU0LCAiYmVnaW4iOiAxMDU0NywgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuTmVzdGVkU3RydWN0LmZf
aW50MzIifX0sIHsiZW5kIjogMTE1ODgsICJiZWdpbiI6IDExNTc5LCAiZWRnZSI6ICIlL2t5dGhl
L2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNv
cnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFn
ZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0VW5pb24i
fX0sIHsiZW5kIjogMTM0OTEsICJiZWdpbiI6IDEzNDgyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2Uv
Z2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6
ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJt
b2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0VW5pb24uZl9ib29s
In19LCB7ImVuZCI6IDEzNjEwLCAiYmVnaW4iOiAxMzYwMCwgImVkZ2UiOiAiJS9reXRoZS9lZGdl
L2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMi
OiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAi
bW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdFVuaW9uLmZfYm9v
bCJ9fSwgeyJlbmQiOiAxMzc2MSwgImJlZ2luIjogMTM3NTEsICJlZGdlIjogIiUva3l0aGUvZWRn
ZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVz
IjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjog
Im1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0YV92aWV3LlRlc3RVbmlvbi5mX2Jv
b2wifX0sIHsiZW5kIjogMTM4NjEsICJiZWdpbiI6IDEzODUxLCAiZWRnZSI6ICIlL2t5dGhlL2Vk
Z2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1
cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6
ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0VW5pb24uZl9p
bnQzMiJ9fSwgeyJlbmQiOiAxMzk4NiwgImJlZ2luIjogMTM5NzUsICJlZGdlIjogIiUva3l0aGUv
ZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29y
cHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdl
IjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0YV92aWV3LlRlc3RVbmlvbi5m
X2ludDMyIn19LCB7ImVuZCI6IDE0MTQxLCAiYmVnaW4iOiAxNDEzMCwgImVkZ2UiOiAiJS9reXRo
ZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJj
b3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3Vh
Z2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdFVuaW9u
LmZfaW50MzIifX0sIHsiZW5kIjogMTUwMDIsICJiZWdpbiI6IDE0OTkyLCAiZWRnZSI6ICIlL2t5
dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7
ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5n
dWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0U3Ry
dWN0In19LCB7ImVuZCI6IDE4ODUwLCAiYmVnaW4iOiAxODg0MiwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdFN0cnVjdC5m
X3N0cmluZyJ9fSwgeyJlbmQiOiAxODk0MSwgImJlZ2luIjogMTg5MzMsICJlZGdlIjogIiUva3l0
aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsi
Y29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1
YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0YV92aWV3LlRlc3RTdHJ1
Y3QuZl9zdHJ1Y3QifX0sIHsiZW5kIjogMTkwNTAsICJiZWdpbiI6IDE5MDM1LCAiZWRnZSI6ICIl
L2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUi
OiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJs
YW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0
U3RydWN0LmZfbmF0aXZlX3N0cnVjdCJ9fSwgeyJlbmQiOiAxOTE1MSwgImJlZ2luIjogMTkxMzks
ICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5l
cyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21p
dW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0
YV92aWV3LlRlc3RTdHJ1Y3QuZl9ib29sX2FycmF5In19LCB7ImVuZCI6IDE5MjU3LCAiYmVnaW4i
OiAxOTI0NCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hv
cl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNv
bS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8u
dGVzdC5kYXRhX3ZpZXcuVGVzdFN0cnVjdC5mX2ludDMyX2FycmF5In19LCB7ImVuZCI6IDE5MzYy
LCAiYmVnaW4iOiAxOTM1MCwgImVkZ2UiOiAiJS9reXRoZS9lZGdlL2dlbmVyYXRlcyIsICJ0eXBl
IjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3JwdXMiOiAiY2hyb21pdW0uZ29vZ2xl
c291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2UiOiAibW9qb20iLCAic2lnbmF0dXJl
IjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdFN0cnVjdC5mX2VudW1fYXJyYXkifX0sIHsiZW5k
IjogMTk1MDUsICJiZWdpbiI6IDE5NDg4LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVz
IiwgInR5cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1
bS5nb29nbGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJz
aWduYXR1cmUiOiAibW9qby50ZXN0LmRhdGFfdmlldy5UZXN0U3RydWN0LmZfaW50ZXJmYWNlX2Fy
cmF5In19LCB7ImVuZCI6IDE5NjI2LCAiYmVnaW4iOiAxOTYxMiwgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam8udGVzdC5kYXRhX3ZpZXcuVGVzdFN0cnVjdC5m
X25lc3RlZF9hcnJheSJ9fSwgeyJlbmQiOiAxOTc0MiwgImJlZ2luIjogMTk3MjgsICJlZGdlIjog
IiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFt
ZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwg
Imxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvLnRlc3QuZGF0YV92aWV3LlRl
c3RTdHJ1Y3QuZl9zdHJ1Y3RfYXJyYXkifX0sIHsiZW5kIjogMTk4NTMsICJiZWdpbiI6IDE5ODQw
LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9yX2RlZmlu
ZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29tL2Nocm9t
aXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qby50ZXN0LmRh
dGFfdmlldy5UZXN0U3RydWN0LmZfdW5pb25fYXJyYXkifX0sIHsiZW5kIjogMTk5NTcsICJiZWdp
biI6IDE5OTUyLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5j
aG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2Uu
Y29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9q
by50ZXN0LmRhdGFfdmlldy5UZXN0U3RydWN0LmZfbWFwIn19XSwgInR5cGUiOiAia3l0aGUwIn0=
*/