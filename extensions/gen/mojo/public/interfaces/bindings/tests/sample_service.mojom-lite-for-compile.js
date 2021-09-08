// mojo/public/interfaces/bindings/tests/sample_service.mojom-lite-for-compile.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
'use strict';

goog.require('mojo.internal');
goog.require('mojo.internal.interfaceSupport');

goog.require('imported.Thing');
goog.require('imported.Point');



goog.provide('sample.TWELVE');
/**
 * @const { !number }
 * @export
 */
sample.TWELVE = 12;



goog.provide('sample.DefaultsSender');
goog.provide('sample.DefaultsSenderReceiver');
goog.provide('sample.DefaultsSenderCallbackRouter');
goog.provide('sample.DefaultsSenderInterface');
goog.provide('sample.DefaultsSenderRemote');
goog.provide('sample.DefaultsSenderPendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
sample.DefaultsSenderPendingReceiver = class {
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
        sample.DefaultsSender.$interfaceName,
        scope);
  }
};

/** @interface */
sample.DefaultsSenderInterface = class {
  
  /**
   * @param { !sample.Bar } bar
   */

  sendBar(bar) {}
  
  /**
   * @param { !sample.Foo } foo
   */

  sendFoo(foo) {}
  
  /**
   * @param { !sample.DefaultsTest } defaults
   */

  sendDefaultsTest(defaults) {}
};

/**
 * @export
 * @implements { sample.DefaultsSenderInterface }
 */
sample.DefaultsSenderRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!sample.DefaultsSenderPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          sample.DefaultsSenderPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!sample.DefaultsSenderPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !sample.Bar } bar
   */

  sendBar(
      bar) {
    this.proxy.sendMessage(
        0,
        sample.DefaultsSender_SendBar_ParamsSpec.$,
        null,
        [
          bar
        ]);
  }

  
  /**
   * @param { !sample.Foo } foo
   */

  sendFoo(
      foo) {
    this.proxy.sendMessage(
        1,
        sample.DefaultsSender_SendFoo_ParamsSpec.$,
        null,
        [
          foo
        ]);
  }

  
  /**
   * @param { !sample.DefaultsTest } defaults
   */

  sendDefaultsTest(
      defaults) {
    this.proxy.sendMessage(
        2,
        sample.DefaultsSender_SendDefaultsTest_ParamsSpec.$,
        null,
        [
          defaults
        ]);
  }
};

/**
 * An object which receives request messages for the DefaultsSender
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
sample.DefaultsSenderReceiver = class {
  /**
   * @param {!sample.DefaultsSenderInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!sample.DefaultsSenderRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        sample.DefaultsSenderRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!sample.DefaultsSenderRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        sample.DefaultsSender_SendBar_ParamsSpec.$,
        null,
        impl.sendBar.bind(impl));
    this.helper_internal_.registerHandler(
        1,
        sample.DefaultsSender_SendFoo_ParamsSpec.$,
        null,
        impl.sendFoo.bind(impl));
    this.helper_internal_.registerHandler(
        2,
        sample.DefaultsSender_SendDefaultsTest_ParamsSpec.$,
        null,
        impl.sendDefaultsTest.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
sample.DefaultsSender = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "sample.DefaultsSender";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!sample.DefaultsSenderRemote}
   * @export
   */
  static getRemote() {
    let remote = new sample.DefaultsSenderRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the DefaultsSender
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
sample.DefaultsSenderCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      sample.DefaultsSenderRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!sample.DefaultsSenderRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.sendBar =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        0,
        sample.DefaultsSender_SendBar_ParamsSpec.$,
        null,
        this.sendBar.createReceiverHandler(false /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.sendFoo =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1,
        sample.DefaultsSender_SendFoo_ParamsSpec.$,
        null,
        this.sendFoo.createReceiverHandler(false /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.sendDefaultsTest =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        2,
        sample.DefaultsSender_SendDefaultsTest_ParamsSpec.$,
        null,
        this.sendDefaultsTest.createReceiverHandler(false /* expectsResponse */));
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


goog.provide('sample.Service');
goog.provide('sample.ServiceReceiver');
goog.provide('sample.ServiceCallbackRouter');
goog.provide('sample.ServiceInterface');
goog.provide('sample.ServiceRemote');
goog.provide('sample.ServicePendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
sample.ServicePendingReceiver = class {
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
        sample.Service.$interfaceName,
        scope);
  }
};

/** @interface */
sample.ServiceInterface = class {
  
  /**
   * @param { ?sample.Foo } foo
   * @param { !sample.Service_BazOptions } baz
   * @param { ?sample.PortRemote } port
   * @return {!Promise<{
        result: !number,
   *  }>}
   */

  frobinate(foo, baz, port) {}
  
  /**
   * @param { !sample.PortPendingReceiver } receiver
   */

  getPort(receiver) {}
};

/**
 * @export
 * @implements { sample.ServiceInterface }
 */
sample.ServiceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!sample.ServicePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          sample.ServicePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!sample.ServicePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { ?sample.Foo } foo
   * @param { !sample.Service_BazOptions } baz
   * @param { ?sample.PortRemote } port
   * @return {!Promise<{
        result: !number,
   *  }>}
   */

  frobinate(
      foo,
      baz,
      port) {
    return this.proxy.sendMessage(
        0,
        sample.Service_Frobinate_ParamsSpec.$,
        sample.Service_Frobinate_ResponseParamsSpec.$,
        [
          foo,
          baz,
          port
        ]);
  }

  
  /**
   * @param { !sample.PortPendingReceiver } receiver
   */

  getPort(
      receiver) {
    this.proxy.sendMessage(
        1,
        sample.Service_GetPort_ParamsSpec.$,
        null,
        [
          receiver
        ]);
  }
};

