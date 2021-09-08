// mojo/public/interfaces/bindings/tests/sample_service.mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';

import {
  Thing as imported_Thing,
  ThingSpec as imported_ThingSpec
} from './sample_import2.mojom.m.js';

import {
  Point as imported_Point,
  PointSpec as imported_PointSpec
} from './sample_import.mojom.m.js';


/**
 * @const { !number }
 */
export const TWELVE = 12;




/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const DefaultsSenderPendingReceiver = class {
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
        this.handle, 'sample.DefaultsSender', scope);
  }
};

/** @interface */
export const DefaultsSenderInterface = class {
  
  /**
   * @param { !Bar } bar
   */

  sendBar(bar) {}
  
  /**
   * @param { !Foo } foo
   */

  sendFoo(foo) {}
  
  /**
   * @param { !DefaultsTest } defaults
   */

  sendDefaultsTest(defaults) {}
};

/**
 * @implements { DefaultsSenderInterface }
 */
export const DefaultsSenderRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!DefaultsSenderPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          DefaultsSenderPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!DefaultsSenderPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !Bar } bar
   */

  sendBar(
      bar) {
    this.proxy.sendMessage(
        0,
        DefaultsSender_SendBar_ParamsSpec.$,
        null,
        [
          bar
        ]);
  }

  
  /**
   * @param { !Foo } foo
   */

  sendFoo(
      foo) {
    this.proxy.sendMessage(
        1,
        DefaultsSender_SendFoo_ParamsSpec.$,
        null,
        [
          foo
        ]);
  }

  
  /**
   * @param { !DefaultsTest } defaults
   */

  sendDefaultsTest(
      defaults) {
    this.proxy.sendMessage(
        2,
        DefaultsSender_SendDefaultsTest_ParamsSpec.$,
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
 */
export const DefaultsSenderReceiver = class {
  /**
   * @param {!DefaultsSenderInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!DefaultsSenderRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        DefaultsSenderRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!DefaultsSenderRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        DefaultsSender_SendBar_ParamsSpec.$,
        null,
        impl.sendBar.bind(impl));
    this.helper_internal_.registerHandler(
        1,
        DefaultsSender_SendFoo_ParamsSpec.$,
        null,
        impl.sendFoo.bind(impl));
    this.helper_internal_.registerHandler(
        2,
        DefaultsSender_SendDefaultsTest_ParamsSpec.$,
        null,
        impl.sendDefaultsTest.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const DefaultsSender = class {
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
   * @return {!DefaultsSenderRemote}
   */
  static getRemote() {
    let remote = new DefaultsSenderRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the DefaultsSender
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const DefaultsSenderCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      DefaultsSenderRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!DefaultsSenderRemote>}
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
        DefaultsSender_SendBar_ParamsSpec.$,
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
        DefaultsSender_SendFoo_ParamsSpec.$,
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
        DefaultsSender_SendDefaultsTest_ParamsSpec.$,
        null,
        this.sendDefaultsTest.createReceiverHandler(false /* expectsResponse */));
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
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const ServicePendingReceiver = class {
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
        this.handle, 'sample.Service', scope);
  }
};

/** @interface */
export const ServiceInterface = class {
  
  /**
   * @param { Foo } foo
   * @param { number } baz
   * @param { PortRemote } port
   * @return {!Promise<{
        result: !number,
   *  }>}
   */

  frobinate(foo, baz, port) {}
  
  /**
   * @param { !PortPendingReceiver } receiver
   */

  getPort(receiver) {}
};

/**
 * @implements { ServiceInterface }
 */
