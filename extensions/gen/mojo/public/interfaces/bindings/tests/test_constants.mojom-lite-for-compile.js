// mojo/public/interfaces/bindings/tests/test_constants.mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');




goog.provide('mojo.test.BOOL_VALUE');
/**
 * @const { !boolean }
 * @export
 */
mojo.test.BOOL_VALUE = true;
goog.provide('mojo.test.INT8_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.INT8_VALUE = -2;
goog.provide('mojo.test.UINT8_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.UINT8_VALUE = 128;
goog.provide('mojo.test.INT16_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.INT16_VALUE = -233;
goog.provide('mojo.test.UINT16_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.UINT16_VALUE = 44204;
goog.provide('mojo.test.INT32_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.INT32_VALUE = -44204;
goog.provide('mojo.test.UINT32_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.UINT32_VALUE = 4294967295;
goog.provide('mojo.test.INT64_VALUE');
/**
 * @const { !bigint }
 * @export
 */
mojo.test.INT64_VALUE = BigInt('-9223372036854775807');
goog.provide('mojo.test.UINT64_VALUE');
/**
 * @const { !bigint }
 * @export
 */
mojo.test.UINT64_VALUE = BigInt('9999999999999999999');
goog.provide('mojo.test.DOUBLE_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.DOUBLE_VALUE = 3.14159;
goog.provide('mojo.test.DOUBLE_INFINITY');
/**
 * @const { !number }
 * @export
 */
mojo.test.DOUBLE_INFINITY = Infinity;
goog.provide('mojo.test.DOUBLE_NEGATIVE_INFINITY');
/**
 * @const { !number }
 * @export
 */
mojo.test.DOUBLE_NEGATIVE_INFINITY = -Infinity;
goog.provide('mojo.test.DOUBLE_NA_N');
/**
 * @const { !number }
 * @export
 */
mojo.test.DOUBLE_NA_N = NaN;
goog.provide('mojo.test.FLOAT_VALUE');
/**
 * @const { !number }
 * @export
 */
mojo.test.FLOAT_VALUE = 2.71828;
goog.provide('mojo.test.FLOAT_INFINITY');
/**
 * @const { !number }
 * @export
 */
mojo.test.FLOAT_INFINITY = Infinity;
goog.provide('mojo.test.FLOAT_NEGATIVE_INFINITY');
/**
 * @const { !number }
 * @export
 */
mojo.test.FLOAT_NEGATIVE_INFINITY = -Infinity;
goog.provide('mojo.test.FLOAT_NA_N');
/**
 * @const { !number }
 * @export
 */
mojo.test.FLOAT_NA_N = NaN;
goog.provide('mojo.test.STRING_VALUE');
/**
 * @const { !string }
 * @export
 */
mojo.test.STRING_VALUE = "test string contents";



goog.provide('mojo.test.InterfaceWithConstants');
goog.provide('mojo.test.InterfaceWithConstantsReceiver');
goog.provide('mojo.test.InterfaceWithConstantsCallbackRouter');
goog.provide('mojo.test.InterfaceWithConstantsInterface');
goog.provide('mojo.test.InterfaceWithConstantsRemote');
goog.provide('mojo.test.InterfaceWithConstantsPendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.InterfaceWithConstantsPendingReceiver = class {
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
        mojo.test.InterfaceWithConstants.$interfaceName,
        scope);
  }
};

/** @interface */
mojo.test.InterfaceWithConstantsInterface = class {
};

/**
 * @export
 * @implements { mojo.test.InterfaceWithConstantsInterface }
 */
mojo.test.InterfaceWithConstantsRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.InterfaceWithConstantsPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.InterfaceWithConstantsPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.InterfaceWithConstantsPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }
};

/**
 * An object which receives request messages for the InterfaceWithConstants
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.InterfaceWithConstantsReceiver = class {
  /**
   * @param {!mojo.test.InterfaceWithConstantsInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.InterfaceWithConstantsRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.InterfaceWithConstantsRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.InterfaceWithConstantsRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.InterfaceWithConstants = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.InterfaceWithConstants";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.InterfaceWithConstantsRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.InterfaceWithConstantsRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the InterfaceWithConstants
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.InterfaceWithConstantsCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.InterfaceWithConstantsRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.InterfaceWithConstantsRemote>}
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


goog.provide('mojo.test.StructWithConstantsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.StructWithConstantsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { !number }
 * @export
 */
mojo.test.StructWithConstants_INT8_VALUE =
    5;

/**
 * @const { !number }
 * @export
 */
mojo.test.StructWithConstants_FLOAT_VALUE =
    765.432;

/**
 * @const { !string }
 * @export
 */
mojo.test.StructWithConstants_STRING_VALUE =
    "struct test string contents";



mojo.internal.Struct(
    mojo.test.StructWithConstantsSpec.$,
    'StructWithConstants',
    [
    ],
    [[0, 8],]);



goog.provide('mojo.test.StructWithConstants');

/** @record */
mojo.test.StructWithConstants = class {
  constructor() {
  }
};


