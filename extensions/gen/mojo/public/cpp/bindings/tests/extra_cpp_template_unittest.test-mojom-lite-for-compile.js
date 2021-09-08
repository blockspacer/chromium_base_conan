// mojo/public/cpp/bindings/tests/extra_cpp_template_unittest.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');







goog.provide('mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterface');
goog.provide('mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceReceiver');
goog.provide('mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceCallbackRouter');
goog.provide('mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceInterface');
goog.provide('mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote');
goog.provide('mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfacePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfacePendingReceiver = class {
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
        mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterface.$interfaceName,
        scope);
  }
};

/** @interface */
mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceInterface = class {
};

/**
 * @export
 * @implements { mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceInterface }
 */
mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }
};

/**
 * An object which receives request messages for the ExtraCppInterface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceReceiver = class {
  /**
   * @param {!mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.extra_cpp_template_unittest.mojom.ExtraCppInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the ExtraCppInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.extraCppTemplateUnittest.mojom.ExtraCppInterfaceRemote>}
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



