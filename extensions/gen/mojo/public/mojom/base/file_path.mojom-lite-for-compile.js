// mojo/public/mojom/base/file_path.mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');







goog.provide('mojoBase.mojom.FilePathSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojoBase.mojom.FilePathSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojoBase.mojom.FilePathSpec.$,
    'FilePath',
    [
      mojo.internal.StructField(
        'path', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojoBase.mojom.FilePath');

/** @record */
mojoBase.mojom.FilePath = class {
  constructor() {
    /** @export { !string } */
    this.path;
  }
};


