// mojo/public/interfaces/bindings/tests/test_sync_methods.mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



goog.provide('mojo.test.TestSyncCodeGeneration');
goog.provide('mojo.test.TestSyncCodeGenerationImpl');
goog.provide('mojo.test.TestSyncCodeGenerationPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.TestSyncCodeGeneration;

/** @interface */
mojo.test.TestSyncCodeGenerationImpl = class {
  /**
   * @return {Promise}
   */
  noInput() {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  noOutput(value) {}
  /**
   * @return {Promise}
   */
  noInOut() {}
  /**
   * @param { !number } value1
   * @param { !number } value2
   * @return {Promise}
   */
  haveInOut(value1, value2) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.TestSyncCodeGenerationImpl }
 */
mojo.test.TestSyncCodeGenerationPtr = class {
  /**
   * @return {Promise}
   */
  noInput() {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  noOutput(value) {}
  /**
   * @return {Promise}
   */
  noInOut() {}
  /**
   * @param { !number } value1
   * @param { !number } value2
   * @return {Promise}
   */
  haveInOut(value1, value2) {}
};

goog.provide('mojo.test.TestSync');
goog.provide('mojo.test.TestSyncImpl');
goog.provide('mojo.test.TestSyncPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.TestSync;

/** @interface */
mojo.test.TestSyncImpl = class {
  /**
   * @return {Promise}
   */
  ping() {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  asyncEcho(value) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.TestSyncImpl }
 */
mojo.test.TestSyncPtr = class {
  /**
   * @return {Promise}
   */
  ping() {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  asyncEcho(value) {}
};

goog.provide('mojo.test.TestSyncPrimary');
goog.provide('mojo.test.TestSyncPrimaryImpl');
goog.provide('mojo.test.TestSyncPrimaryPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.TestSyncPrimary;

/** @interface */
mojo.test.TestSyncPrimaryImpl = class {
  /**
   * @return {Promise}
   */
  ping() {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  asyncEcho(value) {}
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } remote
   */
  sendRemote(remote) {}
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  sendReceiver(receiver) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.TestSyncPrimaryImpl }
 */
mojo.test.TestSyncPrimaryPtr = class {
  /**
   * @return {Promise}
   */
  ping() {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !number } value
   * @return {Promise}
   */
  asyncEcho(value) {}
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } remote
   */
  sendRemote(remote) {}
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  sendReceiver(receiver) {}
};

goog.provide('mojo.test.TestSyncCodeGeneration_NoInput_Params');

mojo.test.TestSyncCodeGeneration_NoInput_Params = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSyncCodeGeneration_NoInput_ResponseParams');

mojo.test.TestSyncCodeGeneration_NoInput_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.result;
  }
};

goog.provide('mojo.test.TestSyncCodeGeneration_NoOutput_Params');

mojo.test.TestSyncCodeGeneration_NoOutput_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.TestSyncCodeGeneration_NoOutput_ResponseParams');

mojo.test.TestSyncCodeGeneration_NoOutput_ResponseParams = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSyncCodeGeneration_NoInOut_Params');

mojo.test.TestSyncCodeGeneration_NoInOut_Params = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSyncCodeGeneration_NoInOut_ResponseParams');

mojo.test.TestSyncCodeGeneration_NoInOut_ResponseParams = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSyncCodeGeneration_HaveInOut_Params');

mojo.test.TestSyncCodeGeneration_HaveInOut_Params = class {
  constructor() {
    /** @type { !number } */
    this.value1;
    /** @type { !number } */
    this.value2;
  }
};

goog.provide('mojo.test.TestSyncCodeGeneration_HaveInOut_ResponseParams');

mojo.test.TestSyncCodeGeneration_HaveInOut_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.result1;
    /** @type { !number } */
    this.result2;
  }
};

goog.provide('mojo.test.TestSync_Ping_Params');

mojo.test.TestSync_Ping_Params = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSync_Ping_ResponseParams');

mojo.test.TestSync_Ping_ResponseParams = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSync_Echo_Params');

mojo.test.TestSync_Echo_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.TestSync_Echo_ResponseParams');

mojo.test.TestSync_Echo_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.result;
  }
};

goog.provide('mojo.test.TestSync_AsyncEcho_Params');

mojo.test.TestSync_AsyncEcho_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.TestSync_AsyncEcho_ResponseParams');

mojo.test.TestSync_AsyncEcho_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.result;
  }
};

goog.provide('mojo.test.TestSyncPrimary_Ping_Params');

mojo.test.TestSyncPrimary_Ping_Params = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSyncPrimary_Ping_ResponseParams');

mojo.test.TestSyncPrimary_Ping_ResponseParams = class {
  constructor() {
  }
};

goog.provide('mojo.test.TestSyncPrimary_Echo_Params');

mojo.test.TestSyncPrimary_Echo_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.TestSyncPrimary_Echo_ResponseParams');

mojo.test.TestSyncPrimary_Echo_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.result;
  }
};

goog.provide('mojo.test.TestSyncPrimary_AsyncEcho_Params');

mojo.test.TestSyncPrimary_AsyncEcho_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.TestSyncPrimary_AsyncEcho_ResponseParams');

mojo.test.TestSyncPrimary_AsyncEcho_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.result;
  }
};

goog.provide('mojo.test.TestSyncPrimary_SendRemote_Params');

mojo.test.TestSyncPrimary_SendRemote_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfacePtrInfo } */
    this.remote;
  }
};

goog.provide('mojo.test.TestSyncPrimary_SendReceiver_Params');

mojo.test.TestSyncPrimary_SendReceiver_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.receiver;
  }
};
