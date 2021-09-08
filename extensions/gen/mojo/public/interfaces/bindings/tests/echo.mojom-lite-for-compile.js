// mojo/public/interfaces/bindings/tests/echo.mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');

goog.require('test.echoImport.mojom.Point');






goog.provide('test.echo.mojom.Echo');
goog.provide('test.echo.mojom.EchoReceiver');
goog.provide('test.echo.mojom.EchoCallbackRouter');
goog.provide('test.echo.mojom.EchoInterface');
goog.provide('test.echo.mojom.EchoRemote');
goog.provide('test.echo.mojom.EchoPendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
test.echo.mojom.EchoPendingReceiver = class {
  /**
   * @param {!MojoHandle|!mojo.internal.interfaceSupport.Endpoint} handle
   */
  constructor(handle) {
    /** @public {!mojo.internal.interfaceSupport.Endpoint} */
    this.handle = mojo.internal.interfaceSupport.getEndpointForReceiver(handle);
  }

  /** @param {string=} scope */
  bindInBrowser(scope = 'context') {
    mojo.internal.interfaceSupport.bind(
        this.handle,
        test.echo.mojom.Echo.$interfaceName,
        scope);
  }
};

/** @interface */
test.echo.mojom.EchoInterface = class {
  
  /**
   * @param { !test.echoImport.mojom.Point } point
   * @return {!Promise<{
        result: !test.echoImport.mojom.Point,
   *  }>}
   */

  echoPoint(point) {}
};

/**
 * @export
 * @implements { test.echo.mojom.EchoInterface }
 */
test.echo.mojom.EchoRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!test.echo.mojom.EchoPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          test.echo.mojom.EchoPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!test.echo.mojom.EchoPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !test.echoImport.mojom.Point } point
   * @return {!Promise<{
        result: !test.echoImport.mojom.Point,
   *  }>}
   */

  echoPoint(
      point) {
    return this.proxy.sendMessage(
        603489257,
        test.echo.mojom.Echo_EchoPoint_ParamsSpec.$,
        test.echo.mojom.Echo_EchoPoint_ResponseParamsSpec.$,
        [
          point
        ]);
  }
};

/**
 * An object which receives request messages for the Echo
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
test.echo.mojom.EchoReceiver = class {
  /**
   * @param {!test.echo.mojom.EchoInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!test.echo.mojom.EchoRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        test.echo.mojom.EchoRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!test.echo.mojom.EchoRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        603489257,
        test.echo.mojom.Echo_EchoPoint_ParamsSpec.$,
        test.echo.mojom.Echo_EchoPoint_ResponseParamsSpec.$,
        impl.echoPoint.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
test.echo.mojom.Echo = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "test.echo.mojom.Echo";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!test.echo.mojom.EchoRemote}
   * @export
   */
  static getRemote() {
    let remote = new test.echo.mojom.EchoRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the Echo
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
test.echo.mojom.EchoCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      test.echo.mojom.EchoRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!test.echo.mojom.EchoRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoPoint =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        603489257,
        test.echo.mojom.Echo_EchoPoint_ParamsSpec.$,
        test.echo.mojom.Echo_EchoPoint_ResponseParamsSpec.$,
        this.echoPoint.createReceiverHandler(true /* expectsResponse */));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }

  /**
   * @param {number} id An ID returned by a prior call to addListener.
   * @return {boolean} True iff the identified listener was found and removed.
   * @export
   */
  removeListener(id) {
    return this.router_.removeListener(id);
  }
};


goog.provide('test.echo.mojom.Echo_EchoPoint_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
test.echo.mojom.Echo_EchoPoint_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('test.echo.mojom.Echo_EchoPoint_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
test.echo.mojom.Echo_EchoPoint_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    test.echo.mojom.Echo_EchoPoint_ParamsSpec.$,
    'Echo_EchoPoint_Params',
    [
      mojo.internal.StructField(
        'point', 0,
        0,
        test.echoImport.mojom.PointSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('test.echo.mojom.Echo_EchoPoint_Params');

/** @record */
test.echo.mojom.Echo_EchoPoint_Params = class {
  constructor() {
    /** @export { !test.echoImport.mojom.Point } */
    this.point;
  }
};




mojo.internal.Struct(
    test.echo.mojom.Echo_EchoPoint_ResponseParamsSpec.$,
    'Echo_EchoPoint_ResponseParams',
    [
      mojo.internal.StructField(
        'result', 0,
        0,
        test.echoImport.mojom.PointSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('test.echo.mojom.Echo_EchoPoint_ResponseParams');

/** @record */
test.echo.mojom.Echo_EchoPoint_ResponseParams = class {
  constructor() {
    /** @export { !test.echoImport.mojom.Point } */
    this.result;
  }
};


