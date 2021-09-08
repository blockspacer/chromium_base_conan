// mojo/public/interfaces/bindings/tests/sample_import.mojom.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

'use strict';

(function() {
  var mojomId = 'mojo/public/interfaces/bindings/tests/sample_import.mojom';
  if (mojo.internal.isMojomLoaded(mojomId)) {
    console.warn('The following mojom is loaded multiple times: ' + mojomId);
    return;
  }
  mojo.internal.markMojomLoaded(mojomId);
  var bindings = mojo;
  var associatedBindings = mojo;
  var codec = mojo.internal;
  var validator = mojo.internal;

  var exports = mojo.internal.exposeNamespace('imported');


  var Shape = {};
  Shape.RECTANGLE = 1;
  Shape.CIRCLE = 2;
  Shape.TRIANGLE = 3;
  Shape.LAST = 3;
  Shape.MIN_VALUE = 1;
  Shape.MAX_VALUE = 3;

  Shape.isKnownEnumValue = function(value) {
    switch (value) {
    case 1:
    case 2:
    case 3:
      return true;
    }
    return false;
  };

  Shape.toKnownEnumValue = function(value) {
    return value;
  };

  Shape.validate = function(enumValue) {
    const isExtensible = false;
    if (isExtensible || this.isKnownEnumValue(enumValue))
      return validator.validationError.NONE;

    return validator.validationError.UNKNOWN_ENUM_VALUE;
  };
  var AnotherShape = {};
  AnotherShape.RECTANGLE = 10;
  AnotherShape.CIRCLE = 11;
  AnotherShape.TRIANGLE = 12;
  AnotherShape.MIN_VALUE = 10;
  AnotherShape.MAX_VALUE = 12;

  AnotherShape.isKnownEnumValue = function(value) {
    switch (value) {
    case 10:
    case 11:
    case 12:
      return true;
    }
    return false;
  };

  AnotherShape.toKnownEnumValue = function(value) {
    return value;
  };

  AnotherShape.validate = function(enumValue) {
    const isExtensible = false;
    if (isExtensible || this.isKnownEnumValue(enumValue))
      return validator.validationError.NONE;

    return validator.validationError.UNKNOWN_ENUM_VALUE;
  };
  var YetAnotherShape = {};
  YetAnotherShape.RECTANGLE = 20;
  YetAnotherShape.CIRCLE = 21;
  YetAnotherShape.TRIANGLE = 22;
  YetAnotherShape.MIN_VALUE = 20;
  YetAnotherShape.MAX_VALUE = 22;

  YetAnotherShape.isKnownEnumValue = function(value) {
    switch (value) {
    case 20:
    case 21:
    case 22:
      return true;
    }
    return false;
  };

  YetAnotherShape.toKnownEnumValue = function(value) {
    return value;
  };

  YetAnotherShape.validate = function(enumValue) {
    const isExtensible = false;
    if (isExtensible || this.isKnownEnumValue(enumValue))
      return validator.validationError.NONE;

    return validator.validationError.UNKNOWN_ENUM_VALUE;
  };

  function Point(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  Point.prototype.initDefaults_ = function() {
    this.x = 0;
    this.y = 0;
  };
  Point.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  Point.validate = function(messageValidator, offset) {
    var err;
    err = messageValidator.validateStructHeader(offset, codec.kStructHeaderSize);
    if (err !== validator.validationError.NONE)
        return err;

    var kVersionSizes = [
      {version: 0, numBytes: 16}
    ];
    err = messageValidator.validateStructVersion(offset, kVersionSizes);
    if (err !== validator.validationError.NONE)
        return err;



    return validator.validationError.NONE;
  };

  Point.encodedSize = codec.kStructHeaderSize + 8;

  Point.decode = function(decoder) {
    var packed;
    var val = new Point();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.x =
        decoder.decodeStruct(codec.Int32);
    val.y =
        decoder.decodeStruct(codec.Int32);
    return val;
  };

  Point.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(Point.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStruct(codec.Int32, val.x);
    encoder.encodeStruct(codec.Int32, val.y);
  };
  function ImportedInterface_DoSomething_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  ImportedInterface_DoSomething_Params.prototype.initDefaults_ = function() {
  };
  ImportedInterface_DoSomething_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  ImportedInterface_DoSomething_Params.validate = function(messageValidator, offset) {
    var err;
    err = messageValidator.validateStructHeader(offset, codec.kStructHeaderSize);
    if (err !== validator.validationError.NONE)
        return err;

    var kVersionSizes = [
      {version: 0, numBytes: 8}
    ];
    err = messageValidator.validateStructVersion(offset, kVersionSizes);
    if (err !== validator.validationError.NONE)
        return err;

    return validator.validationError.NONE;
  };

  ImportedInterface_DoSomething_Params.encodedSize = codec.kStructHeaderSize + 0;

  ImportedInterface_DoSomething_Params.decode = function(decoder) {
    var packed;
    var val = new ImportedInterface_DoSomething_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    return val;
  };

  ImportedInterface_DoSomething_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(ImportedInterface_DoSomething_Params.encodedSize);
    encoder.writeUint32(0);
  };

  function PointOrShape(value) {
    this.initDefault_();
    this.initValue_(value);
  }


  PointOrShape.Tags = {
    point: 0,
    shape: 1,
  };

  PointOrShape.prototype.initDefault_ = function() {
    this.$data = null;
    this.$tag = undefined;
  }

  PointOrShape.prototype.initValue_ = function(value) {
    if (value == undefined) {
      return;
    }

    var keys = Object.keys(value);
    if (keys.length == 0) {
      return;
    }

    if (keys.length > 1) {
      throw new TypeError("You may set only one member on a union.");
    }

    var fields = [
        "point",
        "shape",
    ];

    if (fields.indexOf(keys[0]) < 0) {
      throw new ReferenceError(keys[0] + " is not a PointOrShape member.");

    }

    this[keys[0]] = value[keys[0]];
  }
  Object.defineProperty(PointOrShape.prototype, "point", {
    get: function() {
      if (this.$tag != PointOrShape.Tags.point) {
        throw new ReferenceError(
            "PointOrShape.point is not currently set.");
      }
      return this.$data;
    },

    set: function(value) {
      this.$tag = PointOrShape.Tags.point;
      this.$data = value;
    }
  });
  Object.defineProperty(PointOrShape.prototype, "shape", {
    get: function() {
      if (this.$tag != PointOrShape.Tags.shape) {
        throw new ReferenceError(
            "PointOrShape.shape is not currently set.");
      }
      return this.$data;
    },

    set: function(value) {
      this.$tag = PointOrShape.Tags.shape;
      this.$data = value;
    }
  });


    PointOrShape.encode = function(encoder, val) {
      if (val == null) {
        encoder.writeUint64(0);
        encoder.writeUint64(0);
        return;
      }
      if (val.$tag == undefined) {
        throw new TypeError("Cannot encode unions with an unknown member set.");
      }

      encoder.writeUint32(16);
      encoder.writeUint32(val.$tag);
      switch (val.$tag) {
        case PointOrShape.Tags.point:
          encoder.encodeStructPointer(Point, val.point);
          break;
        case PointOrShape.Tags.shape:
          encoder.encodeStruct(codec.Int32, val.shape);
          break;
      }
      encoder.align();
    };


    PointOrShape.decode = function(decoder) {
      var size = decoder.readUint32();
      if (size == 0) {
        decoder.readUint32();
        decoder.readUint64();
        return null;
      }

      var result = new PointOrShape();
      var tag = decoder.readUint32();
      switch (tag) {
        case PointOrShape.Tags.point:
          result.point = decoder.decodeStructPointer(Point);
          break;
        case PointOrShape.Tags.shape:
          result.shape = decoder.decodeStruct(new codec.Enum(Shape));
          break;
      }
      decoder.align();

      return result;
    };


    PointOrShape.validate = function(messageValidator, offset) {
      var size = messageValidator.decodeUnionSize(offset);
      if (size != 16) {
        return validator.validationError.INVALID_UNION_SIZE;
      }

      var tag = messageValidator.decodeUnionTag(offset);
      var data_offset = offset + 8;
      var err;
      switch (tag) {
        case PointOrShape.Tags.point:
          

    // validate PointOrShape.point
    err = messageValidator.validateStructPointer(data_offset, Point, false);
    if (err !== validator.validationError.NONE)
        return err;
          break;
        case PointOrShape.Tags.shape:
          

    // validate PointOrShape.shape
    err = messageValidator.validateEnum(data_offset, Shape);
    if (err !== validator.validationError.NONE)
        return err;
          break;
      }

      return validator.validationError.NONE;
    };

  PointOrShape.encodedSize = 16;
  var kImportedInterface_DoSomething_Name = 912963854;

  function ImportedInterfacePtr(handleOrPtrInfo) {
    this.ptr = new bindings.InterfacePtrController(ImportedInterface,
                                                   handleOrPtrInfo);
  }

  function ImportedInterfaceAssociatedPtr(associatedInterfacePtrInfo) {
    this.ptr = new associatedBindings.AssociatedInterfacePtrController(
        ImportedInterface, associatedInterfacePtrInfo);
  }

  ImportedInterfaceAssociatedPtr.prototype =
      Object.create(ImportedInterfacePtr.prototype);
  ImportedInterfaceAssociatedPtr.prototype.constructor =
      ImportedInterfaceAssociatedPtr;

  function ImportedInterfaceProxy(receiver) {
    this.receiver_ = receiver;
  }
  ImportedInterfacePtr.prototype.doSomething = function() {
    return ImportedInterfaceProxy.prototype.doSomething
        .apply(this.ptr.getProxy(), arguments);
  };

  ImportedInterfaceProxy.prototype.doSomething = function() {
    var params_ = new ImportedInterface_DoSomething_Params();
    var builder = new codec.MessageV0Builder(
        kImportedInterface_DoSomething_Name,
        codec.align(ImportedInterface_DoSomething_Params.encodedSize));
    builder.encodeStruct(ImportedInterface_DoSomething_Params, params_);
    var message = builder.finish();
    this.receiver_.accept(message);
  };

  function ImportedInterfaceStub(delegate) {
    this.delegate_ = delegate;
  }
  ImportedInterfaceStub.prototype.doSomething = function() {
    return this.delegate_ && this.delegate_.doSomething && this.delegate_.doSomething();
  }

  ImportedInterfaceStub.prototype.accept = function(message) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    case kImportedInterface_DoSomething_Name:
      var params = reader.decodeStruct(ImportedInterface_DoSomething_Params);
      this.doSomething();
      return true;
    default:
      return false;
    }
  };

  ImportedInterfaceStub.prototype.acceptWithResponder =
      function(message, responder) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  function validateImportedInterfaceRequest(messageValidator) {
    var message = messageValidator.message;
    var paramsClass = null;
    switch (message.getName()) {
      case kImportedInterface_DoSomething_Name:
        if (!message.expectsResponse() && !message.isResponse())
          paramsClass = ImportedInterface_DoSomething_Params;
      break;
    }
    if (paramsClass === null)
      return validator.validationError.NONE;
    return paramsClass.validate(messageValidator, messageValidator.message.getHeaderNumBytes());
  }

  function validateImportedInterfaceResponse(messageValidator) {
    return validator.validationError.NONE;
  }

  var ImportedInterface = {
    name: 'imported.ImportedInterface',
    kVersion: 0,
    ptrClass: ImportedInterfacePtr,
    proxyClass: ImportedInterfaceProxy,
    stubClass: ImportedInterfaceStub,
    validateRequest: validateImportedInterfaceRequest,
    validateResponse: null,
  };
  ImportedInterfaceStub.prototype.validator = validateImportedInterfaceRequest;
  ImportedInterfaceProxy.prototype.validator = null;
  exports.Shape = Shape;
  exports.AnotherShape = AnotherShape;
  exports.YetAnotherShape = YetAnotherShape;
  exports.Point = Point;
  exports.PointOrShape = PointOrShape;
  exports.ImportedInterface = ImportedInterface;
  exports.ImportedInterfacePtr = ImportedInterfacePtr;
  exports.ImportedInterfaceAssociatedPtr = ImportedInterfaceAssociatedPtr;
})();