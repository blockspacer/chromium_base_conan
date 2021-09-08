// mojo/public/cpp/bindings/tests/idle_tracking_unittest.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');







goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService');
goog.provide('mojo.test.idleTrackingUnittest.mojom.TestServiceReceiver');
goog.provide('mojo.test.idleTrackingUnittest.mojom.TestServiceCallbackRouter');
goog.provide('mojo.test.idleTrackingUnittest.mojom.TestServiceInterface');
goog.provide('mojo.test.idleTrackingUnittest.mojom.TestServiceRemote');
goog.provide('mojo.test.idleTrackingUnittest.mojom.TestServicePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.TestServicePendingReceiver = class {
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
        mojo.test.idleTrackingUnittest.mojom.TestService.$interfaceName,
        scope);
  }
};

/** @interface */
mojo.test.idleTrackingUnittest.mojom.TestServiceInterface = class {
  
  /**
   */

  ping() {}
  
  /**
   * @return {!Promise}
   */

  pingPong() {}
  
  /**
   * @param { !mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver } receiver
   */

  bindKeepAlive(receiver) {}
};

/**
 * @export
 * @implements { mojo.test.idleTrackingUnittest.mojom.TestServiceInterface }
 */
mojo.test.idleTrackingUnittest.mojom.TestServiceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.idleTrackingUnittest.mojom.TestServicePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.idleTrackingUnittest.mojom.TestServicePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.idleTrackingUnittest.mojom.TestServicePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   */

  ping() {
    this.proxy.sendMessage(
        1611864242,
        mojo.test.idleTrackingUnittest.mojom.TestService_Ping_ParamsSpec.$,
        null,
        [
        ]);
  }

  
  /**
   * @return {!Promise}
   */

  pingPong() {
    return this.proxy.sendMessage(
        1206904002,
        mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ParamsSpec.$,
        mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParamsSpec.$,
        [
        ]);
  }

  
  /**
   * @param { !mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver } receiver
   */

  bindKeepAlive(
      receiver) {
    this.proxy.sendMessage(
        1220089824,
        mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_ParamsSpec.$,
        null,
        [
          receiver
        ]);
  }
};

/**
 * An object which receives request messages for the TestService
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.TestServiceReceiver = class {
  /**
   * @param {!mojo.test.idleTrackingUnittest.mojom.TestServiceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.idleTrackingUnittest.mojom.TestServiceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.idleTrackingUnittest.mojom.TestServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.idleTrackingUnittest.mojom.TestServiceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        1611864242,
        mojo.test.idleTrackingUnittest.mojom.TestService_Ping_ParamsSpec.$,
        null,
        impl.ping.bind(impl));
    this.helper_internal_.registerHandler(
        1206904002,
        mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ParamsSpec.$,
        mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParamsSpec.$,
        impl.pingPong.bind(impl));
    this.helper_internal_.registerHandler(
        1220089824,
        mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_ParamsSpec.$,
        null,
        impl.bindKeepAlive.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.idleTrackingUnittest.mojom.TestService = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.idle_tracking_unittest.mojom.TestService";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.idleTrackingUnittest.mojom.TestServiceRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.idleTrackingUnittest.mojom.TestServiceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the TestService
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.TestServiceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.idleTrackingUnittest.mojom.TestServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.idleTrackingUnittest.mojom.TestServiceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.ping =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1611864242,
        mojo.test.idleTrackingUnittest.mojom.TestService_Ping_ParamsSpec.$,
        null,
        this.ping.createReceiverHandler(false /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.pingPong =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1206904002,
        mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ParamsSpec.$,
        mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParamsSpec.$,
        this.pingPong.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.bindKeepAlive =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1220089824,
        mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_ParamsSpec.$,
        null,
        this.bindKeepAlive.createReceiverHandler(false /* expectsResponse */));
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


goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAlive');
goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAliveReceiver');
goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAliveCallbackRouter');
goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAliveInterface');
goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote');
goog.provide('mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver = class {
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
        mojo.test.idleTrackingUnittest.mojom.KeepAlive.$interfaceName,
        scope);
  }
};

/** @interface */
mojo.test.idleTrackingUnittest.mojom.KeepAliveInterface = class {
};

/**
 * @export
 * @implements { mojo.test.idleTrackingUnittest.mojom.KeepAliveInterface }
 */
mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }
};

/**
 * An object which receives request messages for the KeepAlive
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.KeepAliveReceiver = class {
  /**
   * @param {!mojo.test.idleTrackingUnittest.mojom.KeepAliveInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.idleTrackingUnittest.mojom.KeepAlive = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.idle_tracking_unittest.mojom.KeepAlive";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the KeepAlive
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.KeepAliveCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.idleTrackingUnittest.mojom.KeepAliveRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

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


goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_Ping_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.TestService_Ping_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.idleTrackingUnittest.mojom.TestService_Ping_ParamsSpec.$,
    'TestService_Ping_Params',
    [
    ],
    [[0, 8],]);



goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_Ping_Params');

/** @record */
mojo.test.idleTrackingUnittest.mojom.TestService_Ping_Params = class {
  constructor() {
  }
};




mojo.internal.Struct(
    mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ParamsSpec.$,
    'TestService_PingPong_Params',
    [
    ],
    [[0, 8],]);



goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_Params');

/** @record */
mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_Params = class {
  constructor() {
  }
};




mojo.internal.Struct(
    mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParamsSpec.$,
    'TestService_PingPong_ResponseParams',
    [
    ],
    [[0, 8],]);



goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParams');

/** @record */
mojo.test.idleTrackingUnittest.mojom.TestService_PingPong_ResponseParams = class {
  constructor() {
  }
};




mojo.internal.Struct(
    mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_ParamsSpec.$,
    'TestService_BindKeepAlive_Params',
    [
      mojo.internal.StructField(
        'receiver', 0,
        0,
        mojo.internal.InterfaceRequest(mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver),
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_Params');

/** @record */
mojo.test.idleTrackingUnittest.mojom.TestService_BindKeepAlive_Params = class {
  constructor() {
    /** @export { !mojo.test.idleTrackingUnittest.mojom.KeepAlivePendingReceiver } */
    this.receiver;
  }
};


