// mojo/public/interfaces/bindings/tests/sample_import2.mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



/** @enum {number} */
imported.Color = {};
imported.Color.RED;
imported.Color.BLACK;
goog.provide('imported.Size');

imported.Size = class {
  constructor() {
    /** @type { !number } */
    this.width;
    /** @type { !number } */
    this.height;
  }
};

goog.provide('imported.Thing');

imported.Thing = class {
  constructor() {
    /** @type { !imported.Shape } */
    this.shape;
    /** @type { !imported.Color } */
    this.color;
    /** @type { !imported.Point } */
    this.location;
    /** @type { !imported.Size } */
    this.size;
  }
};