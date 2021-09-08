// mojo/public/js/test/module_a.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');





goog.provide('moduleA.ModuleEnum');
goog.provide('moduleA.ModuleEnumSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
moduleA.ModuleEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
moduleA.ModuleEnum = {
  
  THIRD: 0,
  MIN_VALUE: 0,
  MAX_VALUE: 0,
};



goog.provide('moduleA.ParentInterface');
goog.provide('moduleA.ParentInterfaceReceiver');
goog.provide('moduleA.ParentInterfaceCallbackRouter');
goog.provide('moduleA.ParentInterfaceInterface');
goog.provide('moduleA.ParentInterfaceRemote');
goog.provide('moduleA.ParentInterfacePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
moduleA.ParentInterfacePendingReceiver = class {
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
        moduleA.ParentInterface.$interfaceName,
        scope);
  }
};

/** @interface */
moduleA.ParentInterfaceInterface = class {
  
  /**
   * @param { !moduleA.ParentInterface_NestedEnum } value
   */

  someMethod(value) {}
};

/**
 * @export
 * @implements { moduleA.ParentInterfaceInterface }
 */
moduleA.ParentInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!moduleA.ParentInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          moduleA.ParentInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!moduleA.ParentInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !moduleA.ParentInterface_NestedEnum } value
   */

  someMethod(
      value) {
    this.proxy.sendMessage(
        652447188,
        moduleA.ParentInterface_SomeMethod_ParamsSpec.$,
        null,
        [
          value
        ]);
  }
};

/**
 * An object which receives request messages for the ParentInterface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
moduleA.ParentInterfaceReceiver = class {
  /**
   * @param {!moduleA.ParentInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!moduleA.ParentInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        moduleA.ParentInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!moduleA.ParentInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        652447188,
        moduleA.ParentInterface_SomeMethod_ParamsSpec.$,
        null,
        impl.someMethod.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
moduleA.ParentInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "module_a.ParentInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!moduleA.ParentInterfaceRemote}
   * @export
   */
  static getRemote() {
    let remote = new moduleA.ParentInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};

goog.provide('moduleA.ParentInterface_NestedEnum');
goog.provide('moduleA.ParentInterface.NestedEnumSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
moduleA.ParentInterface.NestedEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
moduleA.ParentInterface_NestedEnum = {
  
  FIRST: 0,
  SECOND: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};

/**
 * An object which receives request messages for the ParentInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
moduleA.ParentInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      moduleA.ParentInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!moduleA.ParentInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.someMethod =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        652447188,
        moduleA.ParentInterface_SomeMethod_ParamsSpec.$,
        null,
        this.someMethod.createReceiverHandler(false /* expectsResponse */));
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


goog.provide('moduleA.TestStructA1Spec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
moduleA.TestStructA1Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('moduleA.TestStructA2Spec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
moduleA.TestStructA2Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('moduleA.ParentInterface_SomeMethod_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
moduleA.ParentInterface_SomeMethod_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    moduleA.TestStructA1Spec.$,
    'TestStructA1',
    [
      mojo.internal.StructField(
        'q', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'r', 8,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        's', 16,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
    ],
    [[0, 32],]);



goog.provide('moduleA.TestStructA1');

/** @record */
moduleA.TestStructA1 = class {
  constructor() {
    /** @export { !string } */
    this.q;
    /** @export { !string } */
    this.r;
    /** @export { !string } */
    this.s;
  }
};



goog.provide('moduleA.TestStructA2_NestedEnum');
goog.provide('moduleA.TestStructA2Spec.NestedEnumSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
moduleA.TestStructA2Spec.NestedEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
moduleA.TestStructA2_NestedEnum = {
  
  A: 0,
  B: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};


mojo.internal.Struct(
    moduleA.TestStructA2Spec.$,
    'TestStructA2',
    [
      mojo.internal.StructField(
        'ax', 0,
        0,
        moduleA.TestStructA1Spec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'ay', 8,
        0,
        moduleA.TestStructA1Spec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'enumField', 16,
        0,
        moduleA.TestStructA2Spec.NestedEnumSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 32],]);



goog.provide('moduleA.TestStructA2');

/** @record */
moduleA.TestStructA2 = class {
  constructor() {
    /** @export { !moduleA.TestStructA1 } */
    this.ax;
    /** @export { !moduleA.TestStructA1 } */
    this.ay;
    /** @export { !moduleA.TestStructA2_NestedEnum } */
    this.enumField;
  }
};




mojo.internal.Struct(
    moduleA.ParentInterface_SomeMethod_ParamsSpec.$,
    'ParentInterface_SomeMethod_Params',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        moduleA.ParentInterface.NestedEnumSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('moduleA.ParentInterface_SomeMethod_Params');

/** @record */
moduleA.ParentInterface_SomeMethod_Params = class {
  constructor() {
    /** @export { !moduleA.ParentInterface_NestedEnum } */
    this.value;
  }
};


