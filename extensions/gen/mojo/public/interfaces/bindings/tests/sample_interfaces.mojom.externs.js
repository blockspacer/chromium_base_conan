// mojo/public/interfaces/bindings/tests/sample_interfaces.mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


/** @type { !number } */
goog.provide('sample.LONG');

/** @enum {number} */
sample.Enum = {};
sample.Enum.VALUE;
goog.provide('sample.PingTest');
goog.provide('sample.PingTestImpl');
goog.provide('sample.PingTestPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
sample.PingTest;

/** @interface */
sample.PingTestImpl = class {
  /**
   * @return {Promise}
   */
  ping() {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { sample.PingTestImpl }
 */
sample.PingTestPtr = class {
  /**
   * @return {Promise}
   */
  ping() {}
};

goog.provide('sample.Provider');
goog.provide('sample.ProviderImpl');
goog.provide('sample.ProviderPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
sample.Provider;

/** @interface */
sample.ProviderImpl = class {
  /**
   * @param { !string } a
   * @return {Promise}
   */
  echoString(a) {}
  /**
   * @param { !string } a
   * @param { !string } b
   * @return {Promise}
   */
  echoStrings(a, b) {}
  /**
   * @param { !MojoHandle } a
   * @return {Promise}
   */
  echoMessagePipeHandle(a) {}
  /**
   * @param { !sample.Enum } a
   * @return {Promise}
   */
  echoEnum(a) {}
  /**
   * @param { !number } a
   * @return {Promise}
   */
  echoInt(a) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { sample.ProviderImpl }
 */
sample.ProviderPtr = class {
  /**
   * @param { !string } a
   * @return {Promise}
   */
  echoString(a) {}
  /**
   * @param { !string } a
   * @param { !string } b
   * @return {Promise}
   */
  echoStrings(a, b) {}
  /**
   * @param { !MojoHandle } a
   * @return {Promise}
   */
  echoMessagePipeHandle(a) {}
  /**
   * @param { !sample.Enum } a
   * @return {Promise}
   */
  echoEnum(a) {}
  /**
   * @param { !number } a
   * @return {Promise}
   */
  echoInt(a) {}
};

goog.provide('sample.IntegerAccessor');
goog.provide('sample.IntegerAccessorImpl');
goog.provide('sample.IntegerAccessorPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
sample.IntegerAccessor;

/** @interface */
sample.IntegerAccessorImpl = class {
  /**
   * @return {Promise}
   */
  getInteger() {}
  /**
   * @param { !number } data
   * @param { !sample.Enum } type
   */
  setInteger(data, type) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { sample.IntegerAccessorImpl }
 */
sample.IntegerAccessorPtr = class {
  /**
   * @return {Promise}
   */
  getInteger() {}
  /**
   * @param { !number } data
   * @param { !sample.Enum } type
   */
  setInteger(data, type) {}
};

goog.provide('sample.InterfaceFactory');
goog.provide('sample.InterfaceFactoryImpl');
goog.provide('sample.InterfaceFactoryPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
sample.InterfaceFactory;

/** @interface */
sample.InterfaceFactoryImpl = class {
  /**
   * @param { !mojoBase.mojom.GenericPendingReceiver } receiver
   */
  bindInterface(receiver) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { sample.InterfaceFactoryImpl }
 */
sample.InterfaceFactoryPtr = class {
  /**
   * @param { !mojoBase.mojom.GenericPendingReceiver } receiver
   */
  bindInterface(receiver) {}
};

goog.provide('sample.PingTest_Ping_Params');

sample.PingTest_Ping_Params = class {
  constructor() {
  }
};

goog.provide('sample.PingTest_Ping_ResponseParams');

sample.PingTest_Ping_ResponseParams = class {
  constructor() {
  }
};

goog.provide('sample.Provider_EchoString_Params');

sample.Provider_EchoString_Params = class {
  constructor() {
    /** @type { !string } */
    this.a;
  }
};

goog.provide('sample.Provider_EchoString_ResponseParams');

sample.Provider_EchoString_ResponseParams = class {
  constructor() {
    /** @type { !string } */
    this.a;
  }
};

goog.provide('sample.Provider_EchoStrings_Params');

sample.Provider_EchoStrings_Params = class {
  constructor() {
    /** @type { !string } */
    this.a;
    /** @type { !string } */
    this.b;
  }
};

goog.provide('sample.Provider_EchoStrings_ResponseParams');

sample.Provider_EchoStrings_ResponseParams = class {
  constructor() {
    /** @type { !string } */
    this.a;
    /** @type { !string } */
    this.b;
  }
};

goog.provide('sample.Provider_EchoMessagePipeHandle_Params');

sample.Provider_EchoMessagePipeHandle_Params = class {
  constructor() {
    /** @type { !MojoHandle } */
    this.a;
  }
};

goog.provide('sample.Provider_EchoMessagePipeHandle_ResponseParams');

sample.Provider_EchoMessagePipeHandle_ResponseParams = class {
  constructor() {
    /** @type { !MojoHandle } */
    this.a;
  }
};

goog.provide('sample.Provider_EchoEnum_Params');

sample.Provider_EchoEnum_Params = class {
  constructor() {
    /** @type { !sample.Enum } */
    this.a;
  }
};

goog.provide('sample.Provider_EchoEnum_ResponseParams');

sample.Provider_EchoEnum_ResponseParams = class {
  constructor() {
    /** @type { !sample.Enum } */
    this.a;
  }
};

goog.provide('sample.Provider_EchoInt_Params');

sample.Provider_EchoInt_Params = class {
  constructor() {
    /** @type { !number } */
    this.a;
  }
};

goog.provide('sample.Provider_EchoInt_ResponseParams');

sample.Provider_EchoInt_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.a;
  }
};

goog.provide('sample.IntegerAccessor_GetInteger_Params');

sample.IntegerAccessor_GetInteger_Params = class {
  constructor() {
  }
};

goog.provide('sample.IntegerAccessor_GetInteger_ResponseParams');

sample.IntegerAccessor_GetInteger_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.data;
    /** @type { !sample.Enum } */
    this.type;
  }
};

goog.provide('sample.IntegerAccessor_SetInteger_Params');

sample.IntegerAccessor_SetInteger_Params = class {
  constructor() {
    /** @type { !number } */
    this.data;
    /** @type { !sample.Enum } */
    this.type;
  }
};

goog.provide('sample.InterfaceFactory_BindInterface_Params');

sample.InterfaceFactory_BindInterface_Params = class {
  constructor() {
    /** @type { !mojoBase.mojom.GenericPendingReceiver } */
    this.receiver;
  }
};
