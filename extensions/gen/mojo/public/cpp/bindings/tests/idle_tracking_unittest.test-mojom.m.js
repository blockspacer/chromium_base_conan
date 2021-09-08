// mojo/public/cpp/bindings/tests/idle_tracking_unittest.test-mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';




/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const TestServicePendingReceiver = class {
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
        this.handle, 'mojo.test.idle_tracking_unittest.mojom.TestService', scope);
  }
};

/** @interface */
export const TestServiceInterface = class {
  
  /**
   */

  ping() {}
  
  /**
   * @return {!Promise}
   */

  pingPong() {}
  
  /**
   * @param { !KeepAlivePendingReceiver } receiver
   */

  bindKeepAlive(receiver) {}
};

/**
 * @implements { TestServiceInterface }
 */
export const TestServiceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!TestServicePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          TestServicePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!TestServicePendingReceiver>}
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
        TestService_Ping_ParamsSpec.$,
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
        TestService_PingPong_ParamsSpec.$,
        TestService_PingPong_ResponseParamsSpec.$,
        [
        ]);
  }

  
  /**
   * @param { !KeepAlivePendingReceiver } receiver
   */

  bindKeepAlive(
      receiver) {
    this.proxy.sendMessage(
        1220089824,
        TestService_BindKeepAlive_ParamsSpec.$,
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
 */
export const TestServiceReceiver = class {
  /**
   * @param {!TestServiceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!TestServiceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        TestServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!TestServiceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        1611864242,
        TestService_Ping_ParamsSpec.$,
        null,
        impl.ping.bind(impl));
    this.helper_internal_.registerHandler(
        1206904002,
        TestService_PingPong_ParamsSpec.$,
        TestService_PingPong_ResponseParamsSpec.$,
        impl.pingPong.bind(impl));
    this.helper_internal_.registerHandler(
        1220089824,
        TestService_BindKeepAlive_ParamsSpec.$,
        null,
        impl.bindKeepAlive.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const TestService = class {
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
   * @return {!TestServiceRemote}
   */
  static getRemote() {
    let remote = new TestServiceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the TestService
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const TestServiceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      TestServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!TestServiceRemote>}
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
        TestService_Ping_ParamsSpec.$,
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
        TestService_PingPong_ParamsSpec.$,
        TestService_PingPong_ResponseParamsSpec.$,
        this.pingPong.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.bindKeepAlive =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1220089824,
        TestService_BindKeepAlive_ParamsSpec.$,
        null,
        this.bindKeepAlive.createReceiverHandler(false /* expectsResponse */));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }

  /**
   * @param {number} id An ID returned by a prior call to addListener.
   * @return {boolean} True iff the identified listener was found and removed.
   */
  removeListener(id) {
    return this.router_.removeListener(id);
  }
};


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const KeepAlivePendingReceiver = class {
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
        this.handle, 'mojo.test.idle_tracking_unittest.mojom.KeepAlive', scope);
  }
};

/** @interface */
export const KeepAliveInterface = class {
};

/**
 * @implements { KeepAliveInterface }
 */
export const KeepAliveRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!KeepAlivePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          KeepAlivePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!KeepAlivePendingReceiver>}
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
 */
export const KeepAliveReceiver = class {
  /**
   * @param {!KeepAliveInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!KeepAliveRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        KeepAliveRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!KeepAliveRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const KeepAlive = class {
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
   * @return {!KeepAliveRemote}
   */
  static getRemote() {
    let remote = new KeepAliveRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the KeepAlive
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const KeepAliveCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      KeepAliveRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!KeepAliveRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }

  /**
   * @param {number} id An ID returned by a prior call to addListener.
   * @return {boolean} True iff the identified listener was found and removed.
   */
  removeListener(id) {
    return this.router_.removeListener(id);
  }
};

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestService_Ping_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestService_PingPong_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestService_PingPong_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestService_BindKeepAlive_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    TestService_Ping_ParamsSpec.$,
    'TestService_Ping_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestService_Ping_Params = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestService_PingPong_ParamsSpec.$,
    'TestService_PingPong_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestService_PingPong_Params = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestService_PingPong_ResponseParamsSpec.$,
    'TestService_PingPong_ResponseParams',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestService_PingPong_ResponseParams = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestService_BindKeepAlive_ParamsSpec.$,
    'TestService_BindKeepAlive_Params',
    [
      mojo.internal.StructField(
        'receiver', 0,
        0,
        mojo.internal.InterfaceRequest(KeepAlivePendingReceiver),
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const TestService_BindKeepAlive_Params = class {
  constructor() {
    /** @type { !KeepAlivePendingReceiver } */
    this.receiver;
  }
};
