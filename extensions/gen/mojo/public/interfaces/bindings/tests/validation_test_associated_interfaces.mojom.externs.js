// mojo/public/interfaces/bindings/tests/validation_test_associated_interfaces.mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



goog.provide('mojo.test.InterfaceX');
goog.provide('mojo.test.InterfaceXImpl');
goog.provide('mojo.test.InterfaceXPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.InterfaceX;

/** @interface */
mojo.test.InterfaceXImpl = class {
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.InterfaceXImpl }
 */
mojo.test.InterfaceXPtr = class {
};

goog.provide('mojo.test.AssociatedConformanceTestInterface');
goog.provide('mojo.test.AssociatedConformanceTestInterfaceImpl');
goog.provide('mojo.test.AssociatedConformanceTestInterfacePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.AssociatedConformanceTestInterface;

/** @interface */
mojo.test.AssociatedConformanceTestInterfaceImpl = class {
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } param0
   */
  method0(param0) {}
  /**
   * @param { !mojo.AssociatedInterfaceRequest } param0
   */
  method1(param0) {}
  /**
   * @param { mojo.AssociatedInterfacePtrInfo } param0
   */
  method2(param0) {}
  /**
   * @param { !Array<mojo.AssociatedInterfacePtrInfo> } param0
   */
  method3(param0) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.AssociatedConformanceTestInterfaceImpl }
 */
mojo.test.AssociatedConformanceTestInterfacePtr = class {
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } param0
   */
  method0(param0) {}
  /**
   * @param { !mojo.AssociatedInterfaceRequest } param0
   */
  method1(param0) {}
  /**
   * @param { mojo.AssociatedInterfacePtrInfo } param0
   */
  method2(param0) {}
  /**
   * @param { !Array<mojo.AssociatedInterfacePtrInfo> } param0
   */
  method3(param0) {}
};

goog.provide('mojo.test.AssociatedConformanceTestInterface_Method0_Params');

mojo.test.AssociatedConformanceTestInterface_Method0_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfacePtrInfo } */
    this.param0;
  }
};

goog.provide('mojo.test.AssociatedConformanceTestInterface_Method1_Params');

mojo.test.AssociatedConformanceTestInterface_Method1_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.param0;
  }
};

goog.provide('mojo.test.AssociatedConformanceTestInterface_Method2_Params');

mojo.test.AssociatedConformanceTestInterface_Method2_Params = class {
  constructor() {
    /** @type { mojo.AssociatedInterfacePtrInfo } */
    this.param0;
  }
};

goog.provide('mojo.test.AssociatedConformanceTestInterface_Method3_Params');

mojo.test.AssociatedConformanceTestInterface_Method3_Params = class {
  constructor() {
    /** @type { !Array<mojo.AssociatedInterfacePtrInfo> } */
    this.param0;
  }
};
