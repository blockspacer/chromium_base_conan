// mojo/public/cpp/bindings/tests/struct_headers_unittest.test-mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('mojo.test.structHeadersUnittest.mojom');







/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.structHeadersUnittest.mojom.FooSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.structHeadersUnittest.mojom.FooSpec.$,
    'Foo',
    [
      mojo.internal.StructField(
        'bar', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.structHeadersUnittest.mojom.Foo = class {
  constructor() {
    /** @export { !number } */
    this.bar;
  }
};

