// mojo/public/interfaces/bindings/tests/math_calculator.mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';




/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const CalculatorPendingReceiver = class {
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
        this.handle, 'math.Calculator', scope);
  }
};

/** @interface */
export const CalculatorInterface = class {
  
  /**
   * @return {!Promise<{
        value: !number,
   *  }>}
   */

  clear() {}
  
  /**
   * @param { !number } value
   * @return {!Promise<{
        value: !number,
   *  }>}
   */

  add(value) {}
  
  /**
   * @param { !number } value
   * @return {!Promise<{
        value: !number,
   *  }>}
   */

  multiply(value) {}
};

/**
 * @implements { CalculatorInterface }
 */
export const CalculatorRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!CalculatorPendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          CalculatorPendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!CalculatorPendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   * @return {!Promise<{
        value: !number,
   *  }>}
   */

  clear() {
    return this.proxy.sendMessage(
        0,
        Calculator_Clear_ParamsSpec.$,
        Calculator_Clear_ResponseParamsSpec.$,
        [
        ]);
  }

  
  /**
   * @param { !number } value
   * @return {!Promise<{
        value: !number,
   *  }>}
   */

  add(
      value) {
    return this.proxy.sendMessage(
        1,
        Calculator_Add_ParamsSpec.$,
        Calculator_Add_ResponseParamsSpec.$,
        [
          value
        ]);
  }

  
  /**
   * @param { !number } value
   * @return {!Promise<{
        value: !number,
   *  }>}
   */

  multiply(
      value) {
    return this.proxy.sendMessage(
        2,
        Calculator_Multiply_ParamsSpec.$,
        Calculator_Multiply_ResponseParamsSpec.$,
        [
          value
        ]);
  }
};

/**
 * An object which receives request messages for the Calculator
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 */
export const CalculatorReceiver = class {
  /**
   * @param {!CalculatorInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!CalculatorRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        CalculatorRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!CalculatorRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        0,
        Calculator_Clear_ParamsSpec.$,
        Calculator_Clear_ResponseParamsSpec.$,
        impl.clear.bind(impl));
    this.helper_internal_.registerHandler(
        1,
        Calculator_Add_ParamsSpec.$,
        Calculator_Add_ResponseParamsSpec.$,
        impl.add.bind(impl));
    this.helper_internal_.registerHandler(
        2,
        Calculator_Multiply_ParamsSpec.$,
        Calculator_Multiply_ResponseParamsSpec.$,
        impl.multiply.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const Calculator = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "math.Calculator";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!CalculatorRemote}
   */
  static getRemote() {
    let remote = new CalculatorRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the Calculator
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const CalculatorCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      CalculatorRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!CalculatorRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);

    this.router_ = new mojo.internal.interfaceSupport.CallbackRouter;

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.clear =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        0,
        Calculator_Clear_ParamsSpec.$,
        Calculator_Clear_ResponseParamsSpec.$,
        this.clear.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.add =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        1,
        Calculator_Add_ParamsSpec.$,
        Calculator_Add_ResponseParamsSpec.$,
        this.add.createReceiverHandler(true /* expectsResponse */));
    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceCallbackReceiver}
     */
    this.multiply =
        new mojo.internal.interfaceSupport.InterfaceCallbackReceiver(
            this.router_);

    this.helper_internal_.registerHandler(
        2,
        Calculator_Multiply_ParamsSpec.$,
        Calculator_Multiply_ResponseParamsSpec.$,
        this.multiply.createReceiverHandler(true /* expectsResponse */));
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
export const Calculator_Clear_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Calculator_Clear_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Calculator_Add_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Calculator_Add_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Calculator_Multiply_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const Calculator_Multiply_ResponseParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    Calculator_Clear_ParamsSpec.$,
    'Calculator_Clear_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const Calculator_Clear_Params = class {
  constructor() {
  }
};



mojo.internal.Struct(
    Calculator_Clear_ResponseParamsSpec.$,
    'Calculator_Clear_ResponseParams',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Double,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Calculator_Clear_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};



mojo.internal.Struct(
    Calculator_Add_ParamsSpec.$,
    'Calculator_Add_Params',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Double,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Calculator_Add_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};



mojo.internal.Struct(
    Calculator_Add_ResponseParamsSpec.$,
    'Calculator_Add_ResponseParams',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Double,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Calculator_Add_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};



mojo.internal.Struct(
    Calculator_Multiply_ParamsSpec.$,
    'Calculator_Multiply_Params',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Double,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Calculator_Multiply_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};



mojo.internal.Struct(
    Calculator_Multiply_ResponseParamsSpec.$,
    'Calculator_Multiply_ResponseParams',
    [
      mojo.internal.StructField(
        'value', 0,
        0,
        mojo.internal.Double,
        0,
        false /* nullable */,
        0),
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Calculator_Multiply_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

