// mojo/public/cpp/test/module.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');




goog.provide('testModule.GLOBAL_CONST');
/**
 * @const { !string }
 * @export
 */
testModule.GLOBAL_CONST = "testString";

goog.provide('testModule.GlobalEnum');
goog.provide('testModule.GlobalEnumSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
testModule.GlobalEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
testModule.GlobalEnum = {
  
  FIRST: 0,
  SECOND: 2,
  MIN_VALUE: 0,
  MAX_VALUE: 2,
};



goog.provide('testModule.Interface');
goog.provide('testModule.InterfaceReceiver');
goog.provide('testModule.InterfaceCallbackRouter');
goog.provide('testModule.InterfaceInterface');
goog.provide('testModule.InterfaceRemote');
goog.provide('testModule.InterfacePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
testModule.InterfacePendingReceiver = class {
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
        testModule.Interface.$interfaceName,
        scope);
  }
};

/** @interface */
testModule.InterfaceInterface = class {
  
  /**
   */

  doSomething() {}
  
  /**
   * @param { !testModule.Struct } s
   * @return {!Promise<{
        e: !testModule.GlobalEnum,
   *  }>}
   */

  doSomethingElse(s) {}
};

/**
 * @export
 * @implements { testModule.InterfaceInterface }
 */
testModule.InterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!testModule.InterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          testModule.InterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!testModule.InterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   */

  doSomething() {
    this.proxy.sendMessage(
        456169886,
        testModule.Interface_DoSomething_ParamsSpec.$,
        null,
        [
        ]);
  }

  
  /**
   * @param { !testModule.Struct } s
   * @return {!Promise<{
        e: !testModule.GlobalEnum,
   *  }>}
   */

  doSomethingElse(
      s) {
    return this.proxy.sendMessage(
        1588538935,
        testModule.Interface_DoSomethingElse_ParamsSpec.$,
        testModule.Interface_DoSomethingElse_ResponseParamsSpec.$,
        [
          s
        ]);
  }
};

/**
 * An object which receives request messages for the Interface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
testModule.InterfaceReceiver = class {
  /**
   * @param {!testModule.InterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!testModule.InterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        testModule.InterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!testModule.InterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        456169886,
        testModule.Interface_DoSomething_ParamsSpec.$,
        null,
        impl.doSomething.bind(impl));
    this.helper_internal_.registerHandler(
        1588538935,
        testModule.Interface_DoSomethingElse_ParamsSpec.$,
        testModule.Interface_DoSomethingElse_ResponseParamsSpec.$,
        impl.doSomethingElse.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
testModule.Interface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "test_module.Interface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!testModule.InterfaceRemote}
   * @export
   */
  static getRemote() {
    let remote = new testModule.InterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};

goog.provide('testModule.Interface_InterfaceEnum');
goog.provide('testModule.Interface.InterfaceEnumSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
testModule.Interface.InterfaceEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
testModule.Interface_InterfaceEnum = {
  
  FIFTH: 0,
  SIXTH: 6,
  MIN_VALUE: 0,
  MAX_VALUE: 6,
};

/**
 * An object which receives request messages for the Interface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
testModule.InterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      testModule.InterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!testModule.InterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.doSomething =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        456169886,
        testModule.Interface_DoSomething_ParamsSpec.$,
        null,
        this.doSomething.createReceiverHandler(false /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.doSomethingElse =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1588538935,
        testModule.Interface_DoSomethingElse_ParamsSpec.$,
        testModule.Interface_DoSomethingElse_ResponseParamsSpec.$,
        this.doSomethingElse.createReceiverHandler(true /* expectsResponse */));
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


goog.provide('testModule.StructSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
testModule.StructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('testModule.Interface_DoSomething_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
testModule.Interface_DoSomething_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('testModule.Interface_DoSomethingElse_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
testModule.Interface_DoSomethingElse_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('testModule.Interface_DoSomethingElse_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
testModule.Interface_DoSomethingElse_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('testModule.UnionSpec');
/**
 * @const { {$:!mojo.internal.MojomType} }
 * @export
 */
testModule.UnionSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { !string }
 * @export
 */
testModule.Struct_STRUCT_CONST =
    "structConst";


goog.provide('testModule.Struct_StructEnum');
goog.provide('testModule.StructSpec.StructEnumSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
testModule.StructSpec.StructEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
testModule.Struct_StructEnum = {
  
  SECOND: 0,
  THIRD: 1,
  FOURTH: 4,
  MIN_VALUE: 0,
  MAX_VALUE: 4,
};


mojo.internal.Struct(
    testModule.StructSpec.$,
    'Struct',
    [
      mojo.internal.StructField(
        'c', 0,
        0,
        mojo.internal.Bool,
        false,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('testModule.Struct');

/** @record */
testModule.Struct = class {
  constructor() {
    /** @export { !boolean } */
    this.c;
  }
};




mojo.internal.Struct(
    testModule.Interface_DoSomething_ParamsSpec.$,
    'Interface_DoSomething_Params',
    [
    ],
    [[0, 8],]);



goog.provide('testModule.Interface_DoSomething_Params');

/** @record */
testModule.Interface_DoSomething_Params = class {
  constructor() {
  }
};




mojo.internal.Struct(
    testModule.Interface_DoSomethingElse_ParamsSpec.$,
    'Interface_DoSomethingElse_Params',
    [
      mojo.internal.StructField(
        's', 0,
        0,
        testModule.StructSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('testModule.Interface_DoSomethingElse_Params');

/** @record */
testModule.Interface_DoSomethingElse_Params = class {
  constructor() {
    /** @export { !testModule.Struct } */
    this.s;
  }
};




mojo.internal.Struct(
    testModule.Interface_DoSomethingElse_ResponseParamsSpec.$,
    'Interface_DoSomethingElse_ResponseParams',
    [
      mojo.internal.StructField(
        'e', 0,
        0,
        testModule.GlobalEnumSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('testModule.Interface_DoSomethingElse_ResponseParams');

/** @record */
testModule.Interface_DoSomethingElse_ResponseParams = class {
  constructor() {
    /** @export { !testModule.GlobalEnum } */
    this.e;
  }
};


goog.provide('testModule.Union');


mojo.internal.Union(
    testModule.UnionSpec.$, 'Union',
    {
      'a': {
        'ordinal': 0,
        'type': mojo.internal.Bool,
      },
      'b': {
        'ordinal': 1,
        'type': mojo.internal.Int64,
      },
    });

/**
 * @typedef { {
 *   a: (!boolean|undefined),
 *   b: (!bigint|undefined),
 * } }
 */
testModule.Union;
