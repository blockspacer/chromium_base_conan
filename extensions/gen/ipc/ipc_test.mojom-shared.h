// ipc/ipc_test.mojom-shared.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPC_IPC_TEST_MOJOM_SHARED_H_
#define IPC_IPC_TEST_MOJOM_SHARED_H_

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
#include "ipc/ipc_test.mojom-shared-internal.h"
#include "mojo/public/cpp/bindings/lib/interface_serialization.h"



#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace IPC {
namespace mojom {
class TestStructDataView;



}  // namespace mojom
}  // namespace IPC

namespace mojo {
namespace internal {

template <>
struct MojomTypeTraits<::IPC::mojom::TestStructDataView> {
  using Data = ::IPC::mojom::internal::TestStruct_Data;
  using DataAsArrayElement = Pointer<Data>;
  static constexpr MojomTypeCategory category = MojomTypeCategory::kStruct;
};

}  // namespace internal
}  // namespace mojo


namespace IPC {
namespace mojom {
// Interface base classes. They are used for type safety check.
class SimpleTestDriverInterfaceBase {};

using SimpleTestDriverPtrDataView =
    mojo::InterfacePtrDataView<SimpleTestDriverInterfaceBase>;
using SimpleTestDriverRequestDataView =
    mojo::InterfaceRequestDataView<SimpleTestDriverInterfaceBase>;
using SimpleTestDriverAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<SimpleTestDriverInterfaceBase>;
using SimpleTestDriverAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<SimpleTestDriverInterfaceBase>;
class SimpleTestClientInterfaceBase {};

using SimpleTestClientPtrDataView =
    mojo::InterfacePtrDataView<SimpleTestClientInterfaceBase>;
using SimpleTestClientRequestDataView =
    mojo::InterfaceRequestDataView<SimpleTestClientInterfaceBase>;
using SimpleTestClientAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<SimpleTestClientInterfaceBase>;
using SimpleTestClientAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<SimpleTestClientInterfaceBase>;
class PingReceiverInterfaceBase {};

using PingReceiverPtrDataView =
    mojo::InterfacePtrDataView<PingReceiverInterfaceBase>;
using PingReceiverRequestDataView =
    mojo::InterfaceRequestDataView<PingReceiverInterfaceBase>;
using PingReceiverAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<PingReceiverInterfaceBase>;
using PingReceiverAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<PingReceiverInterfaceBase>;
class TestStructPasserInterfaceBase {};

using TestStructPasserPtrDataView =
    mojo::InterfacePtrDataView<TestStructPasserInterfaceBase>;
using TestStructPasserRequestDataView =
    mojo::InterfaceRequestDataView<TestStructPasserInterfaceBase>;
using TestStructPasserAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<TestStructPasserInterfaceBase>;
using TestStructPasserAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<TestStructPasserInterfaceBase>;
class IndirectTestDriverInterfaceBase {};

using IndirectTestDriverPtrDataView =
    mojo::InterfacePtrDataView<IndirectTestDriverInterfaceBase>;
using IndirectTestDriverRequestDataView =
    mojo::InterfaceRequestDataView<IndirectTestDriverInterfaceBase>;
using IndirectTestDriverAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<IndirectTestDriverInterfaceBase>;
using IndirectTestDriverAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<IndirectTestDriverInterfaceBase>;
class ReflectorInterfaceBase {};

using ReflectorPtrDataView =
    mojo::InterfacePtrDataView<ReflectorInterfaceBase>;
using ReflectorRequestDataView =
    mojo::InterfaceRequestDataView<ReflectorInterfaceBase>;
using ReflectorAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<ReflectorInterfaceBase>;
using ReflectorAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<ReflectorInterfaceBase>;
class AssociatedInterfaceVendorInterfaceBase {};

using AssociatedInterfaceVendorPtrDataView =
    mojo::InterfacePtrDataView<AssociatedInterfaceVendorInterfaceBase>;
using AssociatedInterfaceVendorRequestDataView =
    mojo::InterfaceRequestDataView<AssociatedInterfaceVendorInterfaceBase>;
using AssociatedInterfaceVendorAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<AssociatedInterfaceVendorInterfaceBase>;
using AssociatedInterfaceVendorAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<AssociatedInterfaceVendorInterfaceBase>;
class InterfacePassingTestDriverInterfaceBase {};

using InterfacePassingTestDriverPtrDataView =
    mojo::InterfacePtrDataView<InterfacePassingTestDriverInterfaceBase>;
using InterfacePassingTestDriverRequestDataView =
    mojo::InterfaceRequestDataView<InterfacePassingTestDriverInterfaceBase>;
using InterfacePassingTestDriverAssociatedPtrInfoDataView =
    mojo::AssociatedInterfacePtrInfoDataView<InterfacePassingTestDriverInterfaceBase>;
using InterfacePassingTestDriverAssociatedRequestDataView =
    mojo::AssociatedInterfaceRequestDataView<InterfacePassingTestDriverInterfaceBase>;


class TestStructDataView {
 public:
  TestStructDataView() {}

  TestStructDataView(
      internal::TestStruct_Data* data,
      mojo::Message* message)
      : data_(data) {}

  bool is_null() const { return !data_; }
 private:
  internal::TestStruct_Data* data_ = nullptr;
};



}  // namespace mojom
}  // namespace IPC

namespace std {

}  // namespace std

namespace mojo {


namespace internal {

template <typename MaybeConstUserType>
struct Serializer<::IPC::mojom::TestStructDataView, MaybeConstUserType> {
  using UserType = typename std::remove_const<MaybeConstUserType>::type;
  using Traits = StructTraits<::IPC::mojom::TestStructDataView, UserType>;

  static void Serialize(
      MaybeConstUserType& input,
      mojo::internal::MessageFragment<::IPC::mojom::internal::TestStruct_Data>& fragment) {
    if (CallIsNullIfExists<Traits>(input))
      return;
    fragment.Allocate();
  }

  static bool Deserialize(::IPC::mojom::internal::TestStruct_Data* input,
                          UserType* output,
                          Message* message) {
    if (!input)
      return CallSetToNullIfExists<Traits>(output);

    ::IPC::mojom::TestStructDataView data_view(input, message);
    return Traits::Read(data_view, output);
  }
};

}  // namespace internal

}  // namespace mojo


namespace IPC {
namespace mojom {




}  // namespace mojom
}  // namespace IPC

// Declare TraceFormatTraits for enums, which should be defined in ::perfetto
// namespace.

#endif  // IPC_IPC_TEST_MOJOM_SHARED_H_

/* Metadata comment
eyJtZXRhIjogW10sICJ0eXBlIjogImt5dGhlMCJ9
*/