// mojo/public/cpp/bindings/tests/enum_default_unittest.test-mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');





goog.provide('mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault');
goog.provide('mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefaultSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefaultSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault = {
  
  kZeroth: 0,
  kFirst: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault');
goog.provide('mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefaultSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefaultSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault = {
  
  kZeroth: 0,
  kFirst: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue');
goog.provide('mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValueSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValueSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue = {
  
  kFirst: 1,
  kSecond: 2,
  MIN_VALUE: 1,
  MAX_VALUE: 2,
};



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface');
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterfaceReceiver');
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterfaceCallbackRouter');
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterfaceInterface');
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote');
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterfacePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterfacePendingReceiver = class {
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
        mojo.test.enumDefaultUnittest.mojom.TestInterface.$interfaceName,
        scope);
  }
};

/** @interface */
mojo.test.enumDefaultUnittest.mojom.TestInterfaceInterface = class {
  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault,
   *  }>}
   */

  echoWithDefault(in_) {}
  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault,
   *  }>}
   */

  echoWithoutDefault(in_) {}
  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault,
   *  }>}
   */

  echoStructWithDefault(in_) {}
  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault,
   *  }>}
   */

  echoStructWithoutDefault(in_) {}
  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault,
   *  }>}
   */

  echoUnionWithDefault(in_) {}
  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault,
   *  }>}
   */

  echoUnionWithoutDefault(in_) {}
};

/**
 * @export
 * @implements { mojo.test.enumDefaultUnittest.mojom.TestInterfaceInterface }
 */
mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!mojo.test.enumDefaultUnittest.mojom.TestInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          mojo.test.enumDefaultUnittest.mojom.TestInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!mojo.test.enumDefaultUnittest.mojom.TestInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault,
   *  }>}
   */

  echoWithDefault(
      in) {
    return this.proxy.sendMessage(
        490516208,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParamsSpec.$,
        [
          in
        ]);
  }

  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault,
   *  }>}
   */

  echoWithoutDefault(
      in) {
    return this.proxy.sendMessage(
        2037498148,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParamsSpec.$,
        [
          in
        ]);
  }

  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault,
   *  }>}
   */

  echoStructWithDefault(
      in) {
    return this.proxy.sendMessage(
        212424705,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParamsSpec.$,
        [
          in
        ]);
  }

  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault,
   *  }>}
   */

  echoStructWithoutDefault(
      in) {
    return this.proxy.sendMessage(
        1474641530,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParamsSpec.$,
        [
          in
        ]);
  }

  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault,
   *  }>}
   */

  echoUnionWithDefault(
      in) {
    return this.proxy.sendMessage(
        559057625,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParamsSpec.$,
        [
          in
        ]);
  }

  
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault } in_
   * @return {!Promise<{
        out: !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault,
   *  }>}
   */

  echoUnionWithoutDefault(
      in) {
    return this.proxy.sendMessage(
        1582513947,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParamsSpec.$,
        [
          in
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
mojo.test.enumDefaultUnittest.mojom.TestInterfaceReceiver = class {
  /**
   * @param {!mojo.test.enumDefaultUnittest.mojom.TestInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        490516208,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParamsSpec.$,
        impl.echoWithDefault.bind(impl));
    this.helper_internal_.registerHandler(
        2037498148,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParamsSpec.$,
        impl.echoWithoutDefault.bind(impl));
    this.helper_internal_.registerHandler(
        212424705,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParamsSpec.$,
        impl.echoStructWithDefault.bind(impl));
    this.helper_internal_.registerHandler(
        1474641530,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParamsSpec.$,
        impl.echoStructWithoutDefault.bind(impl));
    this.helper_internal_.registerHandler(
        559057625,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParamsSpec.$,
        impl.echoUnionWithDefault.bind(impl));
    this.helper_internal_.registerHandler(
        1582513947,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParamsSpec.$,
        impl.echoUnionWithoutDefault.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "mojo.test.enum_default_unittest.mojom.TestInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote}
   * @export
   */
  static getRemote() {
    let remote = new mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote;
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
mojo.test.enumDefaultUnittest.mojom.TestInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!mojo.test.enumDefaultUnittest.mojom.TestInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoWithDefault =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        490516208,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParamsSpec.$,
        this.echoWithDefault.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoWithoutDefault =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        2037498148,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParamsSpec.$,
        this.echoWithoutDefault.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoStructWithDefault =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        212424705,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParamsSpec.$,
        this.echoStructWithDefault.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoStructWithoutDefault =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1474641530,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParamsSpec.$,
        this.echoStructWithoutDefault.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoUnionWithDefault =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        559057625,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParamsSpec.$,
        this.echoUnionWithDefault.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.echoUnionWithoutDefault =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1582513947,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ParamsSpec.$,
        mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParamsSpec.$,
        this.echoUnionWithoutDefault.createReceiverHandler(true /* expectsResponse */));
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


goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefaultSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefaultSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefaultSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefaultSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithoutInitializerSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.StructWithoutInitializerSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithInitializerSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.StructWithInitializerSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefaultSpec');
/**
 * @const { {$:!mojo.internal.MojomType} }
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefaultSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefaultSpec');
/**
 * @const { {$:!mojo.internal.MojomType} }
 * @export
 */
mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefaultSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefaultSpec.$,
    'StructWithExtensibleEnumWithDefault',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefaultSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault');

/** @record */
mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } */
    this.value;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefaultSpec.$,
    'StructWithExtensibleEnumWithoutDefault',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefaultSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault');

/** @record */
mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } */
    this.value;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.StructWithoutInitializerSpec.$,
    'StructWithoutInitializer',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValueSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithoutInitializer');

/** @record */
mojo.test.enumDefaultUnittest.mojom.StructWithoutInitializer = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue } */
    this.value;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.StructWithInitializerSpec.$,
    'StructWithInitializer',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValueSpec.$,
        mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue.kSecond,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithInitializer');

/** @record */
mojo.test.enumDefaultUnittest.mojom.StructWithInitializer = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue } */
    this.value;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ParamsSpec.$,
    'TestInterface_EchoWithDefault_Params',
    [
      mojo.internal.StructField(
        'in', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefaultSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_Params');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_Params = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } */
    this.in;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParamsSpec.$,
    'TestInterface_EchoWithDefault_ResponseParams',
    [
      mojo.internal.StructField(
        'out', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefaultSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParams');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParams = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } */
    this.out;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ParamsSpec.$,
    'TestInterface_EchoWithoutDefault_Params',
    [
      mojo.internal.StructField(
        'in', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefaultSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_Params');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_Params = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } */
    this.in;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParamsSpec.$,
    'TestInterface_EchoWithoutDefault_ResponseParams',
    [
      mojo.internal.StructField(
        'out', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefaultSpec.$,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParams');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParams = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } */
    this.out;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ParamsSpec.$,
    'TestInterface_EchoStructWithDefault_Params',
    [
      mojo.internal.StructField(
        'in', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_Params');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_Params = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } */
    this.in;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParamsSpec.$,
    'TestInterface_EchoStructWithDefault_ResponseParams',
    [
      mojo.internal.StructField(
        'out', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParams');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParams = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } */
    this.out;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ParamsSpec.$,
    'TestInterface_EchoStructWithoutDefault_Params',
    [
      mojo.internal.StructField(
        'in', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_Params');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_Params = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } */
    this.in;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParamsSpec.$,
    'TestInterface_EchoStructWithoutDefault_ResponseParams',
    [
      mojo.internal.StructField(
        'out', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParams');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParams = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } */
    this.out;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ParamsSpec.$,
    'TestInterface_EchoUnionWithDefault_Params',
    [
      mojo.internal.StructField(
        'in', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_Params');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_Params = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault } */
    this.in;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParamsSpec.$,
    'TestInterface_EchoUnionWithDefault_ResponseParams',
    [
      mojo.internal.StructField(
        'out', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParams');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParams = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault } */
    this.out;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ParamsSpec.$,
    'TestInterface_EchoUnionWithoutDefault_Params',
    [
      mojo.internal.StructField(
        'in', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_Params');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_Params = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault } */
    this.in;
  }
};




mojo.internal.Struct(
    mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParamsSpec.$,
    'TestInterface_EchoUnionWithoutDefault_ResponseParams',
    [
      mojo.internal.StructField(
        'out', 0,
        0,
        mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefaultSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParams');

/** @record */
mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParams = class {
  constructor() {
    /** @export { !mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault } */
    this.out;
  }
};


goog.provide('mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault');


mojo.internal.Union(
    mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefaultSpec.$, 'UnionWithExtensibleEnumWithDefault',
    {
      'value': {
        'ordinal': 0,
        'type': mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefaultSpec.$,
      },
    });

/**
 * @typedef { {
 *   value: (!mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault|undefined),
 * } }
 */
mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithDefault;
goog.provide('mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault');


mojo.internal.Union(
    mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefaultSpec.$, 'UnionWithExtensibleEnumWithoutDefault',
    {
      'value': {
        'ordinal': 0,
        'type': mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefaultSpec.$,
      },
    });

/**
 * @typedef { {
 *   value: (!mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault|undefined),
 * } }
 */
mojo.test.enumDefaultUnittest.mojom.UnionWithExtensibleEnumWithoutDefault;
