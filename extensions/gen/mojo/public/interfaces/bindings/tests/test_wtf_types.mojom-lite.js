// mojo/public/interfaces/bindings/tests/test_wtf_types.mojom-lite.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';


mojo.internal.exportModule('mojo.test');





/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
mojo.test.TopLevelEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
mojo.test.TopLevelEnum = {
  
  E0: 0,
  E1: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};





/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.TestWTFPendingReceiver = class {
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
        mojo.test.TestWTF.$interfaceName,
        scope);
  }
};



/**
 * @export
 * @implements { mojo.test.TestWTFInterface }
 */
mojo.test.TestWTFRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.TestWTFPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.TestWTFPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.TestWTFPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { ?string } str
   * @return {!Promise<{
        str: ?string,
   *  }>}
   */

  echoString(
      str) {
    return this.proxy.sendMessage(
        1213665199,
        mojo.test.TestWTF_EchoString_ParamsSpec.$,
        mojo.test.TestWTF_EchoString_ResponseParamsSpec.$,
        [
          str
        ]);
  }

  
  /**
   * @param { ?Array<?string> } arr
   * @return {!Promise<{
        arr: ?Array<?string>,
   *  }>}
   */

  echoStringArray(
      arr) {
    return this.proxy.sendMessage(
        1249773810,
        mojo.test.TestWTF_EchoStringArray_ParamsSpec.$,
        mojo.test.TestWTF_EchoStringArray_ResponseParamsSpec.$,
        [
          arr
        ]);
  }

  
  /**
   * @param { ?Object<!string, ?string> } strMap
   * @return {!Promise<{
        strMap: ?Object<!string, ?string>,
   *  }>}
   */

  echoStringMap(
      strMap) {
    return this.proxy.sendMessage(
        787768058,
        mojo.test.TestWTF_EchoStringMap_ParamsSpec.$,
        mojo.test.TestWTF_EchoStringMap_ResponseParamsSpec.$,
        [
          strMap
        ]);
  }
};

/**
 * An object which receives request messages for the TestWTF
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
mojo.test.TestWTFReceiver = class {
  /**
   * @param {!mojo.test.TestWTFInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.TestWTFRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.TestWTFRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.TestWTFRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        1213665199,
        mojo.test.TestWTF_EchoString_ParamsSpec.$,
        mojo.test.TestWTF_EchoString_ResponseParamsSpec.$,
        impl.echoString.bind(impl));
    this.helper_internal_.registerHandler(
        1249773810,
        mojo.test.TestWTF_EchoStringArray_ParamsSpec.$,
        mojo.test.TestWTF_EchoStringArray_ResponseParamsSpec.$,
        impl.echoStringArray.bind(impl));
    this.helper_internal_.registerHandler(
        787768058,
        mojo.test.TestWTF_EchoStringMap_ParamsSpec.$,
        mojo.test.TestWTF_EchoStringMap_ResponseParamsSpec.$,
        impl.echoStringMap.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.TestWTF = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.TestWTF";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.TestWTFRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.TestWTFRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
mojo.test.TestWTF.NestedEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
mojo.test.TestWTF_NestedEnum = {
  
  E0: 0,
  E1: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};

/**
 * An object which receives request messages for the TestWTF
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
mojo.test.TestWTFCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.TestWTFRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.TestWTFRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoString =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1213665199,
        mojo.test.TestWTF_EchoString_ParamsSpec.$,
        mojo.test.TestWTF_EchoString_ResponseParamsSpec.$,
        this.echoString.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoStringArray =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1249773810,
        mojo.test.TestWTF_EchoStringArray_ParamsSpec.$,
        mojo.test.TestWTF_EchoStringArray_ResponseParamsSpec.$,
        this.echoStringArray.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoStringMap =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        787768058,
        mojo.test.TestWTF_EchoStringMap_ParamsSpec.$,
        mojo.test.TestWTF_EchoStringMap_ResponseParamsSpec.$,
        this.echoStringMap.createReceiverHandler(true /* expectsResponse */));
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
mojo.test.TestWTFCodeGenerationSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTFStructSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTFStructWrapperSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTF_EchoString_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTF_EchoString_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTF_EchoStringArray_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTF_EchoStringArray_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTF_EchoStringMap_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.TestWTF_EchoStringMap_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };


