// mojo/public/js/ts/bindings/tests/export_other3.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');

goog.require('mojo.tstest.exportedOther.ExportedStructTwo');



goog.provide('mojo.tstest.exportedOther.ALSO_TWO');
/**
 * @const { !number }
 * @export
 */
mojo.tstest.exportedOther.ALSO_TWO = 2;



goog.provide('mojo.tstest.exportedOther.ExportedStructThreeSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.tstest.exportedOther.ExportedStructThreeSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.tstest.exportedOther.ExportedStructThreeSpec.$,
    'ExportedStructThree',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.tstest.exportedOther.ExportedStructTwoSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.tstest.exportedOther.ExportedStructThree');

/** @record */
mojo.tstest.exportedOther.ExportedStructThree = class {
  constructor() {
    /** @export { !mojo.tstest.exportedOther.ExportedStructTwo } */
    this.value;
  }
};


