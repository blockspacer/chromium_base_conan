// mojo/public/cpp/bindings/tests/remote_unittest.test-mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_REMOTE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_REMOTE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/cpp/bindings/tests/remote_unittest.test-mojom-blink.h"


namespace mojo {
namespace test {
namespace remote_unittest {
namespace mojom {
namespace blink {


class  SharedRemoteSyncTestInterceptorForTesting : public SharedRemoteSyncTest {
  virtual SharedRemoteSyncTest* GetForwardingInterface() = 0;
  void Fetch(FetchCallback callback) override;
};
class  SharedRemoteSyncTestAsyncWaiter {
 public:
  explicit SharedRemoteSyncTestAsyncWaiter(SharedRemoteSyncTest* proxy);
  ~SharedRemoteSyncTestAsyncWaiter();
  void Fetch(
      int32_t* out_value);

 private:
  SharedRemoteSyncTest* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(SharedRemoteSyncTestAsyncWaiter);
};


class  LargeMessageTestInterceptorForTesting : public LargeMessageTest {
  virtual LargeMessageTest* GetForwardingInterface() = 0;
  void ProcessData(const WTF::Vector<uint8_t>& data, ProcessDataCallback callback) override;
  void ProcessLotsOfData(const WTF::Vector<uint8_t>& data, ProcessLotsOfDataCallback callback) override;
  void GetLotsOfData(uint64_t data_size, GetLotsOfDataCallback callback) override;
};
class  LargeMessageTestAsyncWaiter {
 public:
  explicit LargeMessageTestAsyncWaiter(LargeMessageTest* proxy);
  ~LargeMessageTestAsyncWaiter();
  void ProcessData(
      const WTF::Vector<uint8_t>& data, uint64_t* out_data_size);
  void ProcessLotsOfData(
      const WTF::Vector<uint8_t>& data, uint64_t* out_data_size);
  void GetLotsOfData(
      uint64_t data_size, WTF::Vector<uint8_t>* out_data);

 private:
  LargeMessageTest* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(LargeMessageTestAsyncWaiter);
};




}  // namespace blink
}  // namespace mojom
}  // namespace remote_unittest
}  // namespace test
}  // namespace mojo

#endif  // MOJO_PUBLIC_CPP_BINDINGS_TESTS_REMOTE_UNITTEST_TEST_MOJOM_BLINK_TEST_UTILS_H_