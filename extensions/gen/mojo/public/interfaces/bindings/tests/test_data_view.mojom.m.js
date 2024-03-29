// mojo/public/interfaces/bindings/tests/test_data_view.mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';


/**
 * @const { {$: !mojo.internal.MojomType} }
 */
export const TestEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 */
export const TestEnum = {
  
  VALUE_0: 0,
  VALUE_1: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};



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
        this.handle, 'mojo.test.data_view.TestInterface', scope);
  }
};

/** @interface */
export const TestInterfaceInterface = class {
  
  /**
   * @param { !number } value
   * @return {!Promise<{
        outValue: !number,
   *  }>}
   */

  echo(value) {}
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
   * @param { !number } value
   * @return {!Promise<{
        outValue: !number,
   *  }>}
   */

  echo(
      value) {
    return this.proxy.sendMessage(
        0,
        TestInterface_Echo_ParamsSpec.$,
        TestInterface_Echo_ResponseParamsSpec.$,
        [
          value
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
        0,
        TestInterface_Echo_ParamsSpec.$,
        TestInterface_Echo_ResponseParamsSpec.$,
        impl.echo.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const TestInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.data_view.TestInterface";
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
    this.echo =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        0,
        TestInterface_Echo_ParamsSpec.$,
        TestInterface_Echo_ResponseParamsSpec.$,
        this.echo.createReceiverHandler(true /* expectsResponse */));
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
export const NestedStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestNativeStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestInterface_Echo_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const TestInterface_Echo_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType} }
 */
export const TestUnionSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    NestedStructSpec.$,
    'NestedStruct',
    [
      mojo.internal.StructField(
        'fInt32', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const NestedStruct = class {
  constructor() {
    /** @type { !number } */
    this.fInt32;
  }
};



mojo.internal.Struct(
    TestNativeStructSpec.$,
    'TestNativeStruct',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const TestNativeStruct = class {
  constructor() {
  }
};



mojo.internal.Struct(
    TestStructSpec.$,
    'TestStruct',
    [
      mojo.internal.StructField(
        'fString', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fStruct', 8,
        0,
        NestedStructSpec.$,
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'fNativeStruct', 16,
        0,
        TestNativeStructSpec.$,
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'fBoolArray', 24,
        0,
        mojo.internal.Array(mojo.internal.Bool, false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fInt32Array', 32,
        0,
        mojo.internal.Array(mojo.internal.Int32, false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fEnumArray', 40,
        0,
        mojo.internal.Array(TestEnumSpec.$, false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fInterfaceArray', 48,
        0,
        mojo.internal.Array(mojo.internal.InterfaceProxy(TestInterfaceRemote), false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fNestedArray', 56,
        0,
        mojo.internal.Array(mojo.internal.Array(mojo.internal.Int32, false), false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fStructArray', 64,
        0,
        mojo.internal.Array(NestedStructSpec.$, false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fUnionArray', 72,
        0,
        mojo.internal.Array(TestUnionSpec.$, false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'fMap', 80,
        0,
        mojo.internal.Map(mojo.internal.String, mojo.internal.Int32, false),
        null,
        false /* nullable */,
        0),
    ],
    [[0, 96],]);



/**
 * @record
 */
export const TestStruct = class {
  constructor() {
    /** @type { !string } */
    this.fString;
    /** @type { (NestedStruct|undefined) } */
    this.fStruct;
    /** @type { (TestNativeStruct|undefined) } */
    this.fNativeStruct;
    /** @type { !Array<!boolean> } */
    this.fBoolArray;
    /** @type { !Array<!number> } */
    this.fInt32Array;
    /** @type { !Array<!TestEnum> } */
    this.fEnumArray;
    /** @type { !Array<!TestInterfaceRemote> } */
    this.fInterfaceArray;
    /** @type { !Array<!Array<!number>> } */
    this.fNestedArray;
    /** @type { !Array<!NestedStruct> } */
    this.fStructArray;
    /** @type { !Array<!TestUnion> } */
    this.fUnionArray;
    /** @type { !Object<!string, !number> } */
    this.fMap;
  }
};



mojo.internal.Struct(
    TestInterface_Echo_ParamsSpec.$,
    'TestInterface_Echo_Params',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const TestInterface_Echo_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};



mojo.internal.Struct(
    TestInterface_Echo_ResponseParamsSpec.$,
    'TestInterface_Echo_ResponseParams',
    [
      mojo.internal.StructField(
        'outValue', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const TestInterface_Echo_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.outValue;
  }
};

mojo.internal.Union(
    TestUnionSpec.$, 'TestUnion',
    {
      'fBool': {
        'ordinal': 0,
        'type': mojo.internal.Bool,
      },
      'fInt32': {
        'ordinal': 1,
        'type': mojo.internal.Int32,
      },
    });

/**
 * @typedef { {
 *   fBool: (!boolean|undefined),
 *   fInt32: (!number|undefined),
 * } }
 */
export const TestUnion = {};
