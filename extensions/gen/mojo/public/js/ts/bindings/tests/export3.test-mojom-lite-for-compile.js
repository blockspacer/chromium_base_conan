// mojo/public/js/ts/bindings/tests/export3.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');




goog.provide('mojo.tstest.exported.THREE');
/**
 * @const { !number }
 * @export
 */
mojo.tstest.exported.THREE = 3;



goog.provide('mojo.tstest.exported.ExportedStructThreeSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.tstest.exported.ExportedStructThreeSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.tstest.exported.ExportedStructThreeSpec.$,
    'ExportedStructThree',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Bool,
        false,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.tstest.exported.ExportedStructThree');

/** @record */
mojo.tstest.exported.ExportedStructThree = class {
  constructor() {
    /** @export { !boolean } */
    this.value;
  }
};

