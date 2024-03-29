// mojo/public/interfaces/bindings/tests/test_export.mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');







goog.provide('mojo.test.testExport.ExportedInterface');
goog.provide('mojo.test.testExport.ExportedInterfaceReceiver');
goog.provide('mojo.test.testExport.ExportedInterfaceCallbackRouter');
goog.provide('mojo.test.testExport.ExportedInterfaceInterface');
goog.provide('mojo.test.testExport.ExportedInterfaceRemote');
goog.provide('mojo.test.testExport.ExportedInterfacePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.testExport.ExportedInterfacePendingReceiver = class {
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
        mojo.test.testExport.ExportedInterface.$interfaceName,
        scope);
  }
};

/** @interface */
mojo.test.testExport.ExportedInterfaceInterface = class {
};

/**
 * @export
 * @implements { mojo.test.testExport.ExportedInterfaceInterface }
 */
mojo.test.testExport.ExportedInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.testExport.ExportedInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.testExport.ExportedInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.testExport.ExportedInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }
};

/**
 * An object which receives request messages for the ExportedInterface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.testExport.ExportedInterfaceReceiver = class {
  /**
   * @param {!mojo.test.testExport.ExportedInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.testExport.ExportedInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.testExport.ExportedInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.testExport.ExportedInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.testExport.ExportedInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.test_export.ExportedInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.testExport.ExportedInterfaceRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.testExport.ExportedInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the ExportedInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.testExport.ExportedInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.testExport.ExportedInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.testExport.ExportedInterfaceRemote>}
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


goog.provide('mojo.test.testExport.StringPairSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.testExport.StringPairSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.testExport.StringPairContainerSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.testExport.StringPairContainerSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.testExport.StringPairSpec.$,
    'StringPair',
    [
      mojo.internal.StructField(
        's1', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        's2', 8,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('mojo.test.testExport.StringPair');

/** @record */
mojo.test.testExport.StringPair = class {
  constructor() {
    /** @export { !string } */
    this.s1;
    /** @export { !string } */
    this.s2;
  }
};




mojo.internal.Struct(
    mojo.test.testExport.StringPairContainerSpec.$,
    'StringPairContainer',
    [
      mojo.internal.StructField(
        'pairs', 0,
        0,
        mojo.internal.Array(mojo.test.testExport.StringPairSpec.$, false),
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.testExport.StringPairContainer');

/** @record */
mojo.test.testExport.StringPairContainer = class {
  constructor() {
    /** @export { !Array<!mojo.test.testExport.StringPair> } */
    this.pairs;
  }
};


