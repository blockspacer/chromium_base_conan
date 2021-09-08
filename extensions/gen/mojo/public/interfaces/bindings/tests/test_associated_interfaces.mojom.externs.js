// mojo/public/interfaces/bindings/tests/test_associated_interfaces.mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



goog.provide('mojo.test.FooInterface');
goog.provide('mojo.test.FooInterfaceImpl');
goog.provide('mojo.test.FooInterfacePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.FooInterface;

/** @interface */
mojo.test.FooInterfaceImpl = class {
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.FooInterfaceImpl }
 */
mojo.test.FooInterfacePtr = class {
};

goog.provide('mojo.test.InterfacePassesAssociated');
goog.provide('mojo.test.InterfacePassesAssociatedImpl');
goog.provide('mojo.test.InterfacePassesAssociatedPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.InterfacePassesAssociated;

/** @interface */
mojo.test.InterfacePassesAssociatedImpl = class {
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } fooRemote
   * @param { !mojo.AssociatedInterfaceRequest } fooReceiver
   * @return {Promise}
   */
  passFoo(fooRemote, fooReceiver) {}
  /**
   * @param { !mojo.test.StructContainsAssociated } fooStruct
   * @return {Promise}
   */
  passStruct(fooStruct) {}
  /**
   * @param { !Object } fooUnion
   * @return {Promise}
   */
  passUnion(fooUnion) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.InterfacePassesAssociatedImpl }
 */
mojo.test.InterfacePassesAssociatedPtr = class {
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } fooRemote
   * @param { !mojo.AssociatedInterfaceRequest } fooReceiver
   * @return {Promise}
   */
  passFoo(fooRemote, fooReceiver) {}
  /**
   * @param { !mojo.test.StructContainsAssociated } fooStruct
   * @return {Promise}
   */
  passStruct(fooStruct) {}
  /**
   * @param { !Object } fooUnion
   * @return {Promise}
   */
  passUnion(fooUnion) {}
};

goog.provide('mojo.test.IntegerSender');
goog.provide('mojo.test.IntegerSenderImpl');
goog.provide('mojo.test.IntegerSenderPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.IntegerSender;

/** @interface */
mojo.test.IntegerSenderImpl = class {
  /**
   * @param { !number } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !number } value
   */
  send(value) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.IntegerSenderImpl }
 */
mojo.test.IntegerSenderPtr = class {
  /**
   * @param { !number } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !number } value
   */
  send(value) {}
};

goog.provide('mojo.test.StringSender');
goog.provide('mojo.test.StringSenderImpl');
goog.provide('mojo.test.StringSenderPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.StringSender;

/** @interface */
mojo.test.StringSenderImpl = class {
  /**
   * @param { !string } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !string } value
   */
  send(value) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.StringSenderImpl }
 */
mojo.test.StringSenderPtr = class {
  /**
   * @param { !string } value
   * @return {Promise}
   */
  echo(value) {}
  /**
   * @param { !string } value
   */
  send(value) {}
};

goog.provide('mojo.test.IntegerSenderConnection');
goog.provide('mojo.test.IntegerSenderConnectionImpl');
goog.provide('mojo.test.IntegerSenderConnectionPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.IntegerSenderConnection;

/** @interface */
mojo.test.IntegerSenderConnectionImpl = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getSender(receiver) {}
  /**
   * @return {Promise}
   */
  asyncGetSender() {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.IntegerSenderConnectionImpl }
 */
mojo.test.IntegerSenderConnectionPtr = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getSender(receiver) {}
  /**
   * @return {Promise}
   */
  asyncGetSender() {}
};

goog.provide('mojo.test.IntegerSenderConnectionAtBothEnds');
goog.provide('mojo.test.IntegerSenderConnectionAtBothEndsImpl');
goog.provide('mojo.test.IntegerSenderConnectionAtBothEndsPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.IntegerSenderConnectionAtBothEnds;

/** @interface */
mojo.test.IntegerSenderConnectionAtBothEndsImpl = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getSender(receiver) {}
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } sender
   * @return {Promise}
   */
  setSender(sender) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.IntegerSenderConnectionAtBothEndsImpl }
 */
mojo.test.IntegerSenderConnectionAtBothEndsPtr = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getSender(receiver) {}
  /**
   * @param { !mojo.AssociatedInterfacePtrInfo } sender
   * @return {Promise}
   */
  setSender(sender) {}
};

goog.provide('mojo.test.SenderConnection');
goog.provide('mojo.test.SenderConnectionImpl');
goog.provide('mojo.test.SenderConnectionPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.SenderConnection;

/** @interface */
mojo.test.SenderConnectionImpl = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getIntegerSender(receiver) {}
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getStringSender(receiver) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.SenderConnectionImpl }
 */
mojo.test.SenderConnectionPtr = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getIntegerSender(receiver) {}
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getStringSender(receiver) {}
};

goog.provide('mojo.test.AssociatedPingProvider');
goog.provide('mojo.test.AssociatedPingProviderImpl');
goog.provide('mojo.test.AssociatedPingProviderPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.AssociatedPingProvider;

/** @interface */
mojo.test.AssociatedPingProviderImpl = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getPing(receiver) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.AssociatedPingProviderImpl }
 */
mojo.test.AssociatedPingProviderPtr = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getPing(receiver) {}
};

