// mojo/public/interfaces/bindings/tests/sample_import.mojom.m.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import {mojo} from '../../../js/bindings.js';


/**
 * @const { {$: !mojo.internal.MojomType} }
 */
export const ShapeSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 */
export const Shape = {
  
  RECTANGLE: 1,
  CIRCLE: 2,
  TRIANGLE: 3,
  LAST: 3,
  MIN_VALUE: 1,
  MAX_VALUE: 3,
};

/**
 * @const { {$: !mojo.internal.MojomType} }
 */
export const AnotherShapeSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 */
export const AnotherShape = {
  
  RECTANGLE: 10,
  CIRCLE: 11,
  TRIANGLE: 12,
  MIN_VALUE: 10,
  MAX_VALUE: 12,
};

/**
 * @const { {$: !mojo.internal.MojomType} }
 */
export const YetAnotherShapeSpec = { $: mojo.internal.Enum() };

/**
 * @enum {number}
 */
export const YetAnotherShape = {
  
  RECTANGLE: 20,
  CIRCLE: 21,
  TRIANGLE: 22,
  MIN_VALUE: 20,
  MAX_VALUE: 22,
};



/**
 * @implements {mojo.internal.interfaceSupport.PendingReceiver}
 */
export const ImportedInterfacePendingReceiver = class {
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
        this.handle, 'imported.ImportedInterface', scope);
  }
};

/** @interface */
export const ImportedInterfaceInterface = class {
  
  /**
   */

  doSomething() {}
};

/**
 * @implements { ImportedInterfaceInterface }
 */
export const ImportedInterfaceRemote = class {
  /** @param {MojoHandle|mojo.internal.interfaceSupport.Endpoint=} handle */
  constructor(handle = undefined) {
    /**
     * @private {!mojo.internal.interfaceSupport.InterfaceRemoteBase<!ImportedInterfacePendingReceiver>}
     */
    this.proxy =
        new mojo.internal.interfaceSupport.InterfaceRemoteBase(
          ImportedInterfacePendingReceiver,
          handle);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper<!ImportedInterfacePendingReceiver>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceRemoteBaseWrapper(this.proxy);

    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.proxy.getConnectionErrorEventRouter();
  }

  
  /**
   */

  doSomething() {
    this.proxy.sendMessage(
        912963854,
        ImportedInterface_DoSomething_ParamsSpec.$,
        null,
        [
        ]);
  }
};

/**
 * An object which receives request messages for the ImportedInterface
 * mojom interface. Must be constructed over an object which implements that
 * interface.
 */
export const ImportedInterfaceReceiver = class {
  /**
   * @param {!ImportedInterfaceInterface } impl
   */
  constructor(impl) {
    /** @private {!mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal<!ImportedInterfaceRemote>} */
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
        ImportedInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!ImportedInterfaceRemote>}
     */
    this.$ = new mojo.internal.interfaceSupport.InterfaceReceiverHelper(this.helper_internal_);


    this.helper_internal_.registerHandler(
        912963854,
        ImportedInterface_DoSomething_ParamsSpec.$,
        null,
        impl.doSomething.bind(impl));
    /** @public {!mojo.internal.interfaceSupport.ConnectionErrorEventRouter} */
    this.onConnectionError = this.helper_internal_.getConnectionErrorEventRouter();
  }
};

export const ImportedInterface = class {
  /**
   * @return {!string}
   */
  static get $interfaceName() {
    return "imported.ImportedInterface";
  }

  /**
   * Returns a remote for this interface which sends messages to the browser.
   * The browser must have an interface request binder registered for this
   * interface and accessible to the calling document's frame.
   *
   * @return {!ImportedInterfaceRemote}
   */
  static getRemote() {
    let remote = new ImportedInterfaceRemote;
    remote.$.bindNewPipeAndPassReceiver().bindInBrowser();
    return remote;
  }
};


/**
 * An object which receives request messages for the ImportedInterface
 * mojom interface and dispatches them as callbacks. One callback receiver exists
 * on this object for each message defined in the mojom interface, and each
 * receiver can have any number of listeners added to it.
 */
export const ImportedInterfaceCallbackRouter = class {
  constructor() {
    this.helper_internal_ = new mojo.internal.interfaceSupport.InterfaceReceiverHelperInternal(
      ImportedInterfaceRemote);

    /**
     * @public {!mojo.internal.interfaceSupport.InterfaceReceiverHelper<!ImportedInterfaceRemote>}
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
        912963854,
        ImportedInterface_DoSomething_ParamsSpec.$,
        null,
        this.doSomething.createReceiverHandler(false /* expectsResponse */));
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
export const PointSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType}}
 */
export const ImportedInterface_DoSomething_ParamsSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };

/**
 * @const { {$:!mojo.internal.MojomType} }
 */
export const PointOrShapeSpec =
    { $: /** @type {!mojo.internal.MojomType} */ ({}) };




mojo.internal.Struct(
    PointSpec.$,
    'Point',
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
    ],
    [[0, 16],]);



/**
 * @record
 */
export const Point = class {
  constructor() {
    /** @type { !number } */
    this.x;
    /** @type { !number } */
    this.y;
  }
};



mojo.internal.Struct(
    ImportedInterface_DoSomething_ParamsSpec.$,
    'ImportedInterface_DoSomething_Params',
    [
    ],
    [[0, 8],]);



/**
 * @record
 */
export const ImportedInterface_DoSomething_Params = class {
  constructor() {
  }
};

mojo.internal.Union(
    PointOrShapeSpec.$, 'PointOrShape',
    {
      'point': {
        'ordinal': 0,
        'type': PointSpec.$,
      },
      'shape': {
        'ordinal': 1,
        'type': ShapeSpec.$,
      },
    });

/**
 * @typedef { {
 *   point: (!Point|undefined),
 *   shape: (!Shape|undefined),
 * } }
 */
export const PointOrShape = {};
