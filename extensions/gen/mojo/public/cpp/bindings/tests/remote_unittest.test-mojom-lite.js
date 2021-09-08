// mojo/public/cpp/bindings/tests/remote_unittest.test-mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('mojo.test.remoteUnittest.mojom');








/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestPendingReceiver = class {
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
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest.$interfaceName,
        scope);
  }
};



/**
 * @export
 * @implements { mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestInterface }
 */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @return {!Promise<{
        value: !number,
   *  }>}
   */

  fetch() {
    return this.proxy.sendMessage(
        1284435712,
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ResponseParamsSpec.$,
        [
        ]);
  }
};

/**
 * An object which receives request messages for the SharedRemoteSyncTest
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestReceiver = class {
  /**
   * @param {!mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        1284435712,
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ResponseParamsSpec.$,
        impl.fetch.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.remote_unittest.mojom.SharedRemoteSyncTest";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the SharedRemoteSyncTest
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.remoteUnittest.mojom.SharedRemoteSyncTestRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.fetch =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1284435712,
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ResponseParamsSpec.$,
        this.fetch.createReceiverHandler(true /* expectsResponse */));
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




/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTestPendingReceiver = class {
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
        mojo.test.remoteUnittest.mojom.LargeMessageTest.$interfaceName,
        scope);
  }
};



/**
 * @export
 * @implements { mojo.test.remoteUnittest.mojom.LargeMessageTestInterface }
 */
mojo.test.remoteUnittest.mojom.LargeMessageTestRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.remoteUnittest.mojom.LargeMessageTestPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.remoteUnittest.mojom.LargeMessageTestPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.remoteUnittest.mojom.LargeMessageTestPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !Array<!number> } data
   * @return {!Promise<{
        dataSize: !bigint,
   *  }>}
   */

  processData(
      data) {
    return this.proxy.sendMessage(
        1798604899,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ResponseParamsSpec.$,
        [
          data
        ]);
  }

  
  /**
   * @param { !Array<!number> } data
   * @return {!Promise<{
        dataSize: !bigint,
   *  }>}
   */

  processLotsOfData(
      data) {
    return this.proxy.sendMessage(
        938167658,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ResponseParamsSpec.$,
        [
          data
        ]);
  }

  
  /**
   * @param { !bigint } dataSize
   * @return {!Promise<{
        data: !Array<!number>,
   *  }>}
   */

  getLotsOfData(
      dataSize) {
    return this.proxy.sendMessage(
        1545831854,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ResponseParamsSpec.$,
        [
          dataSize
        ]);
  }
};

/**
 * An object which receives request messages for the LargeMessageTest
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTestReceiver = class {
  /**
   * @param {!mojo.test.remoteUnittest.mojom.LargeMessageTestInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.remoteUnittest.mojom.LargeMessageTestRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.remoteUnittest.mojom.LargeMessageTestRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.remoteUnittest.mojom.LargeMessageTestRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        1798604899,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ResponseParamsSpec.$,
        impl.processData.bind(impl));
    this.helper_internal_.registerHandler(
        938167658,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ResponseParamsSpec.$,
        impl.processLotsOfData.bind(impl));
    this.helper_internal_.registerHandler(
        1545831854,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ResponseParamsSpec.$,
        impl.getLotsOfData.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTest = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.remote_unittest.mojom.LargeMessageTest";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.remoteUnittest.mojom.LargeMessageTestRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.remoteUnittest.mojom.LargeMessageTestRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the LargeMessageTest
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTestCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.remoteUnittest.mojom.LargeMessageTestRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.remoteUnittest.mojom.LargeMessageTestRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.processData =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1798604899,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ResponseParamsSpec.$,
        this.processData.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.processLotsOfData =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        938167658,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ResponseParamsSpec.$,
        this.processLotsOfData.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.getLotsOfData =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1545831854,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ParamsSpec.$,
        mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ResponseParamsSpec.$,
        this.getLotsOfData.createReceiverHandler(true /* expectsResponse */));
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



/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ParamsSpec.$,
    'SharedRemoteSyncTest_Fetch_Params',
    [
    ],
    [[0, 8],]);





/** @record */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_Params = class {
  constructor() {
  }
};




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ResponseParamsSpec.$,
    'SharedRemoteSyncTest_Fetch_ResponseParams',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.remoteUnittest.mojom.SharedRemoteSyncTest_Fetch_ResponseParams = class {
  constructor() {
    /** @export { !number } */
    this.value;
  }
};




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ParamsSpec.$,
    'LargeMessageTest_ProcessData_Params',
    [
      mojo.internal.StructField(
        'data', 0,
        0,
        mojo.internal.Array(mojo.internal.Uint8, false),
        null,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_Params = class {
  constructor() {
    /** @export { !Array<!number> } */
    this.data;
  }
};




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ResponseParamsSpec.$,
    'LargeMessageTest_ProcessData_ResponseParams',
    [
      mojo.internal.StructField(
        'dataSize', 0,
        0,
        mojo.internal.Uint64,
        BigInt(0),
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessData_ResponseParams = class {
  constructor() {
    /** @export { !bigint } */
    this.dataSize;
  }
};




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ParamsSpec.$,
    'LargeMessageTest_ProcessLotsOfData_Params',
    [
      mojo.internal.StructField(
        'data', 0,
        0,
        mojo.internal.Array(mojo.internal.Uint8, false),
        null,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_Params = class {
  constructor() {
    /** @export { !Array<!number> } */
    this.data;
  }
};




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ResponseParamsSpec.$,
    'LargeMessageTest_ProcessLotsOfData_ResponseParams',
    [
      mojo.internal.StructField(
        'dataSize', 0,
        0,
        mojo.internal.Uint64,
        BigInt(0),
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.remoteUnittest.mojom.LargeMessageTest_ProcessLotsOfData_ResponseParams = class {
  constructor() {
    /** @export { !bigint } */
    this.dataSize;
  }
};




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ParamsSpec.$,
    'LargeMessageTest_GetLotsOfData_Params',
    [
      mojo.internal.StructField(
        'dataSize', 0,
        0,
        mojo.internal.Uint64,
        BigInt(0),
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_Params = class {
  constructor() {
    /** @export { !bigint } */
    this.dataSize;
  }
};




mojo.internal.Struct(
    mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ResponseParamsSpec.$,
    'LargeMessageTest_GetLotsOfData_ResponseParams',
    [
      mojo.internal.StructField(
        'data', 0,
        0,
        mojo.internal.Array(mojo.internal.Uint8, false),
        null,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.remoteUnittest.mojom.LargeMessageTest_GetLotsOfData_ResponseParams = class {
  constructor() {
    /** @export { !Array<!number> } */
    this.data;
  }
};