/**
 * An object which receives request messages for the Service
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
sample.ServiceReceiver = class {
  /**
   * @param {!sample.ServiceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!sample.ServiceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        sample.ServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!sample.ServiceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        sample.Service_Frobinate_ParamsSpec.$,
        sample.Service_Frobinate_ResponseParamsSpec.$,
        impl.frobinate.bind(impl));
    this.helper_internal_.registerHandler(
        1,
        sample.Service_GetPort_ParamsSpec.$,
        null,
        impl.getPort.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
sample.Service = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "sample.Service";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!sample.ServiceRemote}
   * @export
   */
  static getRemote() {
    let remote = new sample.ServiceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};

goog.provide('sample.Service_BazOptions');
goog.provide('sample.Service.BazOptionsSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
sample.Service.BazOptionsSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
sample.Service_BazOptions = {
  
  REGULAR: 0,
  EXTRA: 1,
  MIN_VALUE: 0,
  MAX_VALUE: 1,
};

/**
 * An object which receives request messages for the Service
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
sample.ServiceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      sample.ServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!sample.ServiceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.frobinate =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        0,
        sample.Service_Frobinate_ParamsSpec.$,
        sample.Service_Frobinate_ResponseParamsSpec.$,
        this.frobinate.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.getPort =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1,
        sample.Service_GetPort_ParamsSpec.$,
        null,
        this.getPort.createReceiverHandler(false /* expectsResponse */));
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


goog.provide('sample.Port');
goog.provide('sample.PortReceiver');
goog.provide('sample.PortCallbackRouter');
goog.provide('sample.PortInterface');
goog.provide('sample.PortRemote');
goog.provide('sample.PortPendingReceiver');


/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 * @export
 */
sample.PortPendingReceiver = class {
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
        sample.Port.$interfaceName,
        scope);
  }
};

/** @interface */
sample.PortInterface = class {
  
  /**
   * @param { !string } messageText
   * @param { !sample.PortRemote } port
   */

  postMessageToPort(messageText, port) {}
};

/**
 * @export
 * @implements { sample.PortInterface }
 */
sample.PortRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!sample.PortPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          sample.PortPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!sample.PortPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !string } messageText
   * @param { !sample.PortRemote } port
   */

  postMessageToPort(
      messageText,
      port) {
    this.proxy.sendMessage(
        0,
        sample.Port_PostMessageToPort_ParamsSpec.$,
        null,
        [
          messageText,
          port
        ]);
  }
};

/**
 * An object which receives request messages for the Port
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 *
 * @export
 */
sample.PortReceiver = class {
  /**
   * @param {!sample.PortInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!sample.PortRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        sample.PortRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!sample.PortRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        sample.Port_PostMessageToPort_ParamsSpec.$,
        null,
        impl.postMessageToPort.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

/**
 *  @export
 */
sample.Port = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "sample.Port";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!sample.PortRemote}
   * @export
   */
  static getRemote() {
    let remote = new sample.PortRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the Port
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 *
 * @export
 */
sample.PortCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      sample.PortRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!sample.PortRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.postMessageToPort =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        0,
        sample.Port_PostMessageToPort_ParamsSpec.$,
        null,
        this.postMessageToPort.createReceiverHandler(false /* expectsResponse */));
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


