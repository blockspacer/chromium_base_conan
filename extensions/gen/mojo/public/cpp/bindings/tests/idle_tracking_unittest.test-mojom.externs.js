// mojo/public/cpp/bindings/tests/idle_tracking_unittest.test-mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService');
goog.provide('mojo.test.idleTrackingUnittest.mojom.TestServiceImpl');
goog.provide('mojo.test.idleTrackingUnittest.mojom.TestServicePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.idleTrackingUnittest.mojom.TestService;

/** @interface */
mojo.test.idleTrackingUnittest.mojom.TestServiceImpl = class {
  /**
   */
  ping() {}
  /**
   * @return {Promise}
   */
  pingPong() {}
  /**
   * @param { !mojo.InterfaceRequest } receiver
   */
  bindKeepAlive(receiver) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.idleTrackingUnittest.mojom.TestServiceImpl }
 */
mojo.test.idleTrackingUnittest.mojom.TestServicePtr = class {
  /**
   */
  ping() {}
  /**
   * @return {Promise}
   */
  pingPong() {}
  /**
   * @param { !mojo.InterfaceRequest } receiver
   */
  bindKeepAlive(receiver) {}
};

goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAlive');
goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAliveImpl');
goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAlivePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.idleTrackingUnittest.mojom.KeepAlive;

/** @interface */
mojo.test.idleTrackingUnittest.mojom.KeepAliveImpl = class {
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.idleTrackingUnittest.mojom.KeepAliveImpl }
 */
mojo.test.idleTrackingUnittest.mojom.KeepAlivePtr = class {
};

goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_Ping_Params');

mojo.test.idleTrackingUnittest.mojom.TestService_Ping_Params = class {
  constructor() {
  }
};

goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_Params');

mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_Params = class {
  constructor() {
  }
};

goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParams');

mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParams = class {
  constructor() {
  }
};

goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_Params');

mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_Params = class {
  constructor() {
    /** @type { !mojo.InterfaceRequest } */
    this.receiver;
  }
};
