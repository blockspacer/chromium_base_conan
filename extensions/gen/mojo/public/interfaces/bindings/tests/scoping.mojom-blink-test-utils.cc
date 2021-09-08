// mojo/public/interfaces/bindings/tests/scoping.mojom-blink-test-utils.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif


#include "mojo/public/interfaces/bindings/tests/scoping.mojom-blink-test-utils.h"

#include <utility>

#include "base/bind.h"
#include "base/run_loop.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SCOPING_MOJOM_BLINK_JUMBO_H_
#endif


namespace mojo {
namespace test {
namespace blink {


void AInterceptorForTesting::GetB(::mojo::PendingReceiver<B> b) {
  GetForwardingInterface()->GetB(std::move(b));
}
AAsyncWaiter::AAsyncWaiter(
    A* proxy) : proxy_(proxy) {}

AAsyncWaiter::~AAsyncWaiter() = default;




void BInterceptorForTesting::GetC(::mojo::PendingReceiver<C> c) {
  GetForwardingInterface()->GetC(std::move(c));
}
BAsyncWaiter::BAsyncWaiter(
    B* proxy) : proxy_(proxy) {}

BAsyncWaiter::~BAsyncWaiter() = default;




void CInterceptorForTesting::D() {
  GetForwardingInterface()->D();
}
CAsyncWaiter::CAsyncWaiter(
    C* proxy) : proxy_(proxy) {}

CAsyncWaiter::~CAsyncWaiter() = default;






}  // namespace blink
}  // namespace test
}  // namespace mojo

#if defined(__clang__)
#pragma clang diagnostic pop
#endif