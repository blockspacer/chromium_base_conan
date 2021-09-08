// mojo/public/cpp/bindings/tests/connection_group_unittest.test-mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';




/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const TestInterfacePendingReceiver = class {
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
        this.handle, 'mojo.test.connection_group_unittest.mojom.TestInterface', scope);
  }
};

/** @interface */
export const TestInterfaceInterface = class {
  
  /**
   * @param { !TestInterfacePendingReceiver } receiver
   */

  bindReceiver(receiver) {}
};

/**
 * @implements { TestInterfaceInterface }
 */
export const TestInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!TestInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          TestInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!TestInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !TestInterfacePendingReceiver } receiver
   */

  bindReceiver(
      receiver) {
    this.proxy.sendMessage(
        490516208,
        TestInterface_BindReceiver_ParamsSpec.$,
        null,
        [
          receiver
        ]);
  }
};

/**
 * An object which receives request messages for the TestInterface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 */
export const TestInterfaceReceiver = class {
  /**
   * @param {!TestInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!TestInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        TestInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!TestInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        490516208,
        TestInterface_BindReceiver_ParamsSpec.$,
        null,
        impl.bindReceiver.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const TestInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.connection_group_unittest.mojom.TestInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!TestInterfaceRemote}
   */
  static getRemote() {
    let remote = new TestInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the TestInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const TestInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      TestInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!TestInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.bindReceiver =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        490516208,
        TestInterface_BindReceiver_ParamsSpec.$,
        null,
        this.bindReceiver.createReceiverHandler(false /* expectsResponse */));
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
export const TestInterface_BindReceiver_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    TestInterface_BindReceiver_ParamsSpec.$,
    'TestInterface_BindReceiver_Params',
    [
      mojo.internal.StructField(
        'receiver', 0,
        0,
        mojo.internal.InterfaceRequest(TestInterfacePendingReceiver),
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const TestInterface_BindReceiver_Params = class {
  constructor() {
    /** @type { !TestInterfacePendingReceiver } */
    this.receiver;
  }
};
