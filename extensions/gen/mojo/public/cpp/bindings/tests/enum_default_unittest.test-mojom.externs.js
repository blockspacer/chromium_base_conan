// mojo/public/cpp/bindings/tests/enum_default_unittest.test-mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



/** @enum {number} */
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault = {};
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault.kZeroth;
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault.kFirst;
/** @enum {number} */
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault = {};
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault.kZeroth;
mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault.kFirst;
/** @enum {number} */
mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue = {};
mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue.kFirst;
mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue.kSecond;
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface');
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterfaceImpl');
goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterfacePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.enumDefaultUnittest.mojom.TestInterface;

/** @interface */
mojo.test.enumDefaultUnittest.mojom.TestInterfaceImpl = class {
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } in_
   * @return {Promise}
   */
  echoWithDefault(in_) {}
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } in_
   * @return {Promise}
   */
  echoWithoutDefault(in_) {}
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } in_
   * @return {Promise}
   */
  echoStructWithDefault(in_) {}
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } in_
   * @return {Promise}
   */
  echoStructWithoutDefault(in_) {}
  /**
   * @param { !Object } in_
   * @return {Promise}
   */
  echoUnionWithDefault(in_) {}
  /**
   * @param { !Object } in_
   * @return {Promise}
   */
  echoUnionWithoutDefault(in_) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.enumDefaultUnittest.mojom.TestInterfaceImpl }
 */
mojo.test.enumDefaultUnittest.mojom.TestInterfacePtr = class {
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } in_
   * @return {Promise}
   */
  echoWithDefault(in_) {}
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } in_
   * @return {Promise}
   */
  echoWithoutDefault(in_) {}
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } in_
   * @return {Promise}
   */
  echoStructWithDefault(in_) {}
  /**
   * @param { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } in_
   * @return {Promise}
   */
  echoStructWithoutDefault(in_) {}
  /**
   * @param { !Object } in_
   * @return {Promise}
   */
  echoUnionWithDefault(in_) {}
  /**
   * @param { !Object } in_
   * @return {Promise}
   */
  echoUnionWithoutDefault(in_) {}
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault');

mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } */
    this.value;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault');

mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } */
    this.value;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithoutInitializer');

mojo.test.enumDefaultUnittest.mojom.StructWithoutInitializer = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue } */
    this.value;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.StructWithInitializer');

mojo.test.enumDefaultUnittest.mojom.StructWithInitializer = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.EnumWithoutZeroValue } */
    this.value;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_Params');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_Params = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } */
    this.in;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParams');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithDefault_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithDefault } */
    this.out;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_Params');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_Params = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } */
    this.in;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParams');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoWithoutDefault_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.ExtensibleEnumWithoutDefault } */
    this.out;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_Params');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_Params = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } */
    this.in;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParams');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithDefault_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithDefault } */
    this.out;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_Params');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_Params = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } */
    this.in;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParams');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoStructWithoutDefault_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.enumDefaultUnittest.mojom.StructWithExtensibleEnumWithoutDefault } */
    this.out;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_Params');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_Params = class {
  constructor() {
    /** @type { !Object } */
    this.in;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParams');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithDefault_ResponseParams = class {
  constructor() {
    /** @type { !Object } */
    this.out;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_Params');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_Params = class {
  constructor() {
    /** @type { !Object } */
    this.in;
  }
};

goog.provide('mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParams');

mojo.test.enumDefaultUnittest.mojom.TestInterface_EchoUnionWithoutDefault_ResponseParams = class {
  constructor() {
    /** @type { !Object } */
    this.out;
  }
};