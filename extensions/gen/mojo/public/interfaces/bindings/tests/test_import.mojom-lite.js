// mojo/public/interfaces/bindings/tests/test_import.mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('mojo.test.testImport');







/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.testImport.ImportingStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.testImport.ImportingStructSpec.$,
    'ImportingStruct',
    [
      mojo.internal.StructField(
        'strings', 0,
        0,
        mojo.test.testExport.StringPairSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.testImport.ImportingStruct = class {
  constructor() {
    /** @export { !mojo.test.testExport.StringPair } */
    this.strings;
  }
};