export const ServiceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!ServicePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          ServicePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!ServicePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { Foo } foo
   * @param { number } baz
   * @param { PortRemote } port
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
        Service_Frobinate_ParamsSpec.$,
        Service_Frobinate_ResponseParamsSpec.$,
        [
          foo,
          baz,
          port
        ]);
  }

  
  /**
   * @param { !PortPendingReceiver } receiver
   */

  getPort(
      receiver) {
    this.proxy.sendMessage(
        1,
        Service_GetPort_ParamsSpec.$,
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
 */
export const ServiceReceiver = class {
  /**
   * @param {!ServiceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!ServiceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        ServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!ServiceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        Service_Frobinate_ParamsSpec.$,
        Service_Frobinate_ResponseParamsSpec.$,
        impl.frobinate.bind(impl));
    this.helper_internal_.registerHandler(
        1,
        Service_GetPort_ParamsSpec.$,
        null,
        impl.getPort.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const Service = class {
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
   * @return {!ServiceRemote}
   */
  static getRemote() {
    let remote = new ServiceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};

/**
 * @const { {$: !mojo.internal.MojomType} }
 */
export const Service_BazOptionsSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 */
export const Service_BazOptions = {
  
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
 */
export const ServiceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      ServiceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!ServiceRemote>}
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
        Service_Frobinate_ParamsSpec.$,
        Service_Frobinate_ResponseParamsSpec.$,
        this.frobinate.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.getPort =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1,
        Service_GetPort_ParamsSpec.$,
        null,
        this.getPort.createReceiverHandler(false /* expectsResponse */));
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
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const PortPendingReceiver = class {
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
        this.handle, 'sample.Port', scope);
  }
};

/** @interface */
export const PortInterface = class {
  
  /**
   * @param { !string } messageText
   * @param { !PortRemote } port
   */

  postMessageToPort(messageText, port) {}
};

/**
 * @implements { PortInterface }
 */
