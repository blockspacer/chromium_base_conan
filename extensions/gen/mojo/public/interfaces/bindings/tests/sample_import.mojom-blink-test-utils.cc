// mojo/public/interfaces/bindings/tests/sample_import.mojom-blink-test-utils.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
#endif


#include "mojo/public/interfaces/bindings/tests/sample_import.mojom-blink-test-utils.h"

#include <utility>

#include "base/bind.h"
#include "base/run_loop.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"


#ifndef MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT_MOJOM_BLINK_JUMBO_H_
#define MOJO_PUBLIC_INTERFACES_BINDINGS_TESTS_SAMPLE_IMPORT_MOJOM_BLINK_JUMBO_H_
#endif


namespace imported {
namespace blink {


void ImportedInterfaceInterceptorForTesting::DoSomething() {
  GetForwardingInterface()->DoSomething();
}
ImportedInterfaceAsyncWaiter::ImportedInterfaceAsyncWaiter(
    ImportedInterface* proxy) : proxy_(proxy) {}

ImportedInterfaceAsyncWaiter::~ImportedInterfaceAsyncWaiter() = default;






}  // namespace blink
}  // namespace imported

#if defined(__clang__)
#pragma clang diagnostic pop
#endif