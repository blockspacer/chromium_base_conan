// mojo/public/tools/bindings/generators/js_templates/lite/test/test.test-mojom-blink-test-utils.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_TOOLS_BINDINGS_GENERATORS_JS_TEMPLATES_LITE_TEST_TEST_TEST_MOJOM_BLINK_TEST_UTILS_H_
#define MOJO_PUBLIC_TOOLS_BINDINGS_GENERATORS_JS_TEMPLATES_LITE_TEST_TEST_TEST_MOJOM_BLINK_TEST_UTILS_H_

#include "mojo/public/tools/bindings/generators/js_templates/lite/test/test.test-mojom-blink.h"


namespace test {
namespace mojom {
namespace blink {


class  TestPageHandlerInterceptorForTesting : public TestPageHandler {
  virtual TestPageHandler* GetForwardingInterface() = 0;
  void Method1(const WTF::String& p1, int32_t p2, Method1Callback callback) override;
};
class  TestPageHandlerAsyncWaiter {
 public:
  explicit TestPageHandlerAsyncWaiter(TestPageHandler* proxy);
  ~TestPageHandlerAsyncWaiter();
  void Method1(
      const WTF::String& p1, int32_t p2, WTF::Vector<WTF::String>* out_values, TestStructPtr* out_ts);

 private:
  TestPageHandler* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(TestPageHandlerAsyncWaiter);
};


class  TestPageInterceptorForTesting : public TestPage {
  virtual TestPage* GetForwardingInterface() = 0;
  void OnEvent1(TestStructPtr s) override;
};
class  TestPageAsyncWaiter {
 public:
  explicit TestPageAsyncWaiter(TestPage* proxy);
  ~TestPageAsyncWaiter();

 private:
  TestPage* const proxy_;

  DISALLOW_COPY_AND_ASSIGN(TestPageAsyncWaiter);
};




}  // namespace blink
}  // namespace mojom
}  // namespace test

#endif  // MOJO_PUBLIC_TOOLS_BINDINGS_GENERATORS_JS_TEMPLATES_LITE_TEST_TEST_TEST_MOJOM_BLINK_TEST_UTILS_H_