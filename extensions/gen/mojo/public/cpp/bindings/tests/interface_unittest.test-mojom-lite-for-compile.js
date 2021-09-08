// mojo/public/cpp/bindings/tests/interface_unittest.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');







goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterface');
goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceReceiver');
goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceCallbackRouter');
goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceInterface');
goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote');
goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterfacePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.interfaceUnittest.mojom.VeryCoolInterfacePendingReceiver = class {
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
        mojo.test.interfaceUnittest.mojom.VeryCoolInterface.$interfaceName,
        scope);
  }
};

/** @interface */
mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceInterface = class {
  
  /**
   */

  doesNotMatter() {}
};

/**
 * @export
 * @implements { mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceInterface }
 */
mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.interfaceUnittest.mojom.VeryCoolInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.interfaceUnittest.mojom.VeryCoolInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.interfaceUnittest.mojom.VeryCoolInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   */

  doesNotMatter() {
    this.proxy.sendMessage(
        1279067163,
        mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_ParamsSpec.$,
        null,
        [
        ]);
  }
};

/**
 * An object which receives request messages for the VeryCoolInterface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceReceiver = class {
  /**
   * @param {!mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        1279067163,
        mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_ParamsSpec.$,
        null,
        impl.doesNotMatter.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.interfaceUnittest.mojom.VeryCoolInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.interface_unittest.mojom.VeryCoolInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the VeryCoolInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.interfaceUnittest.mojom.VeryCoolInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.doesNotMatter =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1279067163,
        mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_ParamsSpec.$,
        null,
        this.doesNotMatter.createReceiverHandler(false /* expectsResponse */));
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


goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_ParamsSpec.$,
    'VeryCoolInterface_DoesNotMatter_Params',
    [
    ],
    [[0, 8],]);



goog.provide('mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_Params');

/** @record */
mojo.test.interfaceUnittest.mojom.VeryCoolInterface_DoesNotMatter_Params = class {
  constructor() {
  }
};


