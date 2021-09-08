// mojo/public/interfaces/bindings/tests/test_associated_interfaces.mojom-test-utils.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif


#include "mojo/public/interfaces/bindings/tests/test_associated_interfaces.mojom-test-utils.h"

#include <utility>

#include "base/bind.h"
#include "base/run_loop.h"
#include "mojo/public/interfaces/bindings/tests/ping_service.mojom.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_TEST_ASSOCIATED_INTERFACES_MOJOM_JUMBO_H_
#endif


namespace mojo {
namespace test {


FooInterfaceAsyncWaiter::FooInterfaceAsyncWaiter(
    FooInterface* proxy) : proxy_(proxy) {}

FooInterfaceAsyncWaiter::~FooInterfaceAsyncWaiter() = default;




void InterfacePassesAssociatedInterceptorForTesting::PassFoo(::mojo::PendingAssociatedRemote<FooInterface> foo_remote, ::mojo::PendingAssociatedReceiver<FooInterface> foo_receiver, PassFooCallback callback) {
  GetForwardingInterface()->PassFoo(std::move(foo_remote), std::move(foo_receiver), std::move(callback));
}
void InterfacePassesAssociatedInterceptorForTesting::PassStruct(StructContainsAssociatedPtr foo_struct, PassStructCallback callback) {
  GetForwardingInterface()->PassStruct(std::move(foo_struct), std::move(callback));
}
void InterfacePassesAssociatedInterceptorForTesting::PassUnion(UnionContainsAssociatedPtr foo_union, PassUnionCallback callback) {
  GetForwardingInterface()->PassUnion(std::move(foo_union), std::move(callback));
}
InterfacePassesAssociatedAsyncWaiter::InterfacePassesAssociatedAsyncWaiter(
    InterfacePassesAssociated* proxy) : proxy_(proxy) {}

InterfacePassesAssociatedAsyncWaiter::~InterfacePassesAssociatedAsyncWaiter() = default;

void InterfacePassesAssociatedAsyncWaiter::PassFoo(
    ::mojo::PendingAssociatedRemote<FooInterface> foo_remote, ::mojo::PendingAssociatedReceiver<FooInterface> foo_receiver, ::mojo::PendingAssociatedRemote<FooInterface>* out_foo_remote, ::mojo::PendingAssociatedReceiver<FooInterface>* out_foo_receiver) {
  base::RunLoop loop;
  proxy_->PassFoo(std::move(foo_remote),std::move(foo_receiver),
      base::BindOnce(
          [](base::RunLoop* loop,
             ::mojo::PendingAssociatedRemote<FooInterface>* out_foo_remote
,
             ::mojo::PendingAssociatedReceiver<FooInterface>* out_foo_receiver
,
             ::mojo::PendingAssociatedRemote<FooInterface> foo_remote,
             ::mojo::PendingAssociatedReceiver<FooInterface> foo_receiver) {*out_foo_remote = std::move(foo_remote);*out_foo_receiver = std::move(foo_receiver);
            loop->Quit();
          },
          &loop,
          out_foo_remote,
          out_foo_receiver));
  loop.Run();
}
void InterfacePassesAssociatedAsyncWaiter::PassStruct(
    StructContainsAssociatedPtr foo_struct, StructContainsAssociatedPtr* out_foo_struct) {
  base::RunLoop loop;
  proxy_->PassStruct(std::move(foo_struct),
      base::BindOnce(
          [](base::RunLoop* loop,
             StructContainsAssociatedPtr* out_foo_struct
,
             StructContainsAssociatedPtr foo_struct) {*out_foo_struct = std::move(foo_struct);
            loop->Quit();
          },
          &loop,
          out_foo_struct));
  loop.Run();
}
void InterfacePassesAssociatedAsyncWaiter::PassUnion(
    UnionContainsAssociatedPtr foo_union, UnionContainsAssociatedPtr* out_foo_union) {
  base::RunLoop loop;
  proxy_->PassUnion(std::move(foo_union),
      base::BindOnce(
          [](base::RunLoop* loop,
             UnionContainsAssociatedPtr* out_foo_union
,
             UnionContainsAssociatedPtr foo_union) {*out_foo_union = std::move(foo_union);
            loop->Quit();
          },
          &loop,
          out_foo_union));
  loop.Run();
}



void IntegerSenderInterceptorForTesting::Echo(int32_t value, EchoCallback callback) {
  GetForwardingInterface()->Echo(std::move(value), std::move(callback));
}
void IntegerSenderInterceptorForTesting::Send(int32_t value) {
  GetForwardingInterface()->Send(std::move(value));
}
IntegerSenderAsyncWaiter::IntegerSenderAsyncWaiter(
    IntegerSender* proxy) : proxy_(proxy) {}

IntegerSenderAsyncWaiter::~IntegerSenderAsyncWaiter() = default;

void IntegerSenderAsyncWaiter::Echo(
    int32_t value, int32_t* out_value) {
  base::RunLoop loop;
  proxy_->Echo(std::move(value),
      base::BindOnce(
          [](base::RunLoop* loop,
             int32_t* out_value
,
             int32_t value) {*out_value = std::move(value);
            loop->Quit();
          },
          &loop,
          out_value));
  loop.Run();
}



void StringSenderInterceptorForTesting::Echo(const std::string& value, EchoCallback callback) {
  GetForwardingInterface()->Echo(std::move(value), std::move(callback));
}
void StringSenderInterceptorForTesting::Send(const std::string& value) {
  GetForwardingInterface()->Send(std::move(value));
}
StringSenderAsyncWaiter::StringSenderAsyncWaiter(
    StringSender* proxy) : proxy_(proxy) {}

StringSenderAsyncWaiter::~StringSenderAsyncWaiter() = default;

void StringSenderAsyncWaiter::Echo(
    const std::string& value, std::string* out_value) {
  base::RunLoop loop;
  proxy_->Echo(std::move(value),
      base::BindOnce(
          [](base::RunLoop* loop,
             std::string* out_value
,
             const std::string& value) {*out_value = std::move(value);
            loop->Quit();
          },
          &loop,
          out_value));
  loop.Run();
}



void IntegerSenderConnectionInterceptorForTesting::GetSender(::mojo::PendingAssociatedReceiver<IntegerSender> receiver) {
  GetForwardingInterface()->GetSender(std::move(receiver));
}
void IntegerSenderConnectionInterceptorForTesting::AsyncGetSender(AsyncGetSenderCallback callback) {
  GetForwardingInterface()->AsyncGetSender(std::move(callback));
}
IntegerSenderConnectionAsyncWaiter::IntegerSenderConnectionAsyncWaiter(
    IntegerSenderConnection* proxy) : proxy_(proxy) {}

IntegerSenderConnectionAsyncWaiter::~IntegerSenderConnectionAsyncWaiter() = default;

void IntegerSenderConnectionAsyncWaiter::AsyncGetSender(
    ::mojo::PendingAssociatedRemote<IntegerSender>* out_sender) {
  base::RunLoop loop;
  proxy_->AsyncGetSender(
      base::BindOnce(
          [](base::RunLoop* loop,
             ::mojo::PendingAssociatedRemote<IntegerSender>* out_sender
,
             ::mojo::PendingAssociatedRemote<IntegerSender> sender) {*out_sender = std::move(sender);
            loop->Quit();
          },
          &loop,
          out_sender));
  loop.Run();
}



void IntegerSenderConnectionAtBothEndsInterceptorForTesting::GetSender(::mojo::PendingAssociatedReceiver<IntegerSender> receiver) {
  GetForwardingInterface()->GetSender(std::move(receiver));
}
void IntegerSenderConnectionAtBothEndsInterceptorForTesting::SetSender(::mojo::PendingAssociatedRemote<IntegerSender> sender, SetSenderCallback callback) {
  GetForwardingInterface()->SetSender(std::move(sender), std::move(callback));
}
IntegerSenderConnectionAtBothEndsAsyncWaiter::IntegerSenderConnectionAtBothEndsAsyncWaiter(
    IntegerSenderConnectionAtBothEnds* proxy) : proxy_(proxy) {}

IntegerSenderConnectionAtBothEndsAsyncWaiter::~IntegerSenderConnectionAtBothEndsAsyncWaiter() = default;

void IntegerSenderConnectionAtBothEndsAsyncWaiter::SetSender(
    ::mojo::PendingAssociatedRemote<IntegerSender> sender, int32_t* out_value) {
  base::RunLoop loop;
  proxy_->SetSender(std::move(sender),
      base::BindOnce(
          [](base::RunLoop* loop,
             int32_t* out_value
,
             int32_t value) {*out_value = std::move(value);
            loop->Quit();
          },
          &loop,
          out_value));
  loop.Run();
}



void SenderConnectionInterceptorForTesting::GetIntegerSender(::mojo::PendingAssociatedReceiver<IntegerSender> receiver) {
  GetForwardingInterface()->GetIntegerSender(std::move(receiver));
}
void SenderConnectionInterceptorForTesting::GetStringSender(::mojo::PendingAssociatedReceiver<StringSender> receiver) {
  GetForwardingInterface()->GetStringSender(std::move(receiver));
}
SenderConnectionAsyncWaiter::SenderConnectionAsyncWaiter(
    SenderConnection* proxy) : proxy_(proxy) {}

SenderConnectionAsyncWaiter::~SenderConnectionAsyncWaiter() = default;




void AssociatedPingProviderInterceptorForTesting::GetPing(::mojo::PendingAssociatedReceiver<::mojo::test::PingService> receiver) {
  GetForwardingInterface()->GetPing(std::move(receiver));
}
AssociatedPingProviderAsyncWaiter::AssociatedPingProviderAsyncWaiter(
    AssociatedPingProvider* proxy) : proxy_(proxy) {}

AssociatedPingProviderAsyncWaiter::~AssociatedPingProviderAsyncWaiter() = default;




void AssociatedPingProviderProviderInterceptorForTesting::GetPingProvider(::mojo::PendingAssociatedReceiver<AssociatedPingProvider> receiver) {
  GetForwardingInterface()->GetPingProvider(std::move(receiver));
}
AssociatedPingProviderProviderAsyncWaiter::AssociatedPingProviderProviderAsyncWaiter(
    AssociatedPingProviderProvider* proxy) : proxy_(proxy) {}

AssociatedPingProviderProviderAsyncWaiter::~AssociatedPingProviderProviderAsyncWaiter() = default;






}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif