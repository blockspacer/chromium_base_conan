// mojo/public/js/ts/bindings/tests/structs.test-mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../bindings.js';



/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const EmptyStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const StructMemberStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const IntStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const BoolStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const NoDefaultValuesStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    EmptyStructSpec.$,
    'EmptyStruct',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const EmptyStruct = class {
  constructor() {
  }
};



mojo.internal.Struct(
    StructMemberStructSpec.$,
    'StructMemberStruct',
    [
      mojo.internal.StructField(
        'emptyStruct', 0,
        0,
        EmptyStructSpec.$,
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const StructMemberStruct = class {
  constructor() {
    /** @type { !EmptyStruct } */
    this.emptyStruct;
  }
};



mojo.internal.Struct(
    IntStructSpec.$,
    'IntStruct',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Int8,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const IntStruct = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};



mojo.internal.Struct(
    BoolStructSpec.$,
    'BoolStruct',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Bool,
        false,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const BoolStruct = class {
  constructor() {
    /** @type { !boolean } */
    this.value;
  }
};



mojo.internal.Struct(
    NoDefaultValuesStructSpec.$,
    'NoDefaultValuesStruct',
    [
      mojo.internal.StructField(
        'boolValue', 0,
        0,
        mojo.internal.Bool,
        false,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'int8Value', 1,
        0,
        mojo.internal.Int8,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'uint8Value', 2,
        0,
        mojo.internal.Uint8,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'int16Value', 4,
        0,
        mojo.internal.Int16,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'uint16Value', 6,
        0,
        mojo.internal.Uint16,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'int32Value', 8,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'uint32Value', 12,
        0,
        mojo.internal.Uint32,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'int64Value', 16,
        0,
        mojo.internal.Int64,
        BigInt(0),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'uint64Value', 24,
        0,
        mojo.internal.Uint64,
        BigInt(0),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'floatValue', 32,
        0,
        mojo.internal.Float,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'doubleValue', 40,
        0,
        mojo.internal.Double,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'stringValue', 48,
        0,
        mojo.internal.String,
        null,
        false /* nullable */,
        0),
    ],
    [[0, 64],]);



/**
 * @record
 */
export const NoDefaultValuesStruct = class {
  constructor() {
    /** @type { !boolean } */
    this.boolValue;
    /** @type { !number } */
    this.int8Value;
    /** @type { !number } */
    this.uint8Value;
    /** @type { !number } */
    this.int16Value;
    /** @type { !number } */
    this.uint16Value;
    /** @type { !number } */
    this.int32Value;
    /** @type { !number } */
    this.uint32Value;
    /** @type { !bigint } */
    this.int64Value;
    /** @type { !bigint } */
    this.uint64Value;
    /** @type { !number } */
    this.floatValue;
    /** @type { !number } */
    this.doubleValue;
    /** @type { !string } */
    this.stringValue;
  }
};

