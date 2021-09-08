// mojo/public/interfaces/bindings/tests/struct_with_traits.mojom.externs.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



/** @enum {number} */
mojo.test.EnumWithTraits = {};
mojo.test.EnumWithTraits.VALUE_0;
mojo.test.EnumWithTraits.VALUE_1;
goog.provide('mojo.test.TraitsTestService');
goog.provide('mojo.test.TraitsTestServiceImpl');
goog.provide('mojo.test.TraitsTestServicePtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.TraitsTestService;

/** @interface */
mojo.test.TraitsTestServiceImpl = class {
  /**
   * @param { !mojo.test.StructWithTraits } s
   * @return {Promise}
   */
  echoStructWithTraits(s) {}
  /**
   * @param { !mojo.test.TrivialStructWithTraits } s
   * @return {Promise}
   */
  echoTrivialStructWithTraits(s) {}
  /**
   * @param { !mojo.test.MoveOnlyStructWithTraits } s
   * @return {Promise}
   */
  echoMoveOnlyStructWithTraits(s) {}
  /**
   * @param { mojo.test.MoveOnlyStructWithTraits } s
   * @return {Promise}
   */
  echoNullableMoveOnlyStructWithTraits(s) {}
  /**
   * @param { !mojo.test.EnumWithTraits } e
   * @return {Promise}
   */
  echoEnumWithTraits(e) {}
  /**
   * @param { !mojo.test.StructWithTraitsForUniquePtr } e
   * @return {Promise}
   */
  echoStructWithTraitsForUniquePtr(e) {}
  /**
   * @param { mojo.test.StructWithTraitsForUniquePtr } e
   * @return {Promise}
   */
  echoNullableStructWithTraitsForUniquePtr(e) {}
  /**
   * @param { !Object } u
   * @return {Promise}
   */
  echoUnionWithTraits(u) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.TraitsTestServiceImpl }
 */
mojo.test.TraitsTestServicePtr = class {
  /**
   * @param { !mojo.test.StructWithTraits } s
   * @return {Promise}
   */
  echoStructWithTraits(s) {}
  /**
   * @param { !mojo.test.TrivialStructWithTraits } s
   * @return {Promise}
   */
  echoTrivialStructWithTraits(s) {}
  /**
   * @param { !mojo.test.MoveOnlyStructWithTraits } s
   * @return {Promise}
   */
  echoMoveOnlyStructWithTraits(s) {}
  /**
   * @param { mojo.test.MoveOnlyStructWithTraits } s
   * @return {Promise}
   */
  echoNullableMoveOnlyStructWithTraits(s) {}
  /**
   * @param { !mojo.test.EnumWithTraits } e
   * @return {Promise}
   */
  echoEnumWithTraits(e) {}
  /**
   * @param { !mojo.test.StructWithTraitsForUniquePtr } e
   * @return {Promise}
   */
  echoStructWithTraitsForUniquePtr(e) {}
  /**
   * @param { mojo.test.StructWithTraitsForUniquePtr } e
   * @return {Promise}
   */
  echoNullableStructWithTraitsForUniquePtr(e) {}
  /**
   * @param { !Object } u
   * @return {Promise}
   */
  echoUnionWithTraits(u) {}
};

goog.provide('mojo.test.TestUnserializedStruct');
goog.provide('mojo.test.TestUnserializedStructImpl');
goog.provide('mojo.test.TestUnserializedStructPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.TestUnserializedStruct;

/** @interface */
mojo.test.TestUnserializedStructImpl = class {
  /**
   * @param { !mojo.test.StructWithUnreachableTraits } s
   * @return {Promise}
   */
  passUnserializedStruct(s) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.TestUnserializedStructImpl }
 */
mojo.test.TestUnserializedStructPtr = class {
  /**
   * @param { !mojo.test.StructWithUnreachableTraits } s
   * @return {Promise}
   */
  passUnserializedStruct(s) {}
};

goog.provide('mojo.test.ForceSerializeTester');
goog.provide('mojo.test.ForceSerializeTesterImpl');
goog.provide('mojo.test.ForceSerializeTesterPtr');



/**
 * @const
 * @type { !mojo.Interface };
 */
mojo.test.ForceSerializeTester;

/** @interface */
mojo.test.ForceSerializeTesterImpl = class {
  /**
   * @param { !mojo.test.StructForceSerialize } s
   * @return {Promise}
   */
  sendForceSerializedStruct(s) {}
  /**
   * @param { !mojo.test.StructNestedForceSerialize } s
   * @return {Promise}
   */
  sendNestedForceSerializedStruct(s) {}
};

/**
 * @implements { mojo.InterfacePtr }
 * @implements { mojo.test.ForceSerializeTesterImpl }
 */
mojo.test.ForceSerializeTesterPtr = class {
  /**
   * @param { !mojo.test.StructForceSerialize } s
   * @return {Promise}
   */
  sendForceSerializedStruct(s) {}
  /**
   * @param { !mojo.test.StructNestedForceSerialize } s
   * @return {Promise}
   */
  sendNestedForceSerializedStruct(s) {}
};

goog.provide('mojo.test.NestedStructWithTraits');

mojo.test.NestedStructWithTraits = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.StructWithTraits');

mojo.test.StructWithTraits = class {
  constructor() {
    /** @type { !mojo.test.EnumWithTraits } */
    this.fEnum;
    /** @type { !boolean } */
    this.fBool;
    /** @type { !number } */
    this.fUint32;
    /** @type { !number } */
    this.fUint64;
    /** @type { !string } */
    this.fString;
    /** @type { !string } */
    this.fString2;
    /** @type { !Array<string> } */
    this.fStringArray;
    /** @type { !Array<string> } */
    this.fStringSet;
    /** @type { !mojo.test.NestedStructWithTraits } */
    this.fStruct;
    /** @type { !Array<mojo.test.NestedStructWithTraits> } */
    this.fStructArray;
    /** @type { !Map<string, mojo.test.NestedStructWithTraits> } */
    this.fStructMap;
  }
};

goog.provide('mojo.test.StructWithUnreachableTraits');

mojo.test.StructWithUnreachableTraits = class {
  constructor() {
    /** @type { !boolean } */
    this.ignoreMe;
  }
};

goog.provide('mojo.test.StructWithTraitsContainer');

mojo.test.StructWithTraitsContainer = class {
  constructor() {
    /** @type { !mojo.test.StructWithTraits } */
    this.fStruct;
  }
};

goog.provide('mojo.test.TrivialStructWithTraits');

mojo.test.TrivialStructWithTraits = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.MoveOnlyStructWithTraits');

mojo.test.MoveOnlyStructWithTraits = class {
  constructor() {
    /** @type { !MojoHandle } */
    this.fHandle;
  }
};

goog.provide('mojo.test.MoveOnlyStructWithTraitsContainer');

mojo.test.MoveOnlyStructWithTraitsContainer = class {
  constructor() {
    /** @type { !mojo.test.MoveOnlyStructWithTraits } */
    this.fStruct;
  }
};

goog.provide('mojo.test.StructWithTraitsForUniquePtr');

mojo.test.StructWithTraitsForUniquePtr = class {
  constructor() {
    /** @type { !number } */
    this.fInt32;
  }
};

goog.provide('mojo.test.EnumWithTraitsContainer');

mojo.test.EnumWithTraitsContainer = class {
  constructor() {
    /** @type { !mojo.test.EnumWithTraits } */
    this.fField;
  }
};

goog.provide('mojo.test.StructForceSerialize');

mojo.test.StructForceSerialize = class {
  constructor() {
    /** @type { !number } */
    this.value;
  }
};

goog.provide('mojo.test.StructNestedForceSerialize');

mojo.test.StructNestedForceSerialize = class {
  constructor() {
    /** @type { !mojo.test.StructForceSerialize } */
    this.force;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoStructWithTraits_Params');

mojo.test.TraitsTestService_EchoStructWithTraits_Params = class {
  constructor() {
    /** @type { !mojo.test.StructWithTraits } */
    this.s;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoStructWithTraits_ResponseParams');

mojo.test.TraitsTestService_EchoStructWithTraits_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.StructWithTraits } */
    this.passed;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoTrivialStructWithTraits_Params');

mojo.test.TraitsTestService_EchoTrivialStructWithTraits_Params = class {
  constructor() {
    /** @type { !mojo.test.TrivialStructWithTraits } */
    this.s;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoTrivialStructWithTraits_ResponseParams');

mojo.test.TraitsTestService_EchoTrivialStructWithTraits_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.TrivialStructWithTraits } */
    this.passed;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoMoveOnlyStructWithTraits_Params');

mojo.test.TraitsTestService_EchoMoveOnlyStructWithTraits_Params = class {
  constructor() {
    /** @type { !mojo.test.MoveOnlyStructWithTraits } */
    this.s;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoMoveOnlyStructWithTraits_ResponseParams');

mojo.test.TraitsTestService_EchoMoveOnlyStructWithTraits_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.MoveOnlyStructWithTraits } */
    this.passed;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoNullableMoveOnlyStructWithTraits_Params');

mojo.test.TraitsTestService_EchoNullableMoveOnlyStructWithTraits_Params = class {
  constructor() {
    /** @type { mojo.test.MoveOnlyStructWithTraits } */
    this.s;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoNullableMoveOnlyStructWithTraits_ResponseParams');

mojo.test.TraitsTestService_EchoNullableMoveOnlyStructWithTraits_ResponseParams = class {
  constructor() {
    /** @type { mojo.test.MoveOnlyStructWithTraits } */
    this.passed;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoEnumWithTraits_Params');

mojo.test.TraitsTestService_EchoEnumWithTraits_Params = class {
  constructor() {
    /** @type { !mojo.test.EnumWithTraits } */
    this.e;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoEnumWithTraits_ResponseParams');

mojo.test.TraitsTestService_EchoEnumWithTraits_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.EnumWithTraits } */
    this.passed;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoStructWithTraitsForUniquePtr_Params');

mojo.test.TraitsTestService_EchoStructWithTraitsForUniquePtr_Params = class {
  constructor() {
    /** @type { !mojo.test.StructWithTraitsForUniquePtr } */
    this.e;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoStructWithTraitsForUniquePtr_ResponseParams');

mojo.test.TraitsTestService_EchoStructWithTraitsForUniquePtr_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.StructWithTraitsForUniquePtr } */
    this.passed;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoNullableStructWithTraitsForUniquePtr_Params');

mojo.test.TraitsTestService_EchoNullableStructWithTraitsForUniquePtr_Params = class {
  constructor() {
    /** @type { mojo.test.StructWithTraitsForUniquePtr } */
    this.e;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoNullableStructWithTraitsForUniquePtr_ResponseParams');

mojo.test.TraitsTestService_EchoNullableStructWithTraitsForUniquePtr_ResponseParams = class {
  constructor() {
    /** @type { mojo.test.StructWithTraitsForUniquePtr } */
    this.passed;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoUnionWithTraits_Params');

mojo.test.TraitsTestService_EchoUnionWithTraits_Params = class {
  constructor() {
    /** @type { !Object } */
    this.u;
  }
};

goog.provide('mojo.test.TraitsTestService_EchoUnionWithTraits_ResponseParams');

mojo.test.TraitsTestService_EchoUnionWithTraits_ResponseParams = class {
  constructor() {
    /** @type { !Object } */
    this.passed;
  }
};

goog.provide('mojo.test.TestUnserializedStruct_PassUnserializedStruct_Params');

mojo.test.TestUnserializedStruct_PassUnserializedStruct_Params = class {
  constructor() {
    /** @type { !mojo.test.StructWithUnreachableTraits } */
    this.s;
  }
};

goog.provide('mojo.test.TestUnserializedStruct_PassUnserializedStruct_ResponseParams');

mojo.test.TestUnserializedStruct_PassUnserializedStruct_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.StructWithUnreachableTraits } */
    this.passed;
  }
};

goog.provide('mojo.test.ForceSerializeTester_SendForceSerializedStruct_Params');

mojo.test.ForceSerializeTester_SendForceSerializedStruct_Params = class {
  constructor() {
    /** @type { !mojo.test.StructForceSerialize } */
    this.s;
  }
};

goog.provide('mojo.test.ForceSerializeTester_SendForceSerializedStruct_ResponseParams');

mojo.test.ForceSerializeTester_SendForceSerializedStruct_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.StructForceSerialize } */
    this.passed;
  }
};

goog.provide('mojo.test.ForceSerializeTester_SendNestedForceSerializedStruct_Params');

mojo.test.ForceSerializeTester_SendNestedForceSerializedStruct_Params = class {
  constructor() {
    /** @type { !mojo.test.StructNestedForceSerialize } */
    this.s;
  }
};

goog.provide('mojo.test.ForceSerializeTester_SendNestedForceSerializedStruct_ResponseParams');

mojo.test.ForceSerializeTester_SendNestedForceSerializedStruct_ResponseParams = class {
  constructor() {
    /** @type { !mojo.test.StructNestedForceSerialize } */
    this.passed;
  }
};