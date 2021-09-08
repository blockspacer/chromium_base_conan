// mojo/public/js/test/module_b_2.test-mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('moduleB');








/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
moduleB.TestInterfacePendingReceiver = class {
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
        moduleB.TestInterface.$interfaceName,
        scope);
  }
};



/**
 * @export
 * @implements { moduleB.TestInterfaceInterface }
 */
moduleB.TestInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!moduleB.TestInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          moduleB.TestInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!moduleB.TestInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !moduleA.TestStructA1 } a1
   */

  passA1(
      a1) {
    this.proxy.sendMessage(
        490516208,
        moduleB.TestInterface_PassA1_ParamsSpec.$,
        null,
        [
          a1
        ]);
  }

  
  /**
   * @param { !moduleB.TestStructB1 } b1
   */

  passB1(
      b1) {
    this.proxy.sendMessage(
        2037498148,
        moduleB.TestInterface_PassB1_ParamsSpec.$,
        null,
        [
          b1
        ]);
  }

  
  /**
   * @param { !moduleB.TestStructB2 } b2
   */

  passB2(
      b2) {
    this.proxy.sendMessage(
        212424705,
        moduleB.TestInterface_PassB2_ParamsSpec.$,
        null,
        [
          b2
        ]);
  }
};

/**
 * An object which receives request messages for the TestInterface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
moduleB.TestInterfaceReceiver = class {
  /**
   * @param {!moduleB.TestInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!moduleB.TestInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        moduleB.TestInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!moduleB.TestInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        490516208,
        moduleB.TestInterface_PassA1_ParamsSpec.$,
        null,
        impl.passA1.bind(impl));
    this.helper_internal_.registerHandler(
        2037498148,
        moduleB.TestInterface_PassB1_ParamsSpec.$,
        null,
        impl.passB1.bind(impl));
    this.helper_internal_.registerHandler(
        212424705,
        moduleB.TestInterface_PassB2_ParamsSpec.$,
        null,
        impl.passB2.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
moduleB.TestInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "module_b.TestInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!moduleB.TestInterfaceRemote}
   * @export
   */
  static getRemote() {
    let remote = new moduleB.TestInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the TestInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
moduleB.TestInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      moduleB.TestInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!moduleB.TestInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.passA1 =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        490516208,
        moduleB.TestInterface_PassA1_ParamsSpec.$,
        null,
        this.passA1.createReceiverHandler(false /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.passB1 =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        2037498148,
        moduleB.TestInterface_PassB1_ParamsSpec.$,
        null,
        this.passB1.createReceiverHandler(false /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.passB2 =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        212424705,
        moduleB.TestInterface_PassB2_ParamsSpec.$,
        null,
        this.passB2.createReceiverHandler(false /* expectsResponse */));
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
moduleB.TestStructB2Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
moduleB.TestInterface_PassA1_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
moduleB.TestInterface_PassB1_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
moduleB.TestInterface_PassB2_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    moduleB.TestStructB2Spec.$,
    'TestStructB2',
    [
      mojo.internal.StructField(
        'a1', 0,
        0,
        moduleA.TestStructA1Spec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'a2', 8,
        0,
        moduleA.TestStructA2Spec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'b2', 16,
        0,
        moduleB.TestStructB2Spec.$,
        null,
        false /* nullable */),
    ],
    [[0, 32],]);





/** @record */
moduleB.TestStructB2 = class {
  constructor() {
    /** @export { !moduleA.TestStructA1 } */
    this.a1;
    /** @export { !moduleA.TestStructA2 } */
    this.a2;
    /** @export { !moduleB.TestStructB2 } */
    this.b2;
  }
};




mojo.internal.Struct(
    moduleB.TestInterface_PassA1_ParamsSpec.$,
    'TestInterface_PassA1_Params',
    [
      mojo.internal.StructField(
        'a1', 0,
        0,
        moduleA.TestStructA1Spec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
moduleB.TestInterface_PassA1_Params = class {
  constructor() {
    /** @export { !moduleA.TestStructA1 } */
    this.a1;
  }
};




mojo.internal.Struct(
    moduleB.TestInterface_PassB1_ParamsSpec.$,
    'TestInterface_PassB1_Params',
    [
      mojo.internal.StructField(
        'b1', 0,
        0,
        moduleB.TestStructB1Spec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
moduleB.TestInterface_PassB1_Params = class {
  constructor() {
    /** @export { !moduleB.TestStructB1 } */
    this.b1;
  }
};




mojo.internal.Struct(
    moduleB.TestInterface_PassB2_ParamsSpec.$,
    'TestInterface_PassB2_Params',
    [
      mojo.internal.StructField(
        'b2', 0,
        0,
        moduleB.TestStructB2Spec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);





/** @record */
moduleB.TestInterface_PassB2_Params = class {
  constructor() {
    /** @export { !moduleB.TestStructB2 } */
    this.b2;
  }
};

