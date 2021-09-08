// mojo/public/cpp/bindings/tests/enum_default_unittest.test-mojom-test-utils.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif


#include "mojo/public/cpp/bindings/tests/enum_default_unittest.test-mojom-test-utils.h"

#include <utility>

#include "base/bind.h"
#include "base/run_loop.h"


#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_ENUM_DEFAULT_UNITTEST_TEST_MOJOM_JUMBO_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_ENUM_DEFAULT_UNITTEST_TEST_MOJOM_JUMBO_H_
#endif


namespace mojo {
namespace test {
namespace enum_default_unittest {
namespace mojom {


void TestInterfaceInterceptorForTesting::EchoWithDefault(ExtensibleEnumWithDefault in, EchoWithDefaultCallback callback) {
  GetForwardingInterface()->EchoWithDefault(std::move(in), std::move(callback));
}
void TestInterfaceInterceptorForTesting::EchoWithoutDefault(ExtensibleEnumWithoutDefault in, EchoWithoutDefaultCallback callback) {
  GetForwardingInterface()->EchoWithoutDefault(std::move(in), std::move(callback));
}
void TestInterfaceInterceptorForTesting::EchoStructWithDefault(StructWithExtensibleEnumWithDefaultPtr in, EchoStructWithDefaultCallback callback) {
  GetForwardingInterface()->EchoStructWithDefault(std::move(in), std::move(callback));
}
void TestInterfaceInterceptorForTesting::EchoStructWithoutDefault(StructWithExtensibleEnumWithoutDefaultPtr in, EchoStructWithoutDefaultCallback callback) {
  GetForwardingInterface()->EchoStructWithoutDefault(std::move(in), std::move(callback));
}
void TestInterfaceInterceptorForTesting::EchoUnionWithDefault(UnionWithExtensibleEnumWithDefaultPtr in, EchoUnionWithDefaultCallback callback) {
  GetForwardingInterface()->EchoUnionWithDefault(std::move(in), std::move(callback));
}
void TestInterfaceInterceptorForTesting::EchoUnionWithoutDefault(UnionWithExtensibleEnumWithoutDefaultPtr in, EchoUnionWithoutDefaultCallback callback) {
  GetForwardingInterface()->EchoUnionWithoutDefault(std::move(in), std::move(callback));
}
TestInterfaceAsyncWaiter::TestInterfaceAsyncWaiter(
    TestInterface* proxy) : proxy_(proxy) {}

TestInterfaceAsyncWaiter::~TestInterfaceAsyncWaiter() = default;

void TestInterfaceAsyncWaiter::EchoWithDefault(
    ExtensibleEnumWithDefault in, ExtensibleEnumWithDefault* out_out) {
  base::RunLoop loop;
  proxy_->EchoWithDefault(std::move(in),
      base::BindOnce(
          [](base::RunLoop* loop,
             ExtensibleEnumWithDefault* out_out
,
             ExtensibleEnumWithDefault out) {*out_out = std::move(out);
            loop->Quit();
          },
          &loop,
          out_out));
  loop.Run();
}
void TestInterfaceAsyncWaiter::EchoWithoutDefault(
    ExtensibleEnumWithoutDefault in, ExtensibleEnumWithoutDefault* out_out) {
  base::RunLoop loop;
  proxy_->EchoWithoutDefault(std::move(in),
      base::BindOnce(
          [](base::RunLoop* loop,
             ExtensibleEnumWithoutDefault* out_out
,
             ExtensibleEnumWithoutDefault out) {*out_out = std::move(out);
            loop->Quit();
          },
          &loop,
          out_out));
  loop.Run();
}
void TestInterfaceAsyncWaiter::EchoStructWithDefault(
    StructWithExtensibleEnumWithDefaultPtr in, StructWithExtensibleEnumWithDefaultPtr* out_out) {
  base::RunLoop loop;
  proxy_->EchoStructWithDefault(std::move(in),
      base::BindOnce(
          [](base::RunLoop* loop,
             StructWithExtensibleEnumWithDefaultPtr* out_out
,
             StructWithExtensibleEnumWithDefaultPtr out) {*out_out = std::move(out);
            loop->Quit();
          },
          &loop,
          out_out));
  loop.Run();
}
void TestInterfaceAsyncWaiter::EchoStructWithoutDefault(
    StructWithExtensibleEnumWithoutDefaultPtr in, StructWithExtensibleEnumWithoutDefaultPtr* out_out) {
  base::RunLoop loop;
  proxy_->EchoStructWithoutDefault(std::move(in),
      base::BindOnce(
          [](base::RunLoop* loop,
             StructWithExtensibleEnumWithoutDefaultPtr* out_out
,
             StructWithExtensibleEnumWithoutDefaultPtr out) {*out_out = std::move(out);
            loop->Quit();
          },
          &loop,
          out_out));
  loop.Run();
}
void TestInterfaceAsyncWaiter::EchoUnionWithDefault(
    UnionWithExtensibleEnumWithDefaultPtr in, UnionWithExtensibleEnumWithDefaultPtr* out_out) {
  base::RunLoop loop;
  proxy_->EchoUnionWithDefault(std::move(in),
      base::BindOnce(
          [](base::RunLoop* loop,
             UnionWithExtensibleEnumWithDefaultPtr* out_out
,
             UnionWithExtensibleEnumWithDefaultPtr out) {*out_out = std::move(out);
            loop->Quit();
          },
          &loop,
          out_out));
  loop.Run();
}
void TestInterfaceAsyncWaiter::EchoUnionWithoutDefault(
    UnionWithExtensibleEnumWithoutDefaultPtr in, UnionWithExtensibleEnumWithoutDefaultPtr* out_out) {
  base::RunLoop loop;
  proxy_->EchoUnionWithoutDefault(std::move(in),
      base::BindOnce(
          [](base::RunLoop* loop,
             UnionWithExtensibleEnumWithoutDefaultPtr* out_out
,
             UnionWithExtensibleEnumWithoutDefaultPtr out) {*out_out = std::move(out);
            loop->Quit();
          },
          &loop,
          out_out));
  loop.Run();
}





}  // namespace mojom
}  // namespace enum_default_unittest
}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif