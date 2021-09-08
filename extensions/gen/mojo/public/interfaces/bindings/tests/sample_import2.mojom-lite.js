// mojo/public/interfaces/bindings/tests/sample_import2.mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('imported');





/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
imported.ColorSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
imported.Color = {
  
  RED: 0,
  BLACK: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};




/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
imported.SizeSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
imported.ThingSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    imported.SizeSpec.$,
    'Size',
    [
      mojo.internal.StructField(
        'width', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
      mojo.internal.StructField(
        'height', 4,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
imported.Size = class {
  constructor() {
    /** @export { !number } */
    this.width;
    /** @export { !number } */
    this.height;
  }
};




mojo.internal.Struct(
    imported.ThingSpec.$,
    'Thing',
    [
      mojo.internal.StructField(
        'shape', 0,
        0,
        imported.ShapeSpec.$,
        imported.Shape.RECTANGLE,
        false /* nullable */),
      mojo.internal.StructField(
        'color', 4,
        0,
        imported.ColorSpec.$,
        imported.Color.BLACK,
        false /* nullable */),
      mojo.internal.StructField(
        'location', 8,
        0,
        imported.PointSpec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'size', 16,
        0,
        imported.SizeSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 32],]);





/** @record */
imported.Thing = class {
  constructor() {
    /** @export { !imported.Shape } */
    this.shape;
    /** @export { !imported.Color } */
    this.color;
    /** @export { !imported.Point } */
    this.location;
    /** @export { !imported.Size } */
    this.size;
  }
};


