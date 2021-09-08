// mojo/public/mojom/base/read_only_file.mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('mojoBase.mojom');







/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojoBase.mojom.ReadOnlyFileSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojoBase.mojom.ReadOnlyFileSpec.$,
    'ReadOnlyFile',
    [
      mojo.internal.StructField(
        'fd', 0,
        0,
        mojo.internal.Handle,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'async', 4,
        0,
        mojo.internal.Bool,
        false,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojoBase.mojom.ReadOnlyFile = class {
  constructor() {
    /** @export { !MojoHandle } */
    this.fd;
    /** @export { !boolean } */
    this.async;
  }
};


