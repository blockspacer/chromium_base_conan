// mojo/public/interfaces/bindings/tests/regression_tests.mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



/** @enum {number} */
regressionTests.EnumWithReference = {};
regressionTests.EnumWithReference.k_STEREO_AND_KEYBOARD_MIC;
regressionTests.EnumWithReference.k_MAX;
/** @enum {number} */
regressionTests.EnumWithLowercase = {};
regressionTests.EnumWithLowercase.PlanarF16;
regressionTests.EnumWithLowercase.PlanarF32;
/** @enum {number} */
regressionTests.EnumWithNumbers = {};
regressionTests.EnumWithNumbers.k_2_1;
/** @enum {number} */
regressionTests.EnumWithK = {};
regressionTests.EnumWithK.K;
goog.provide('regressionTests.CheckMethodWithEmptyResponse');
goog.provide('regressionTests.CheckMethodWithEmptyResponseImpl');
goog.provide('regressionTests.CheckMethodWithEmptyResponsePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
regressionTests.CheckMethodWithEmptyResponse;

/** @interface */
regressionTests.CheckMethodWithEmptyResponseImpl = class {
  /**
   * @return {Promise}
   */
  withouParameterAndEmptyResponse() {}
  /**
   * @param { !boolean } b
   * @return {Promise}
   */
  withParameterAndEmptyResponse(b) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { regressionTests.CheckMethodWithEmptyResponseImpl }
 */
regressionTests.CheckMethodWithEmptyResponsePtr = class {
  /**
   * @return {Promise}
   */
  withouParameterAndEmptyResponse() {}
  /**
   * @param { !boolean } b
   * @return {Promise}
   */
  withParameterAndEmptyResponse(b) {}
};

goog.provide('regressionTests.CheckNameCollision');
goog.provide('regressionTests.CheckNameCollisionImpl');
goog.provide('regressionTests.CheckNameCollisionPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
regressionTests.CheckNameCollision;

/** @interface */
regressionTests.CheckNameCollisionImpl = class {
  /**
   * @param { !boolean } message
   * @param { !boolean } response
   * @return {Promise}
   */
  withNameCollision(message, response) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { regressionTests.CheckNameCollisionImpl }
 */
regressionTests.CheckNameCollisionPtr = class {
  /**
   * @param { !boolean } message
   * @param { !boolean } response
   * @return {Promise}
   */
  withNameCollision(message, response) {}
};

goog.provide('regressionTests.HandlesNameCollisionInterface');
goog.provide('regressionTests.HandlesNameCollisionInterfaceImpl');
goog.provide('regressionTests.HandlesNameCollisionInterfacePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
regressionTests.HandlesNameCollisionInterface;

/** @interface */
regressionTests.HandlesNameCollisionInterfaceImpl = class {
  /**
   * @param { !regressionTests.EmptyStruct } handles
   * @return {Promise}
   */
  method(handles) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { regressionTests.HandlesNameCollisionInterfaceImpl }
 */
regressionTests.HandlesNameCollisionInterfacePtr = class {
  /**
   * @param { !regressionTests.EmptyStruct } handles
   * @return {Promise}
   */
  method(handles) {}
};

goog.provide('regressionTests.Edge');

regressionTests.Edge = class {
  constructor() {
    /** @type { regressionTests.Vertex } */
    this.v;
  }
};

goog.provide('regressionTests.Vertex');

regressionTests.Vertex = class {
  constructor() {
    /** @type { regressionTests.EmptyStruct } */
    this.e;
  }
};

goog.provide('regressionTests.EmptyStruct');

regressionTests.EmptyStruct = class {
  constructor() {
  }
};

goog.provide('regressionTests.A');

regressionTests.A = class {
  constructor() {
    /** @type { regressionTests.B } */
    this.b;
  }
};

goog.provide('regressionTests.B');

regressionTests.B = class {
  constructor() {
    /** @type { regressionTests.A } */
    this.a;
  }
};

goog.provide('regressionTests.HandlesNameCollisionStruct');

regressionTests.HandlesNameCollisionStruct = class {
  constructor() {
    /** @type { !regressionTests.EmptyStruct } */
    this.handles;
  }
};

goog.provide('regressionTests.HandlesHandleNameCollisionStruct');

regressionTests.HandlesHandleNameCollisionStruct = class {
  constructor() {
    /** @type { !MojoHandle } */
    this.handles;
  }
};

goog.provide('regressionTests.HandlesUnionNameCollisionStruct');

regressionTests.HandlesUnionNameCollisionStruct = class {
  constructor() {
    /** @type { !Object } */
    this.handles;
  }
};

goog.provide('regressionTests.CheckMethodWithEmptyResponse_WithouParameterAndEmptyResponse_Params');

regressionTests.CheckMethodWithEmptyResponse_WithouParameterAndEmptyResponse_Params = class {
  constructor() {
  }
};

goog.provide('regressionTests.CheckMethodWithEmptyResponse_WithouParameterAndEmptyResponse_ResponseParams');

regressionTests.CheckMethodWithEmptyResponse_WithouParameterAndEmptyResponse_ResponseParams = class {
  constructor() {
  }
};

goog.provide('regressionTests.CheckMethodWithEmptyResponse_WithParameterAndEmptyResponse_Params');

regressionTests.CheckMethodWithEmptyResponse_WithParameterAndEmptyResponse_Params = class {
  constructor() {
    /** @type { !boolean } */
    this.b;
  }
};

goog.provide('regressionTests.CheckMethodWithEmptyResponse_WithParameterAndEmptyResponse_ResponseParams');

regressionTests.CheckMethodWithEmptyResponse_WithParameterAndEmptyResponse_ResponseParams = class {
  constructor() {
  }
};

goog.provide('regressionTests.CheckNameCollision_WithNameCollision_Params');

regressionTests.CheckNameCollision_WithNameCollision_Params = class {
  constructor() {
    /** @type { !boolean } */
    this.message;
    /** @type { !boolean } */
    this.response;
  }
};

goog.provide('regressionTests.CheckNameCollision_WithNameCollision_ResponseParams');

regressionTests.CheckNameCollision_WithNameCollision_ResponseParams = class {
  constructor() {
    /** @type { !boolean } */
    this.message;
    /** @type { !boolean } */
    this.response;
  }
};

goog.provide('regressionTests.HandlesNameCollisionInterface_Method_Params');

regressionTests.HandlesNameCollisionInterface_Method_Params = class {
  constructor() {
    /** @type { !regressionTests.EmptyStruct } */
    this.handles;
  }
};

goog.provide('regressionTests.HandlesNameCollisionInterface_Method_ResponseParams');

regressionTests.HandlesNameCollisionInterface_Method_ResponseParams = class {
  constructor() {
    /** @type { !MojoHandle } */
    this.handles;
  }
};