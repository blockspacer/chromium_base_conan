// mojo/public/interfaces/bindings/tests/test_bad_messages.mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';




/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const TestBadMessagesPendingReceiver = class {
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
        this.handle, 'mojo.test.TestBadMessages', scope);
  }
};

/** @interface */
export const TestBadMessagesInterface = class {
  
  /**
   * @return {!Promise}
   */

  rejectEventually() {}
  
  /**
   * @return {!Promise}
   */

  requestResponse() {}
  
  /**
   * @return {!Promise}
   */

  rejectSync() {}
  
  /**
   * @return {!Promise}
   */

  requestResponseSync() {}
};

/**
 * @implements { TestBadMessagesInterface }
 */
export const TestBadMessagesRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!TestBadMessagesPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          TestBadMessagesPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!TestBadMessagesPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @return {!Promise}
   */

  rejectEventually() {
    return this.proxy.sendMessage(
        0,
        TestBadMessages_RejectEventually_ParamsSpec.$,
        TestBadMessages_RejectEventually_ResponseParamsSpec.$,
        [
        ]);
  }

  
  /**
   * @return {!Promise}
   */

  requestResponse() {
    return this.proxy.sendMessage(
        1,
        TestBadMessages_RequestResponse_ParamsSpec.$,
        TestBadMessages_RequestResponse_ResponseParamsSpec.$,
        [
        ]);
  }

  
  /**
   * @return {!Promise}
   */

  rejectSync() {
    return this.proxy.sendMessage(
        2,
        TestBadMessages_RejectSync_ParamsSpec.$,
        TestBadMessages_RejectSync_ResponseParamsSpec.$,
        [
        ]);
  }

  
  /**
   * @return {!Promise}
   */

  requestResponseSync() {
    return this.proxy.sendMessage(
        3,
        TestBadMessages_RequestResponseSync_ParamsSpec.$,
        TestBadMessages_RequestResponseSync_ResponseParamsSpec.$,
        [
        ]);
  }
};

/**
 * An object which receives request messages for the TestBadMessages
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 */
export const TestBadMessagesReceiver = class {
  /**
   * @param {!TestBadMessagesInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!TestBadMessagesRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        TestBadMessagesRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!TestBadMessagesRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        TestBadMessages_RejectEventually_ParamsSpec.$,
        TestBadMessages_RejectEventually_ResponseParamsSpec.$,
        impl.rejectEventually.bind(impl));
    this.helper_internal_.registerHandler(
        1,
        TestBadMessages_RequestResponse_ParamsSpec.$,
        TestBadMessages_RequestResponse_ResponseParamsSpec.$,
        impl.requestResponse.bind(impl));
    this.helper_internal_.registerHandler(
        2,
        TestBadMessages_RejectSync_ParamsSpec.$,
        TestBadMessages_RejectSync_ResponseParamsSpec.$,
        impl.rejectSync.bind(impl));
    this.helper_internal_.registerHandler(
        3,
        TestBadMessages_RequestResponseSync_ParamsSpec.$,
        TestBadMessages_RequestResponseSync_ResponseParamsSpec.$,
        impl.requestResponseSync.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const TestBadMessages = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.TestBadMessages";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!TestBadMessagesRemote}
   */
  static getRemote() {
    let remote = new TestBadMessagesRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the TestBadMessages
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const TestBadMessagesCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      TestBadMessagesRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!TestBadMessagesRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.rejectEventually =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        0,
        TestBadMessages_RejectEventually_ParamsSpec.$,
        TestBadMessages_RejectEventually_ResponseParamsSpec.$,
        this.rejectEventually.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.requestResponse =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1,
        TestBadMessages_RequestResponse_ParamsSpec.$,
        TestBadMessages_RequestResponse_ResponseParamsSpec.$,
        this.requestResponse.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.rejectSync =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        2,
        TestBadMessages_RejectSync_ParamsSpec.$,
        TestBadMessages_RejectSync_ResponseParamsSpec.$,
        this.rejectSync.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.requestResponseSync =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        3,
        TestBadMessages_RequestResponseSync_ParamsSpec.$,
        TestBadMessages_RequestResponseSync_ResponseParamsSpec.$,
        this.requestResponseSync.createReceiverHandler(true /* expectsResponse */));
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
export const TestBadMessages_RejectEventually_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestBadMessages_RejectEventually_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestBadMessages_RequestResponse_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestBadMessages_RequestResponse_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestBadMessages_RejectSync_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestBadMessages_RejectSync_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestBadMessages_RequestResponseSync_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestBadMessages_RequestResponseSync_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    TestBadMessages_RejectEventually_ParamsSpec.$,
    'TestBadMessages_RejectEventually_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RejectEventually_Params = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestBadMessages_RejectEventually_ResponseParamsSpec.$,
    'TestBadMessages_RejectEventually_ResponseParams',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RejectEventually_ResponseParams = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestBadMessages_RequestResponse_ParamsSpec.$,
    'TestBadMessages_RequestResponse_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RequestResponse_Params = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestBadMessages_RequestResponse_ResponseParamsSpec.$,
    'TestBadMessages_RequestResponse_ResponseParams',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RequestResponse_ResponseParams = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestBadMessages_RejectSync_ParamsSpec.$,
    'TestBadMessages_RejectSync_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RejectSync_Params = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestBadMessages_RejectSync_ResponseParamsSpec.$,
    'TestBadMessages_RejectSync_ResponseParams',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RejectSync_ResponseParams = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestBadMessages_RequestResponseSync_ParamsSpec.$,
    'TestBadMessages_RequestResponseSync_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RequestResponseSync_Params = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestBadMessages_RequestResponseSync_ResponseParamsSpec.$,
    'TestBadMessages_RequestResponseSync_ResponseParams',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestBadMessages_RequestResponseSync_ResponseParams = class {
  constructor() {
  }
};
