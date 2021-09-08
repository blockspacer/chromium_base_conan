// mojo/public/js/ts/bindings/tests/export2.test-mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('mojo.tstest.exported');




/**
 * @const { !number }
 * @export
 */
mojo.tstest.exported.TWO = 2;




/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.tstest.exported.ExportedStructTwoSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.tstest.exported.ExportedStructTwoSpec.$,
    'ExportedStructTwo',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Bool,
        false,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.tstest.exported.ExportedStructTwo = class {
  constructor() {
    /** @export { !boolean } */
    this.value;
  }
};

