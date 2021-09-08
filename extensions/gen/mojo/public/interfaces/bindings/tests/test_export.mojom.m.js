// mojo/public/interfaces/bindings/tests/test_export.mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';




/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const ExportedInterfacePendingReceiver = class {
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
        this.handle, 'mojo.test.test_export.ExportedInterface', scope);
  }
};

/** @interface */
export const ExportedInterfaceInterface = class {
};

/**
 * @implements { ExportedInterfaceInterface }
 */
export const ExportedInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!ExportedInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          ExportedInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!ExportedInterfacePendingReceiver>}
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
 */
export const ExportedInterfaceReceiver = class {
  /**
   * @param {!ExportedInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!ExportedInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        ExportedInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!ExportedInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const ExportedInterface = class {
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
   * @return {!ExportedInterfaceRemote}
   */
  static getRemote() {
    let remote = new ExportedInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the ExportedInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const ExportedInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      ExportedInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!ExportedInterfaceRemote>}
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
export const StringPairSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const StringPairContainerSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    StringPairSpec.$,
    'StringPair',
    [
      mojo.internal.StructField(
        's1', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        's2', 8,
        0,
        mojo.internal.String,
        null,
        false /* nullable */,
        0),
    ],
    [[0, 24],]);



/**
 * @record
 */
export const StringPair = class {
  constructor() {
    /** @type { !string } */
    this.s1;
    /** @type { !string } */
    this.s2;
  }
};



mojo.internal.Struct(
    StringPairContainerSpec.$,
    'StringPairContainer',
    [
      mojo.internal.StructField(
        'pairs', 0,
        0,
        mojo.internal.Array(StringPairSpec.$, false),
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const StringPairContainer = class {
  constructor() {
    /** @type { !Array<!StringPair> } */
    this.pairs;
  }
};

