// mojo/public/tools/fuzzers/fuzz.mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_TOOLS_FUZZERS_FUZZ_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_TOOLS_FUZZERS_FUZZ_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/tools/fuzzers/fuzz.mojom-blink.h"


namespace fuzz {
namespace mojom {
namespace blink {


class  FuzzDummyInterfaceInterceptorForTesting : public FuzzDummyInterface {
  virtual FuzzDummyInterface* GetForwardingInterface() = 0;
  void Ping() override;
};
class  FuzzDummyInterfaceAsyncWaiter {
 public:
  explicit FuzzDummyInterfaceAsyncWaiter(FuzzDummyInterface* proxy);
  ~FuzzDummyInterfaceAsyncWaiter();

 private:
  FuzzDummyInterface* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(FuzzDummyInterfaceAsyncWaiter);
};


class  FuzzInterfaceInterceptorForTesting : public FuzzInterface {
  virtual FuzzInterface* GetForwardingInterface() = 0;
  void FuzzBasic() override;
  void FuzzBasicResp(FuzzBasicRespCallback callback) override;
  void FuzzBasicSyncResp(FuzzBasicSyncRespCallback callback) override;
  void FuzzArgs(FuzzStructPtr a, FuzzStructPtr b) override;
  void FuzzArgsResp(FuzzStructPtr a, FuzzStructPtr b, FuzzArgsRespCallback callback) override;
  void FuzzArgsSyncResp(FuzzStructPtr a, FuzzStructPtr b, FuzzArgsSyncRespCallback callback) override;
  void FuzzAssociated(::mojo::PendingAssociatedReceiver<FuzzDummyInterface> receiver) override;
};
class  FuzzInterfaceAsyncWaiter {
 public:
  explicit FuzzInterfaceAsyncWaiter(FuzzInterface* proxy);
  ~FuzzInterfaceAsyncWaiter();
  void FuzzBasicResp(
      );
  void FuzzBasicSyncResp(
      );
  void FuzzArgsResp(
      FuzzStructPtr a, FuzzStructPtr b);
  void FuzzArgsSyncResp(
      FuzzStructPtr a, FuzzStructPtr b);

 private:
  FuzzInterface* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(FuzzInterfaceAsyncWaiter);
};




}  // namespace blink
}  // namespace mojom
}  // namespace fuzz

#endif  // MOJO_PUBLIC_TOOLS_FUZZERS_FUZZ_MOJOM_BLINK_TEST_UTILS_H_