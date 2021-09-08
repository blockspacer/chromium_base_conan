// mojo/public/mojom/base/big_buffer.mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('mojoBase.mojom');







/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojoBase.mojom.BigBufferSharedMemoryRegionSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType} }
 * @export
 */
mojoBase.mojom.BigBufferSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojoBase.mojom.BigBufferSharedMemoryRegionSpec.$,
    'BigBufferSharedMemoryRegion',
    [
      mojo.internal.StructField(
        'bufferHandle', 0,
        0,
        mojo.internal.Handle,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'size', 4,
        0,
        mojo.internal.Uint32,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojoBase.mojom.BigBufferSharedMemoryRegion = class {
  constructor() {
    /** @export { !MojoHandle } */
    this.bufferHandle;
    /** @export { !number } */
    this.size;
  }
};




mojo.internal.Union(
    mojoBase.mojom.BigBufferSpec.$, 'BigBuffer',
    {
      'bytes': {
        'ordinal': 0,
        'type': mojo.internal.Array(mojo.internal.Uint8, false),
      },
      'sharedMemory': {
        'ordinal': 1,
        'type': mojoBase.mojom.BigBufferSharedMemoryRegionSpec.$,
      },
      'invalidBuffer': {
        'ordinal': 2,
        'type': mojo.internal.Bool,
      },
    });

/**
 * @typedef { {
 *   bytes: (!Array<!number>|undefined),
 *   sharedMemory: (!mojoBase.mojom.BigBufferSharedMemoryRegion|undefined),
 *   invalidBuffer: (!boolean|undefined),
 * } }
 */
mojoBase.mojom.BigBuffer;