goog.provide('sample.BarSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.BarSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.FooSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.FooSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.DefaultsTestSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.DefaultsTestSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.StructWithHoleV1Spec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.StructWithHoleV1Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.StructWithHoleV2Spec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.StructWithHoleV2Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.DefaultsSender_SendBar_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.DefaultsSender_SendBar_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.DefaultsSender_SendFoo_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.DefaultsSender_SendFoo_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.DefaultsSender_SendDefaultsTest_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.DefaultsSender_SendDefaultsTest_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.Service_Frobinate_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.Service_Frobinate_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.Service_Frobinate_ResponseParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.Service_Frobinate_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.Service_GetPort_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.Service_GetPort_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

goog.provide('sample.Port_PostMessageToPort_ParamsSpec');
/**
 * @const { {$:!mojo.internal.MojomType}}
 * @export
 */
sample.Port_PostMessageToPort_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };



goog.provide('sample.Bar_Type');
goog.provide('sample.BarSpec.TypeSpec');
/**
 * @const { {$: !mojo.internal.MojomType} }
 * @export
 */
sample.BarSpec.TypeSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 * @export
 */
sample.Bar_Type = {
  
  VERTICAL: 1,
  HORIZONTAL: 2,
  BOTH: 3,
  INVALID: 4,
  MIN_VALUE: 1,
  MAX_VALUE: 4,
};