/**
 * @const { {$:!mojo.internal.MojomType} }
 * @export
 */
mojo.test.TestWTFCodeGeneration2Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.TestWTFCodeGenerationSpec.$,
    'TestWTFCodeGeneration',
    [
      mojo.internal.StructField(
        'str', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'nullableStr', 8,
        0,
        mojo.internal.String,
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'strs', 16,
        0,
        mojo.internal.Array(mojo.internal.String, false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'nullableStrs', 24,
        0,
        mojo.internal.Array(mojo.internal.String, true),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'arrays', 32,
        0,
        mojo.internal.Array(mojo.internal.Array(mojo.internal.Int32, false), false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'bools', 40,
        0,
        mojo.internal.Array(mojo.internal.Bool, false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'handles', 48,
        0,
        mojo.internal.Array(mojo.internal.Handle, false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'strMap', 56,
        0,
        mojo.internal.Map(mojo.internal.String, mojo.internal.String, true),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'arrayMap', 64,
        0,
        mojo.internal.Map(mojo.internal.Int32, mojo.internal.Array(mojo.internal.Int32, false), false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'handleMap', 72,
        0,
        mojo.internal.Map(mojo.internal.Int32, mojo.internal.Handle, false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'strMaps', 80,
        0,
        mojo.internal.Array(mojo.internal.Map(mojo.internal.String, mojo.internal.String, true), false),
        null,
        false /* nullable */),
    ],
    [[0, 96],]);





/** @record */
mojo.test.TestWTFCodeGeneration = class {
  constructor() {
    /** @export { !string } */
    this.str;
    /** @export { (string|undefined) } */
    this.nullableStr;
    /** @export { !Array<!string> } */
    this.strs;
    /** @export { !Array<?string> } */
    this.nullableStrs;
    /** @export { !Array<!Array<!number>> } */
    this.arrays;
    /** @export { !Array<!boolean> } */
    this.bools;
    /** @export { !Array<!MojoHandle> } */
    this.handles;
    /** @export { !Object<!string, ?string> } */
    this.strMap;
    /** @export { !Object<!number, !Array<!number>> } */
    this.arrayMap;
    /** @export { !Object<!number, !MojoHandle> } */
    this.handleMap;
    /** @export { !Array<!Object<!string, ?string>> } */
    this.strMaps;
  }
};




/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
mojo.test.TestWTFStructSpec.NestedEnumSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
mojo.test.TestWTFStruct_NestedEnum = {
  
  E0: 0,
  E1: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};


mojo.internal.Struct(
    mojo.test.TestWTFStructSpec.$,
    'TestWTFStruct',
    [
      mojo.internal.StructField(
        'str', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'integer', 8,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
    ],
    [[0, 24],]);





/** @record */
mojo.test.TestWTFStruct = class {
  constructor() {
    /** @export { !string } */
    this.str;
    /** @export { !number } */
    this.integer;
  }
};




mojo.internal.Struct(
    mojo.test.TestWTFStructWrapperSpec.$,
    'TestWTFStructWrapper',
    [
      mojo.internal.StructField(
        'nestedStruct', 0,
        0,
        mojo.test.TestWTFStructSpec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'arrayStruct', 8,
        0,
        mojo.internal.Array(mojo.test.TestWTFStructSpec.$, false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'mapStruct', 16,
        0,
        mojo.internal.Map(mojo.test.TestWTFStructSpec.$, mojo.test.TestWTFStructSpec.$, false),
        null,
        false /* nullable */),
    ],
    [[0, 32],]);





/** @record */
mojo.test.TestWTFStructWrapper = class {
  constructor() {
    /** @export { !mojo.test.TestWTFStruct } */
    this.nestedStruct;
    /** @export { !Array<!mojo.test.TestWTFStruct> } */
    this.arrayStruct;
    /** @export { !Map<!mojo.test.TestWTFStruct, !mojo.test.TestWTFStruct> } */
    this.mapStruct;
  }
};




mojo.internal.Struct(
    mojo.test.TestWTF_EchoString_ParamsSpec.$,
    'TestWTF_EchoString_Params',
    [
      mojo.internal.StructField(
        'str', 0,
        0,
        mojo.internal.String,
        null,
        true /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.TestWTF_EchoString_Params = class {
  constructor() {
    /** @export { (string|undefined) } */
    this.str;
  }
};




mojo.internal.Struct(
    mojo.test.TestWTF_EchoString_ResponseParamsSpec.$,
    'TestWTF_EchoString_ResponseParams',
    [
      mojo.internal.StructField(
        'str', 0,
        0,
        mojo.internal.String,
        null,
        true /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.TestWTF_EchoString_ResponseParams = class {
  constructor() {
    /** @export { (string|undefined) } */
    this.str;
  }
};




mojo.internal.Struct(
    mojo.test.TestWTF_EchoStringArray_ParamsSpec.$,
    'TestWTF_EchoStringArray_Params',
    [
      mojo.internal.StructField(
        'arr', 0,
        0,
        mojo.internal.Array(mojo.internal.String, true),
        null,
        true /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.TestWTF_EchoStringArray_Params = class {
  constructor() {
    /** @export { (Array<?string>|undefined) } */
    this.arr;
  }
};




mojo.internal.Struct(
    mojo.test.TestWTF_EchoStringArray_ResponseParamsSpec.$,
    'TestWTF_EchoStringArray_ResponseParams',
    [
      mojo.internal.StructField(
        'arr', 0,
        0,
        mojo.internal.Array(mojo.internal.String, true),
        null,
        true /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.TestWTF_EchoStringArray_ResponseParams = class {
  constructor() {
    /** @export { (Array<?string>|undefined) } */
    this.arr;
  }
};




mojo.internal.Struct(
    mojo.test.TestWTF_EchoStringMap_ParamsSpec.$,
    'TestWTF_EchoStringMap_Params',
    [
      mojo.internal.StructField(
        'strMap', 0,
        0,
        mojo.internal.Map(mojo.internal.String, mojo.internal.String, true),
        null,
        true /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.TestWTF_EchoStringMap_Params = class {
  constructor() {
    /** @export { (Object<!string, ?string>|undefined) } */
    this.strMap;
  }
};




mojo.internal.Struct(
    mojo.test.TestWTF_EchoStringMap_ResponseParamsSpec.$,
    'TestWTF_EchoStringMap_ResponseParams',
    [
      mojo.internal.StructField(
        'strMap', 0,
        0,
        mojo.internal.Map(mojo.internal.String, mojo.internal.String, true),
        null,
        true /* nullable */),
    ],
    [[0, 16],]);





/** @record */
mojo.test.TestWTF_EchoStringMap_ResponseParams = class {
  constructor() {
    /** @export { (Object<!string, ?string>|undefined) } */
    this.strMap;
  }
};




mojo.internal.Union(
    mojo.test.TestWTFCodeGeneration2Spec.$, 'TestWTFCodeGeneration2',
    {
      'str': {
        'ordinal': 0,
        'type': mojo.internal.String,
      },
      'strs': {
        'ordinal': 1,
        'type': mojo.internal.Array(mojo.internal.String, false),
      },
      'strMap': {
        'ordinal': 2,
        'type': mojo.internal.Map(mojo.internal.String, mojo.internal.String, true),
      },
    });

/**
 * @typedef { {
 *   str: (!string|undefined),
 *   strs: (!Array<!string>|undefined),
 *   strMap: (!Object<!string, ?string>|undefined),
 * } }
 */
mojo.test.TestWTFCodeGeneration2;