goog.provide('mojo.test.AssociatedPingProviderProvider');
goog.provide('mojo.test.AssociatedPingProviderProviderImpl');
goog.provide('mojo.test.AssociatedPingProviderProviderPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.AssociatedPingProviderProvider;

/** @interface */
mojo.test.AssociatedPingProviderProviderImpl = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getPingProvider(receiver) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.AssociatedPingProviderProviderImpl }
 */
mojo.test.AssociatedPingProviderProviderPtr = class {
  /**
   * @param { !mojo.AssociatedInterfaceRequest } receiver
   */
  getPingProvider(receiver) {}
};

goog.provide('mojo.test.StructContainsAssociated');

mojo.test.StructContainsAssociated = class {
  constructor() {
    /** @type { mojo.AssociatedInterfacePtrInfo } */
    this.fooRemote;
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.fooReceiver;
    /** @type { !Array<mojo.AssociatedInterfacePtrInfo> } */
    this.fooRemotes;
    /** @type { !Array<mojo.AssociatedInterfaceRequest> } */
    this.fooReceivers;
  }
};

goog.provide('mojo.test.InterfacePassesAssociated_PassFoo_Params');

mojo.test.InterfacePassesAssociated_PassFoo_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfacePtrInfo } */
    this.fooRemote;
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.fooReceiver;
  }
};

goog.provide('mojo.test.InterfacePassesAssociated_PassFoo_ResponseParams');

mojo.test.InterfacePassesAssociated_PassFoo_ResponseParams = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfacePtrInfo } */
    this.fooRemote;
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.fooReceiver;
  }
};

goog.provide('mojo.test.InterfacePassesAssociated_PassStruct_Params');

mojo.test.InterfacePassesAssociated_PassStruct_Params = class {
  constructor() {
    /** @type { !mojo.test.StructContainsAssociated } */
    this.fooStruct;
  }
};

goog.provide('mojo.test.InterfacePassesAssociated_PassStruct_ResponseParams');

mojo.test.InterfacePassesAssociated_PassStruct_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.StructContainsAssociated } */
    this.fooStruct;
  }
};

goog.provide('mojo.test.InterfacePassesAssociated_PassUnion_Params');

mojo.test.InterfacePassesAssociated_PassUnion_Params = class {
  constructor() {
    /** @type { !Object } */
    this.fooUnion;
  }
};

goog.provide('mojo.test.InterfacePassesAssociated_PassUnion_ResponseParams');

mojo.test.InterfacePassesAssociated_PassUnion_ResponseParams = class {
  constructor() {
    /** @type { !Object } */
    this.fooUnion;
  }
};

goog.provide('mojo.test.IntegerSender_Echo_Params');

mojo.test.IntegerSender_Echo_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.IntegerSender_Echo_ResponseParams');

mojo.test.IntegerSender_Echo_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.IntegerSender_Send_Params');

mojo.test.IntegerSender_Send_Params = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.StringSender_Echo_Params');

mojo.test.StringSender_Echo_Params = class {
  constructor() {
    /** @type { !string } */
    this.value;
  }
};

goog.provide('mojo.test.StringSender_Echo_ResponseParams');

mojo.test.StringSender_Echo_ResponseParams = class {
  constructor() {
    /** @type { !string } */
    this.value;
  }
};

goog.provide('mojo.test.StringSender_Send_Params');

mojo.test.StringSender_Send_Params = class {
  constructor() {
    /** @type { !string } */
    this.value;
  }
};

goog.provide('mojo.test.IntegerSenderConnection_GetSender_Params');

mojo.test.IntegerSenderConnection_GetSender_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.receiver;
  }
};

goog.provide('mojo.test.IntegerSenderConnection_AsyncGetSender_Params');

mojo.test.IntegerSenderConnection_AsyncGetSender_Params = class {
  constructor() {
  }
};

goog.provide('mojo.test.IntegerSenderConnection_AsyncGetSender_ResponseParams');

mojo.test.IntegerSenderConnection_AsyncGetSender_ResponseParams = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfacePtrInfo } */
    this.sender;
  }
};

goog.provide('mojo.test.IntegerSenderConnectionAtBothEnds_GetSender_Params');

mojo.test.IntegerSenderConnectionAtBothEnds_GetSender_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.receiver;
  }
};

goog.provide('mojo.test.IntegerSenderConnectionAtBothEnds_SetSender_Params');

mojo.test.IntegerSenderConnectionAtBothEnds_SetSender_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfacePtrInfo } */
    this.sender;
  }
};

goog.provide('mojo.test.IntegerSenderConnectionAtBothEnds_SetSender_ResponseParams');

mojo.test.IntegerSenderConnectionAtBothEnds_SetSender_ResponseParams = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.SenderConnection_GetIntegerSender_Params');

mojo.test.SenderConnection_GetIntegerSender_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.receiver;
  }
};

goog.provide('mojo.test.SenderConnection_GetStringSender_Params');

mojo.test.SenderConnection_GetStringSender_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.receiver;
  }
};

goog.provide('mojo.test.AssociatedPingProvider_GetPing_Params');

mojo.test.AssociatedPingProvider_GetPing_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.receiver;
  }
};

goog.provide('mojo.test.AssociatedPingProviderProvider_GetPingProvider_Params');

mojo.test.AssociatedPingProviderProvider_GetPingProvider_Params = class {
  constructor() {
    /** @type { !mojo.AssociatedInterfaceRequest } */
    this.receiver;
  }
};