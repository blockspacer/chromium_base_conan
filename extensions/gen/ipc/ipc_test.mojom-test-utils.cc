// ipc/ipc_test.mojom-test-utils.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif


#include "ipc/ipc_test.mojom-test-utils.h"

#include <utility>

#include "base/bind.h"
#include "base/run_loop.h"


#ifndef IPC_IPC_TEST_MOJOM_JUMBO_H_
#define IPC_IPC_TEST_MOJOM_JUMBO_H_
#endif


namespace IPC {
namespace mojom {


void SimpleTestDriverInterceptorForTesting::ExpectValue(int32_t value) {
  GetForwardingInterface()->ExpectValue(std::move(value));
}
void SimpleTestDriverInterceptorForTesting::GetExpectedValue(GetExpectedValueCallback callback) {
  GetForwardingInterface()->GetExpectedValue(std::move(callback));
}
void SimpleTestDriverInterceptorForTesting::RequestValue(RequestValueCallback callback) {
  GetForwardingInterface()->RequestValue(std::move(callback));
}
void SimpleTestDriverInterceptorForTesting::RequestQuit(RequestQuitCallback callback) {
  GetForwardingInterface()->RequestQuit(std::move(callback));
}
SimpleTestDriverAsyncWaiter::SimpleTestDriverAsyncWaiter(
    SimpleTestDriver* proxy) : proxy_(proxy) {}

SimpleTestDriverAsyncWaiter::~SimpleTestDriverAsyncWaiter() = default;

void SimpleTestDriverAsyncWaiter::GetExpectedValue(
    int32_t* out_value) {
  base::RunLoop loop;
  proxy_->GetExpectedValue(
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
void SimpleTestDriverAsyncWaiter::RequestValue(
    int32_t* out_value) {
  base::RunLoop loop;
  proxy_->RequestValue(
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
void SimpleTestDriverAsyncWaiter::RequestQuit(
    ) {
  base::RunLoop loop;
  proxy_->RequestQuit(
      base::BindOnce(
          [](base::RunLoop* loop) {
            loop->Quit();
          },
          &loop));
  loop.Run();
}



void SimpleTestClientInterceptorForTesting::RequestValue(RequestValueCallback callback) {
  GetForwardingInterface()->RequestValue(std::move(callback));
}
SimpleTestClientAsyncWaiter::SimpleTestClientAsyncWaiter(
    SimpleTestClient* proxy) : proxy_(proxy) {}

SimpleTestClientAsyncWaiter::~SimpleTestClientAsyncWaiter() = default;

void SimpleTestClientAsyncWaiter::RequestValue(
    int32_t* out_value) {
  base::RunLoop loop;
  proxy_->RequestValue(
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



void PingReceiverInterceptorForTesting::Ping(PingCallback callback) {
  GetForwardingInterface()->Ping(std::move(callback));
}
PingReceiverAsyncWaiter::PingReceiverAsyncWaiter(
    PingReceiver* proxy) : proxy_(proxy) {}

PingReceiverAsyncWaiter::~PingReceiverAsyncWaiter() = default;

void PingReceiverAsyncWaiter::Ping(
    ) {
  base::RunLoop loop;
  proxy_->Ping(
      base::BindOnce(
          [](base::RunLoop* loop) {
            loop->Quit();
          },
          &loop));
  loop.Run();
}



void TestStructPasserInterceptorForTesting::Pass(TestStructPtr s) {
  GetForwardingInterface()->Pass(std::move(s));
}
TestStructPasserAsyncWaiter::TestStructPasserAsyncWaiter(
    TestStructPasser* proxy) : proxy_(proxy) {}

TestStructPasserAsyncWaiter::~TestStructPasserAsyncWaiter() = default;




void IndirectTestDriverInterceptorForTesting::GetPingReceiver(::mojo::PendingAssociatedReceiver<PingReceiver> receiver) {
  GetForwardingInterface()->GetPingReceiver(std::move(receiver));
}
IndirectTestDriverAsyncWaiter::IndirectTestDriverAsyncWaiter(
    IndirectTestDriver* proxy) : proxy_(proxy) {}

IndirectTestDriverAsyncWaiter::~IndirectTestDriverAsyncWaiter() = default;




void ReflectorInterceptorForTesting::Ping(const std::string& value, PingCallback callback) {
  GetForwardingInterface()->Ping(std::move(value), std::move(callback));
}
void ReflectorInterceptorForTesting::SyncPing(const std::string& value, SyncPingCallback callback) {
  GetForwardingInterface()->SyncPing(std::move(value), std::move(callback));
}
void ReflectorInterceptorForTesting::Quit() {
  GetForwardingInterface()->Quit();
}
ReflectorAsyncWaiter::ReflectorAsyncWaiter(
    Reflector* proxy) : proxy_(proxy) {}

ReflectorAsyncWaiter::~ReflectorAsyncWaiter() = default;

void ReflectorAsyncWaiter::Ping(
    const std::string& value, std::string* out_value) {
  base::RunLoop loop;
  proxy_->Ping(std::move(value),
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
void ReflectorAsyncWaiter::SyncPing(
    const std::string& value, std::string* out_response) {
  base::RunLoop loop;
  proxy_->SyncPing(std::move(value),
      base::BindOnce(
          [](base::RunLoop* loop,
             std::string* out_response
,
             const std::string& response) {*out_response = std::move(response);
            loop->Quit();
          },
          &loop,
          out_response));
  loop.Run();
}



void AssociatedInterfaceVendorInterceptorForTesting::GetTestInterface(::mojo::PendingAssociatedReceiver<SimpleTestDriver> receiver) {
  GetForwardingInterface()->GetTestInterface(std::move(receiver));
}
AssociatedInterfaceVendorAsyncWaiter::AssociatedInterfaceVendorAsyncWaiter(
    AssociatedInterfaceVendor* proxy) : proxy_(proxy) {}

AssociatedInterfaceVendorAsyncWaiter::~AssociatedInterfaceVendorAsyncWaiter() = default;




void InterfacePassingTestDriverInterceptorForTesting::Init(InitCallback callback) {
  GetForwardingInterface()->Init(std::move(callback));
}
void InterfacePassingTestDriverInterceptorForTesting::GetPingReceiver(std::vector<::mojo::PendingReceiver<PingReceiver>> receiver, GetPingReceiverCallback callback) {
  GetForwardingInterface()->GetPingReceiver(std::move(receiver), std::move(callback));
}
void InterfacePassingTestDriverInterceptorForTesting::GetAssociatedPingReceiver(std::vector<::mojo::PendingAssociatedReceiver<PingReceiver>> receiver, GetAssociatedPingReceiverCallback callback) {
  GetForwardingInterface()->GetAssociatedPingReceiver(std::move(receiver), std::move(callback));
}
void InterfacePassingTestDriverInterceptorForTesting::Quit() {
  GetForwardingInterface()->Quit();
}
InterfacePassingTestDriverAsyncWaiter::InterfacePassingTestDriverAsyncWaiter(
    InterfacePassingTestDriver* proxy) : proxy_(proxy) {}

InterfacePassingTestDriverAsyncWaiter::~InterfacePassingTestDriverAsyncWaiter() = default;

void InterfacePassingTestDriverAsyncWaiter::Init(
    ) {
  base::RunLoop loop;
  proxy_->Init(
      base::BindOnce(
          [](base::RunLoop* loop) {
            loop->Quit();
          },
          &loop));
  loop.Run();
}
void InterfacePassingTestDriverAsyncWaiter::GetPingReceiver(
    std::vector<::mojo::PendingReceiver<PingReceiver>> receiver) {
  base::RunLoop loop;
  proxy_->GetPingReceiver(std::move(receiver),
      base::BindOnce(
          [](base::RunLoop* loop) {
            loop->Quit();
          },
          &loop));
  loop.Run();
}
void InterfacePassingTestDriverAsyncWaiter::GetAssociatedPingReceiver(
    std::vector<::mojo::PendingAssociatedReceiver<PingReceiver>> receiver) {
  base::RunLoop loop;
  proxy_->GetAssociatedPingReceiver(std::move(receiver),
      base::BindOnce(
          [](base::RunLoop* loop) {
            loop->Quit();
          },
          &loop));
  loop.Run();
}





}  // namespace mojom
}  // namespace IPC

#if defined(__clang__)
#pragma clang diagnostic pop
#endif