export const PortRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!PortPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          PortPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!PortPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @param { !string } messageText
   * @param { !PortRemote } port
   */

  postMessageToPort(
      messageText,
      port) {
    this.proxy.sendMessage(
        0,
        Port_PostMessageToPort_ParamsSpec.$,
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
 */
export const PortReceiver = class {
  /**
   * @param {!PortInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!PortRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        PortRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!PortRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        Port_PostMessageToPort_ParamsSpec.$,
        null,
        impl.postMessageToPort.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const Port = class {
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
   * @return {!PortRemote}
   */
  static getRemote() {
    let remote = new PortRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the Port
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const PortCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      PortRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!PortRemote>}
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
        Port_PostMessageToPort_ParamsSpec.$,
        null,
        this.postMessageToPort.createReceiverHandler(false /* expectsResponse */));
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
export const BarSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const FooSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const DefaultsTestSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const StructWithHoleV1Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const StructWithHoleV2Spec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const DefaultsSender_SendBar_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const DefaultsSender_SendFoo_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const DefaultsSender_SendDefaultsTest_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Service_Frobinate_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Service_Frobinate_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Service_GetPort_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Port_PostMessageToPort_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };



/**
 * @const { {$: !mojo.internal.MojomType} }
 */
export const Bar_TypeSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 */
export const Bar_Type = {
  
  VERTICAL: 1,
  HORIZONTAL: 2,
  BOTH: 3,
  INVALID: 4,
  MIN_VALUE: 1,
  MAX_VALUE: 4,
};


mojo.internal.Struct(
    BarSpec.$,
    'Bar',
    [
      mojo.internal.StructField(
        'alpha', 0,
        0,
        mojo.internal.Uint8,
        0xff,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'beta', 1,
        0,
        mojo.internal.Uint8,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'gamma', 2,
        0,
        mojo.internal.Uint8,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'type', 4,
        0,
        Bar_TypeSpec.$,
        Bar_Type.VERTICAL,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Bar = class {
  constructor() {
    /** @type { !number } */
    this.alpha;
    /** @type { !number } */
    this.beta;
    /** @type { !number } */
    this.gamma;
    /** @type { !Bar_Type } */
    this.type;
  }
};

/**
 * @const { !string }
 */
export const Foo_FOOBY =
    "Fooby";



mojo.internal.Struct(
    FooSpec.$,
    'Foo',
    [
      mojo.internal.StructField(
        'x', 0,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'y', 4,
        0,
        mojo.internal.Int32,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a', 8,
        0,
        mojo.internal.Bool,
        true,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'b', 8,
        1,
        mojo.internal.Bool,
        false,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'c', 8,
        2,
        mojo.internal.Bool,
        false,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'bar', 16,
        0,
        BarSpec.$,
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'data', 24,
        0,
        mojo.internal.Array(mojo.internal.Uint8, false),
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'extraBars', 32,
        0,
        mojo.internal.Array(BarSpec.$, false),
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'name', 40,
        0,
        mojo.internal.String,
        Foo_FOOBY,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'source', 12,
        0,
        mojo.internal.Handle,
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'inputStreams', 48,
        0,
        mojo.internal.Array(mojo.internal.Handle, false),
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'outputStreams', 56,
        0,
        mojo.internal.Array(mojo.internal.Handle, false),
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'arrayOfArrayOfBools', 64,
        0,
        mojo.internal.Array(mojo.internal.Array(mojo.internal.Bool, false), false),
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'multiArrayOfStrings', 72,
        0,
        mojo.internal.Array(mojo.internal.Array(mojo.internal.Array(mojo.internal.String, false), false), false),
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'arrayOfBools', 80,
        0,
        mojo.internal.Array(mojo.internal.Bool, false),
        null,
        true /* nullable */,
        0),
    ],
    [[0, 96],]);



/**
 * @record
 */
export const Foo = class {
  constructor() {
    /** @type { !number } */
    this.x;
    /** @type { !number } */
    this.y;
    /** @type { !boolean } */
    this.a;
    /** @type { !boolean } */
    this.b;
    /** @type { !boolean } */
    this.c;
    /** @type { (MojoHandle|undefined) } */
    this.source;
    /** @type { (Bar|undefined) } */
    this.bar;
    /** @type { (Array<!number>|undefined) } */
    this.data;
    /** @type { (Array<!Bar>|undefined) } */
    this.extraBars;
    /** @type { !string } */
    this.name;
    /** @type { (Array<!MojoHandle>|undefined) } */
    this.inputStreams;
    /** @type { (Array<!MojoHandle>|undefined) } */
    this.outputStreams;
    /** @type { (Array<!Array<!boolean>>|undefined) } */
    this.arrayOfArrayOfBools;
    /** @type { (Array<!Array<!Array<!string>>>|undefined) } */
    this.multiArrayOfStrings;
    /** @type { (Array<!boolean>|undefined) } */
    this.arrayOfBools;
  }
};



mojo.internal.Struct(
    DefaultsTestSpec.$,
    'DefaultsTest',
    [
      mojo.internal.StructField(
        'a0', 0,
        0,
        mojo.internal.Int8,
        -12,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a1', 1,
        0,
        mojo.internal.Uint8,
        TWELVE,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a2', 2,
        0,
        mojo.internal.Int16,
        1234,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a3', 4,
        0,
        mojo.internal.Uint16,
        34567,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a4', 8,
        0,
        mojo.internal.Int32,
        123456,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a5', 12,
        0,
        mojo.internal.Uint32,
        3456789012,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a6', 16,
        0,
        mojo.internal.Int64,
        BigInt('-111111111111'),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a7', 24,
        0,
        mojo.internal.Uint64,
        BigInt('9999999999999999999'),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a8', 32,
        0,
        mojo.internal.Int32,
        0x12345,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a9', 36,
        0,
        mojo.internal.Int32,
        -0x12345,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a10', 40,
        0,
        mojo.internal.Int32,
        +1234,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a11', 6,
        0,
        mojo.internal.Bool,
        true,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a12', 6,
        1,
        mojo.internal.Bool,
        false,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a13', 44,
        0,
        mojo.internal.Float,
        123.25,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a14', 48,
        0,
        mojo.internal.Double,
        1234567890.123,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a15', 56,
        0,
        mojo.internal.Double,
        1E10,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a16', 64,
        0,
        mojo.internal.Double,
        -1.2E+20,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a17', 72,
        0,
        mojo.internal.Double,
        +1.23E-20,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a18', 80,
        0,
        mojo.internal.Array(mojo.internal.Uint8, false),
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a19', 88,
        0,
        mojo.internal.String,
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a20', 96,
        0,
        Bar_TypeSpec.$,
        Bar_Type.BOTH,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a21', 104,
        0,
        imported_PointSpec.$,
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a22', 112,
        0,
        imported_ThingSpec.$,
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a23', 120,
        0,
        mojo.internal.Uint64,
        BigInt('18446744073709551615'),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a24', 128,
        0,
        mojo.internal.Int64,
        BigInt('4886718345'),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a25', 136,
        0,
        mojo.internal.Int64,
        BigInt('-4886718345'),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a26', 144,
        0,
        mojo.internal.Double,
        Infinity,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a27', 152,
        0,
        mojo.internal.Double,
        -Infinity,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a28', 160,
        0,
        mojo.internal.Double,
        NaN,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a29', 100,
        0,
        mojo.internal.Float,
        Infinity,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a30', 168,
        0,
        mojo.internal.Float,
        -Infinity,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'a31', 172,
        0,
        mojo.internal.Float,
        NaN,
        false /* nullable */,
        0),
    ],
    [[0, 184],]);



/**
 * @record
 */
export const DefaultsTest = class {
  constructor() {
    /** @type { !number } */
    this.a0;
    /** @type { !number } */
    this.a1;
    /** @type { !number } */
    this.a2;
    /** @type { !number } */
    this.a3;
    /** @type { !boolean } */
    this.a11;
    /** @type { !boolean } */
    this.a12;
    /** @type { !number } */
    this.a4;
    /** @type { !number } */
    this.a5;
    /** @type { !bigint } */
    this.a6;
    /** @type { !bigint } */
    this.a7;
    /** @type { !number } */
    this.a8;
    /** @type { !number } */
    this.a9;
    /** @type { !number } */
    this.a10;
    /** @type { !number } */
    this.a13;
    /** @type { !number } */
    this.a14;
    /** @type { !number } */
    this.a15;
    /** @type { !number } */
    this.a16;
    /** @type { !number } */
    this.a17;
    /** @type { !Array<!number> } */
    this.a18;
    /** @type { !string } */
    this.a19;
    /** @type { !Bar_Type } */
    this.a20;
    /** @type { !number } */
    this.a29;
    /** @type { !imported_Point } */
    this.a21;
    /** @type { !imported_Thing } */
    this.a22;
    /** @type { !bigint } */
    this.a23;
    /** @type { !bigint } */
    this.a24;
    /** @type { !bigint } */
    this.a25;
    /** @type { !number } */
    this.a26;
    /** @type { !number } */
    this.a27;
    /** @type { !number } */
    this.a28;
    /** @type { !number } */
    this.a30;
    /** @type { !number } */
    this.a31;
  }
};



mojo.internal.Struct(
    StructWithHoleV1Spec.$,
    'StructWithHoleV1',
    [
      mojo.internal.StructField(
        'v1', 0,
        0,
        mojo.internal.Int32,
        1,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'v2', 8,
        0,
        mojo.internal.Int64,
        BigInt('2'),
        false /* nullable */,
        0),
    ],
    [[0, 24],]);



/**
 * @record
 */
export const StructWithHoleV1 = class {
  constructor() {
    /** @type { !number } */
    this.v1;
    /** @type { !bigint } */
    this.v2;
  }
};



mojo.internal.Struct(
    StructWithHoleV2Spec.$,
    'StructWithHoleV2',
    [
      mojo.internal.StructField(
        'v1', 0,
        0,
        mojo.internal.Int32,
        1,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'v2', 8,
        0,
        mojo.internal.Int64,
        BigInt('2'),
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'v3', 4,
        0,
        mojo.internal.Int32,
        3,
        false /* nullable */,
        0),
    ],
    [[0, 24],]);



/**
 * @record
 */
export const StructWithHoleV2 = class {
  constructor() {
    /** @type { !number } */
    this.v1;
    /** @type { !number } */
    this.v3;
    /** @type { !bigint } */
    this.v2;
  }
};



mojo.internal.Struct(
    DefaultsSender_SendBar_ParamsSpec.$,
    'DefaultsSender_SendBar_Params',
    [
      mojo.internal.StructField(
        'bar', 0,
        0,
        BarSpec.$,
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const DefaultsSender_SendBar_Params = class {
  constructor() {
    /** @type { !Bar } */
    this.bar;
  }
};



mojo.internal.Struct(
    DefaultsSender_SendFoo_ParamsSpec.$,
    'DefaultsSender_SendFoo_Params',
    [
      mojo.internal.StructField(
        'foo', 0,
        0,
        FooSpec.$,
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const DefaultsSender_SendFoo_Params = class {
  constructor() {
    /** @type { !Foo } */
    this.foo;
  }
};



mojo.internal.Struct(
    DefaultsSender_SendDefaultsTest_ParamsSpec.$,
    'DefaultsSender_SendDefaultsTest_Params',
    [
      mojo.internal.StructField(
        'defaults', 0,
        0,
        DefaultsTestSpec.$,
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const DefaultsSender_SendDefaultsTest_Params = class {
  constructor() {
    /** @type { !DefaultsTest } */
    this.defaults;
  }
};



mojo.internal.Struct(
    Service_Frobinate_ParamsSpec.$,
    'Service_Frobinate_Params',
    [
      mojo.internal.StructField(
        'foo', 0,
        0,
        FooSpec.$,
        null,
        true /* nullable */,
        0),
      mojo.internal.StructField(
        'baz', 8,
        0,
        Service_BazOptionsSpec.$,
        0,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'port', 12,
        0,
        mojo.internal.InterfaceProxy(PortRemote),
        null,
        true /* nullable */,
        0),
    ],
    [[0, 32],]);



/**
 * @record
 */
export const Service_Frobinate_Params = class {
  constructor() {
    /** @type { (Foo|undefined) } */
    this.foo;
    /** @type { !Service_BazOptions } */
    this.baz;
    /** @type { (PortRemote|undefined) } */
    this.port;
  }
};



mojo.internal.Struct(
    Service_Frobinate_ResponseParamsSpec.$,
    'Service_Frobinate_ResponseParams',
    [
      mojo.internal.StructField(
        'result', 0,
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
export const Service_Frobinate_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.result;
  }
};



mojo.internal.Struct(
    Service_GetPort_ParamsSpec.$,
    'Service_GetPort_Params',
    [
      mojo.internal.StructField(
        'receiver', 0,
        0,
        mojo.internal.InterfaceRequest(PortPendingReceiver),
        null,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Service_GetPort_Params = class {
  constructor() {
    /** @type { !PortPendingReceiver } */
    this.receiver;
  }
};



mojo.internal.Struct(
    Port_PostMessageToPort_ParamsSpec.$,
    'Port_PostMessageToPort_Params',
    [
      mojo.internal.StructField(
        'messageText', 0,
        0,
        mojo.internal.String,
        null,
        false /* nullable */,
        0),
      mojo.internal.StructField(
        'port', 8,
        0,
        mojo.internal.InterfaceProxy(PortRemote),
        null,
        false /* nullable */,
        0),
    ],
    [[0, 24],]);



/**
 * @record
 */
export const Port_PostMessageToPort_Params = class {
  constructor() {
    /** @type { !string } */
    this.messageText;
    /** @type { !PortRemote } */
    this.port;
  }
};