mojo.internal.Struct(
    sample.BarSpec.$,
    'Bar',
    [
      mojo.internal.StructField(
        'alpha', 0,
        0,
        mojo.internal.Uint8,
        0xff,
        false /* nullable */),
      mojo.internal.StructField(
        'beta', 1,
        0,
        mojo.internal.Uint8,
        0,
        false /* nullable */),
      mojo.internal.StructField(
        'gamma', 2,
        0,
        mojo.internal.Uint8,
        0,
        false /* nullable */),
      mojo.internal.StructField(
        'type', 4,
        0,
        sample.BarSpec.TypeSpec.$,
        sample.Bar_Type.VERTICAL,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('sample.Bar');

/** @record */
sample.Bar = class {
  constructor() {
    /** @export { !number } */
    this.alpha;
    /** @export { !number } */
    this.beta;
    /** @export { !number } */
    this.gamma;
    /** @export { !sample.Bar_Type } */
    this.type;
  }
};


/**
 * @const { !string }
 * @export
 */
sample.Foo_FOOBY =
    "Fooby";



mojo.internal.Struct(
    sample.FooSpec.$,
    'Foo',
    [
      mojo.internal.StructField(
        'x', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
      mojo.internal.StructField(
        'y', 4,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
      mojo.internal.StructField(
        'a', 8,
        0,
        mojo.internal.Bool,
        true,
        false /* nullable */),
      mojo.internal.StructField(
        'b', 8,
        1,
        mojo.internal.Bool,
        false,
        false /* nullable */),
      mojo.internal.StructField(
        'c', 8,
        2,
        mojo.internal.Bool,
        false,
        false /* nullable */),
      mojo.internal.StructField(
        'bar', 16,
        0,
        sample.BarSpec.$,
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'data', 24,
        0,
        mojo.internal.Array(mojo.internal.Uint8, false),
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'extraBars', 32,
        0,
        mojo.internal.Array(sample.BarSpec.$, false),
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'name', 40,
        0,
        mojo.internal.String,
        sample.Foo_FOOBY,
        false /* nullable */),
      mojo.internal.StructField(
        'source', 12,
        0,
        mojo.internal.Handle,
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'inputStreams', 48,
        0,
        mojo.internal.Array(mojo.internal.Handle, false),
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'outputStreams', 56,
        0,
        mojo.internal.Array(mojo.internal.Handle, false),
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'arrayOfArrayOfBools', 64,
        0,
        mojo.internal.Array(mojo.internal.Array(mojo.internal.Bool, false), false),
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'multiArrayOfStrings', 72,
        0,
        mojo.internal.Array(mojo.internal.Array(mojo.internal.Array(mojo.internal.String, false), false), false),
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'arrayOfBools', 80,
        0,
        mojo.internal.Array(mojo.internal.Bool, false),
        null,
        true /* nullable */),
    ],
    [[0, 96],]);



goog.provide('sample.Foo');

/** @record */
sample.Foo = class {
  constructor() {
    /** @export { !number } */
    this.x;
    /** @export { !number } */
    this.y;
    /** @export { !boolean } */
    this.a;
    /** @export { !boolean } */
    this.b;
    /** @export { !boolean } */
    this.c;
    /** @export { (MojoHandle|undefined) } */
    this.source;
    /** @export { (sample.Bar|undefined) } */
    this.bar;
    /** @export { (Array<!number>|undefined) } */
    this.data;
    /** @export { (Array<!sample.Bar>|undefined) } */
    this.extraBars;
    /** @export { !string } */
    this.name;
    /** @export { (Array<!MojoHandle>|undefined) } */
    this.inputStreams;
    /** @export { (Array<!MojoHandle>|undefined) } */
    this.outputStreams;
    /** @export { (Array<!Array<!boolean>>|undefined) } */
    this.arrayOfArrayOfBools;
    /** @export { (Array<!Array<!Array<!string>>>|undefined) } */
    this.multiArrayOfStrings;
    /** @export { (Array<!boolean>|undefined) } */
    this.arrayOfBools;
  }
};




mojo.internal.Struct(
    sample.DefaultsTestSpec.$,
    'DefaultsTest',
    [
      mojo.internal.StructField(
        'a0', 0,
        0,
        mojo.internal.Int8,
        -12,
        false /* nullable */),
      mojo.internal.StructField(
        'a1', 1,
        0,
        mojo.internal.Uint8,
        sample.TWELVE,
        false /* nullable */),
      mojo.internal.StructField(
        'a2', 2,
        0,
        mojo.internal.Int16,
        1234,
        false /* nullable */),
      mojo.internal.StructField(
        'a3', 4,
        0,
        mojo.internal.Uint16,
        34567,
        false /* nullable */),
      mojo.internal.StructField(
        'a4', 8,
        0,
        mojo.internal.Int32,
        123456,
        false /* nullable */),
      mojo.internal.StructField(
        'a5', 12,
        0,
        mojo.internal.Uint32,
        3456789012,
        false /* nullable */),
      mojo.internal.StructField(
        'a6', 16,
        0,
        mojo.internal.Int64,
        BigInt('-111111111111'),
        false /* nullable */),
      mojo.internal.StructField(
        'a7', 24,
        0,
        mojo.internal.Uint64,
        BigInt('9999999999999999999'),
        false /* nullable */),
      mojo.internal.StructField(
        'a8', 32,
        0,
        mojo.internal.Int32,
        0x12345,
        false /* nullable */),
      mojo.internal.StructField(
        'a9', 36,
        0,
        mojo.internal.Int32,
        -0x12345,
        false /* nullable */),
      mojo.internal.StructField(
        'a10', 40,
        0,
        mojo.internal.Int32,
        +1234,
        false /* nullable */),
      mojo.internal.StructField(
        'a11', 6,
        0,
        mojo.internal.Bool,
        true,
        false /* nullable */),
      mojo.internal.StructField(
        'a12', 6,
        1,
        mojo.internal.Bool,
        false,
        false /* nullable */),
      mojo.internal.StructField(
        'a13', 44,
        0,
        mojo.internal.Float,
        123.25,
        false /* nullable */),
      mojo.internal.StructField(
        'a14', 48,
        0,
        mojo.internal.Double,
        1234567890.123,
        false /* nullable */),
      mojo.internal.StructField(
        'a15', 56,
        0,
        mojo.internal.Double,
        1E10,
        false /* nullable */),
      mojo.internal.StructField(
        'a16', 64,
        0,
        mojo.internal.Double,
        -1.2E+20,
        false /* nullable */),
      mojo.internal.StructField(
        'a17', 72,
        0,
        mojo.internal.Double,
        +1.23E-20,
        false /* nullable */),
      mojo.internal.StructField(
        'a18', 80,
        0,
        mojo.internal.Array(mojo.internal.Uint8, false),
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'a19', 88,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'a20', 96,
        0,
        sample.BarSpec.TypeSpec.$,
        sample.Bar_Type.BOTH,
        false /* nullable */),
      mojo.internal.StructField(
        'a21', 104,
        0,
        imported.PointSpec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'a22', 112,
        0,
        imported.ThingSpec.$,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'a23', 120,
        0,
        mojo.internal.Uint64,
        BigInt('18446744073709551615'),
        false /* nullable */),
      mojo.internal.StructField(
        'a24', 128,
        0,
        mojo.internal.Int64,
        BigInt('4886718345'),
        false /* nullable */),
      mojo.internal.StructField(
        'a25', 136,
        0,
        mojo.internal.Int64,
        BigInt('-4886718345'),
        false /* nullable */),
      mojo.internal.StructField(
        'a26', 144,
        0,
        mojo.internal.Double,
        Infinity,
        false /* nullable */),
      mojo.internal.StructField(
        'a27', 152,
        0,
        mojo.internal.Double,
        -Infinity,
        false /* nullable */),
      mojo.internal.StructField(
        'a28', 160,
        0,
        mojo.internal.Double,
        NaN,
        false /* nullable */),
      mojo.internal.StructField(
        'a29', 100,
        0,
        mojo.internal.Float,
        Infinity,
        false /* nullable */),
      mojo.internal.StructField(
        'a30', 168,
        0,
        mojo.internal.Float,
        -Infinity,
        false /* nullable */),
      mojo.internal.StructField(
        'a31', 172,
        0,
        mojo.internal.Float,
        NaN,
        false /* nullable */),
    ],
    [[0, 184],]);



goog.provide('sample.DefaultsTest');

/** @record */
sample.DefaultsTest = class {
  constructor() {
    /** @export { !number } */
    this.a0;
    /** @export { !number } */
    this.a1;
    /** @export { !number } */
    this.a2;
    /** @export { !number } */
    this.a3;
    /** @export { !boolean } */
    this.a11;
    /** @export { !boolean } */
    this.a12;
    /** @export { !number } */
    this.a4;
    /** @export { !number } */
    this.a5;
    /** @export { !bigint } */
    this.a6;
    /** @export { !bigint } */
    this.a7;
    /** @export { !number } */
    this.a8;
    /** @export { !number } */
    this.a9;
    /** @export { !number } */
    this.a10;
    /** @export { !number } */
    this.a13;
    /** @export { !number } */
    this.a14;
    /** @export { !number } */
    this.a15;
    /** @export { !number } */
    this.a16;
    /** @export { !number } */
    this.a17;
    /** @export { !Array<!number> } */
    this.a18;
    /** @export { !string } */
    this.a19;
    /** @export { !sample.Bar_Type } */
    this.a20;
    /** @export { !number } */
    this.a29;
    /** @export { !imported.Point } */
    this.a21;
    /** @export { !imported.Thing } */
    this.a22;
    /** @export { !bigint } */
    this.a23;
    /** @export { !bigint } */
    this.a24;
    /** @export { !bigint } */
    this.a25;
    /** @export { !number } */
    this.a26;
    /** @export { !number } */
    this.a27;
    /** @export { !number } */
    this.a28;
    /** @export { !number } */
    this.a30;
    /** @export { !number } */
    this.a31;
  }
};




mojo.internal.Struct(
    sample.StructWithHoleV1Spec.$,
    'StructWithHoleV1',
    [
      mojo.internal.StructField(
        'v1', 0,
        0,
        mojo.internal.Int32,
        1,
        false /* nullable */),
      mojo.internal.StructField(
        'v2', 8,
        0,
        mojo.internal.Int64,
        BigInt('2'),
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('sample.StructWithHoleV1');

/** @record */
sample.StructWithHoleV1 = class {
  constructor() {
    /** @export { !number } */
    this.v1;
    /** @export { !bigint } */
    this.v2;
  }
};




mojo.internal.Struct(
    sample.StructWithHoleV2Spec.$,
    'StructWithHoleV2',
    [
      mojo.internal.StructField(
        'v1', 0,
        0,
        mojo.internal.Int32,
        1,
        false /* nullable */),
      mojo.internal.StructField(
        'v2', 8,
        0,
        mojo.internal.Int64,
        BigInt('2'),
        false /* nullable */),
      mojo.internal.StructField(
        'v3', 4,
        0,
        mojo.internal.Int32,
        3,
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('sample.StructWithHoleV2');

/** @record */
sample.StructWithHoleV2 = class {
  constructor() {
    /** @export { !number } */
    this.v1;
    /** @export { !number } */
    this.v3;
    /** @export { !bigint } */
    this.v2;
  }
};




mojo.internal.Struct(
    sample.DefaultsSender_SendBar_ParamsSpec.$,
    'DefaultsSender_SendBar_Params',
    [
      mojo.internal.StructField(
        'bar', 0,
        0,
        sample.BarSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('sample.DefaultsSender_SendBar_Params');

/** @record */
sample.DefaultsSender_SendBar_Params = class {
  constructor() {
    /** @export { !sample.Bar } */
    this.bar;
  }
};




mojo.internal.Struct(
    sample.DefaultsSender_SendFoo_ParamsSpec.$,
    'DefaultsSender_SendFoo_Params',
    [
      mojo.internal.StructField(
        'foo', 0,
        0,
        sample.FooSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('sample.DefaultsSender_SendFoo_Params');

/** @record */
sample.DefaultsSender_SendFoo_Params = class {
  constructor() {
    /** @export { !sample.Foo } */
    this.foo;
  }
};




mojo.internal.Struct(
    sample.DefaultsSender_SendDefaultsTest_ParamsSpec.$,
    'DefaultsSender_SendDefaultsTest_Params',
    [
      mojo.internal.StructField(
        'defaults', 0,
        0,
        sample.DefaultsTestSpec.$,
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('sample.DefaultsSender_SendDefaultsTest_Params');

/** @record */
sample.DefaultsSender_SendDefaultsTest_Params = class {
  constructor() {
    /** @export { !sample.DefaultsTest } */
    this.defaults;
  }
};




mojo.internal.Struct(
    sample.Service_Frobinate_ParamsSpec.$,
    'Service_Frobinate_Params',
    [
      mojo.internal.StructField(
        'foo', 0,
        0,
        sample.FooSpec.$,
        null,
        true /* nullable */),
      mojo.internal.StructField(
        'baz', 8,
        0,
        sample.Service.BazOptionsSpec.$,
        0,
        false /* nullable */),
      mojo.internal.StructField(
        'port', 12,
        0,
        mojo.internal.InterfaceProxy(sample.PortRemote),
        null,
        true /* nullable */),
    ],
    [[0, 32],]);



goog.provide('sample.Service_Frobinate_Params');

/** @record */
sample.Service_Frobinate_Params = class {
  constructor() {
    /** @export { (sample.Foo|undefined) } */
    this.foo;
    /** @export { !sample.Service_BazOptions } */
    this.baz;
    /** @export { (sample.PortRemote|undefined) } */
    this.port;
  }
};




mojo.internal.Struct(
    sample.Service_Frobinate_ResponseParamsSpec.$,
    'Service_Frobinate_ResponseParams',
    [
      mojo.internal.StructField(
        'result', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('sample.Service_Frobinate_ResponseParams');

/** @record */
sample.Service_Frobinate_ResponseParams = class {
  constructor() {
    /** @export { !number } */
    this.result;
  }
};




mojo.internal.Struct(
    sample.Service_GetPort_ParamsSpec.$,
    'Service_GetPort_Params',
    [
      mojo.internal.StructField(
        'receiver', 0,
        0,
        mojo.internal.InterfaceRequest(sample.PortPendingReceiver),
        null,
        false /* nullable */),
    ],
    [[0, 16],]);



goog.provide('sample.Service_GetPort_Params');

/** @record */
sample.Service_GetPort_Params = class {
  constructor() {
    /** @export { !sample.PortPendingReceiver } */
    this.receiver;
  }
};




mojo.internal.Struct(
    sample.Port_PostMessageToPort_ParamsSpec.$,
    'Port_PostMessageToPort_Params',
    [
      mojo.internal.StructField(
        'messageText', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */),
      mojo.internal.StructField(
        'port', 8,
        0,
        mojo.internal.InterfaceProxy(sample.PortRemote),
        null,
        false /* nullable */),
    ],
    [[0, 24],]);



goog.provide('sample.Port_PostMessageToPort_Params');

/** @record */
sample.Port_PostMessageToPort_Params = class {
  constructor() {
    /** @export { !string } */
    this.messageText;
    /** @export { !sample.PortRemote } */
    this.port;
  }
};


