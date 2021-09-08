// mojo/public/cpp/bindings/tests/remote_unittest.test-mojom.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

'use strict';

(function() {
  var mojomId = 'mojo/public/cpp/bindings/tests/remote_unittest.test-mojom';
  if (mojo.internal.isMojomLoaded(mojomId)) {
    console.warn('The following mojom is loaded multiple times: ' + mojomId);
    return;
  }
  mojo.internal.markMojomLoaded(mojomId);
  var bindings = mojo;
  var associatedBindings = mojo;
  var codec = mojo.internal;
  var validator = mojo.internal;

  var exports = mojo.internal.exposeNamespace('mojo.test.remoteUnittest.mojom');



  function SharedRemoteSyncTest_Fetch_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  SharedRemoteSyncTest_Fetch_Params.prototype.initDefaults_ = function() {
  };
  SharedRemoteSyncTest_Fetch_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  SharedRemoteSyncTest_Fetch_Params.validate = function(messageValidator, offset) {
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

  SharedRemoteSyncTest_Fetch_Params.encodedSize = codec.kStructHeaderSize + 0;

  SharedRemoteSyncTest_Fetch_Params.decode = function(decoder) {
    var packed;
    var val = new SharedRemoteSyncTest_Fetch_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    return val;
  };

  SharedRemoteSyncTest_Fetch_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(SharedRemoteSyncTest_Fetch_Params.encodedSize);
    encoder.writeUint32(0);
  };
  function SharedRemoteSyncTest_Fetch_ResponseParams(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  SharedRemoteSyncTest_Fetch_ResponseParams.prototype.initDefaults_ = function() {
    this.value = 0;
  };
  SharedRemoteSyncTest_Fetch_ResponseParams.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  SharedRemoteSyncTest_Fetch_ResponseParams.validate = function(messageValidator, offset) {
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

  SharedRemoteSyncTest_Fetch_ResponseParams.encodedSize = codec.kStructHeaderSize + 8;

  SharedRemoteSyncTest_Fetch_ResponseParams.decode = function(decoder) {
    var packed;
    var val = new SharedRemoteSyncTest_Fetch_ResponseParams();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.value =
        decoder.decodeStruct(codec.Int32);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    return val;
  };

  SharedRemoteSyncTest_Fetch_ResponseParams.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(SharedRemoteSyncTest_Fetch_ResponseParams.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStruct(codec.Int32, val.value);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
  };
  function LargeMessageTest_ProcessData_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  LargeMessageTest_ProcessData_Params.prototype.initDefaults_ = function() {
    this.data = null;
  };
  LargeMessageTest_ProcessData_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  LargeMessageTest_ProcessData_Params.validate = function(messageValidator, offset) {
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


    // validate LargeMessageTest_ProcessData_Params.data
    err = messageValidator.validateArrayPointer(offset + codec.kStructHeaderSize + 0, 1, codec.Uint8, false, [0], 0);
    if (err !== validator.validationError.NONE)
        return err;

    return validator.validationError.NONE;
  };

  LargeMessageTest_ProcessData_Params.encodedSize = codec.kStructHeaderSize + 8;

  LargeMessageTest_ProcessData_Params.decode = function(decoder) {
    var packed;
    var val = new LargeMessageTest_ProcessData_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.data =
        decoder.decodeArrayPointer(codec.Uint8);
    return val;
  };

  LargeMessageTest_ProcessData_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(LargeMessageTest_ProcessData_Params.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeArrayPointer(codec.Uint8, val.data);
  };
  function LargeMessageTest_ProcessData_ResponseParams(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  LargeMessageTest_ProcessData_ResponseParams.prototype.initDefaults_ = function() {
    this.dataSize = 0;
  };
  LargeMessageTest_ProcessData_ResponseParams.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  LargeMessageTest_ProcessData_ResponseParams.validate = function(messageValidator, offset) {
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

  LargeMessageTest_ProcessData_ResponseParams.encodedSize = codec.kStructHeaderSize + 8;

  LargeMessageTest_ProcessData_ResponseParams.decode = function(decoder) {
    var packed;
    var val = new LargeMessageTest_ProcessData_ResponseParams();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.dataSize =
        decoder.decodeStruct(codec.Uint64);
    return val;
  };

  LargeMessageTest_ProcessData_ResponseParams.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(LargeMessageTest_ProcessData_ResponseParams.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStruct(codec.Uint64, val.dataSize);
  };
  function LargeMessageTest_ProcessLotsOfData_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  LargeMessageTest_ProcessLotsOfData_Params.prototype.initDefaults_ = function() {
    this.data = null;
  };
  LargeMessageTest_ProcessLotsOfData_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  LargeMessageTest_ProcessLotsOfData_Params.validate = function(messageValidator, offset) {
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


    // validate LargeMessageTest_ProcessLotsOfData_Params.data
    err = messageValidator.validateArrayPointer(offset + codec.kStructHeaderSize + 0, 1, codec.Uint8, false, [0], 0);
    if (err !== validator.validationError.NONE)
        return err;

    return validator.validationError.NONE;
  };

  LargeMessageTest_ProcessLotsOfData_Params.encodedSize = codec.kStructHeaderSize + 8;

  LargeMessageTest_ProcessLotsOfData_Params.decode = function(decoder) {
    var packed;
    var val = new LargeMessageTest_ProcessLotsOfData_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.data =
        decoder.decodeArrayPointer(codec.Uint8);
    return val;
  };

  LargeMessageTest_ProcessLotsOfData_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(LargeMessageTest_ProcessLotsOfData_Params.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeArrayPointer(codec.Uint8, val.data);
  };
  function LargeMessageTest_ProcessLotsOfData_ResponseParams(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  LargeMessageTest_ProcessLotsOfData_ResponseParams.prototype.initDefaults_ = function() {
    this.dataSize = 0;
  };
  LargeMessageTest_ProcessLotsOfData_ResponseParams.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  LargeMessageTest_ProcessLotsOfData_ResponseParams.validate = function(messageValidator, offset) {
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

  LargeMessageTest_ProcessLotsOfData_ResponseParams.encodedSize = codec.kStructHeaderSize + 8;

  LargeMessageTest_ProcessLotsOfData_ResponseParams.decode = function(decoder) {
    var packed;
    var val = new LargeMessageTest_ProcessLotsOfData_ResponseParams();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.dataSize =
        decoder.decodeStruct(codec.Uint64);
    return val;
  };

  LargeMessageTest_ProcessLotsOfData_ResponseParams.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(LargeMessageTest_ProcessLotsOfData_ResponseParams.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStruct(codec.Uint64, val.dataSize);
  };
  function LargeMessageTest_GetLotsOfData_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  LargeMessageTest_GetLotsOfData_Params.prototype.initDefaults_ = function() {
    this.dataSize = 0;
  };
  LargeMessageTest_GetLotsOfData_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  LargeMessageTest_GetLotsOfData_Params.validate = function(messageValidator, offset) {
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

  LargeMessageTest_GetLotsOfData_Params.encodedSize = codec.kStructHeaderSize + 8;

  LargeMessageTest_GetLotsOfData_Params.decode = function(decoder) {
    var packed;
    var val = new LargeMessageTest_GetLotsOfData_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.dataSize =
        decoder.decodeStruct(codec.Uint64);
    return val;
  };

  LargeMessageTest_GetLotsOfData_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(LargeMessageTest_GetLotsOfData_Params.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStruct(codec.Uint64, val.dataSize);
  };
  function LargeMessageTest_GetLotsOfData_ResponseParams(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  LargeMessageTest_GetLotsOfData_ResponseParams.prototype.initDefaults_ = function() {
    this.data = null;
  };
  LargeMessageTest_GetLotsOfData_ResponseParams.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  LargeMessageTest_GetLotsOfData_ResponseParams.validate = function(messageValidator, offset) {
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


    // validate LargeMessageTest_GetLotsOfData_ResponseParams.data
    err = messageValidator.validateArrayPointer(offset + codec.kStructHeaderSize + 0, 1, codec.Uint8, false, [0], 0);
    if (err !== validator.validationError.NONE)
        return err;

    return validator.validationError.NONE;
  };

  LargeMessageTest_GetLotsOfData_ResponseParams.encodedSize = codec.kStructHeaderSize + 8;

  LargeMessageTest_GetLotsOfData_ResponseParams.decode = function(decoder) {
    var packed;
    var val = new LargeMessageTest_GetLotsOfData_ResponseParams();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.data =
        decoder.decodeArrayPointer(codec.Uint8);
    return val;
  };

  LargeMessageTest_GetLotsOfData_ResponseParams.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(LargeMessageTest_GetLotsOfData_ResponseParams.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeArrayPointer(codec.Uint8, val.data);
  };
  var kSharedRemoteSyncTest_Fetch_Name = 1284435712;

  function SharedRemoteSyncTestPtr(handleOrPtrInfo) {
    this.ptr = new bindings.InterfacePtrController(SharedRemoteSyncTest,
                                                   handleOrPtrInfo);
  }

  function SharedRemoteSyncTestAssociatedPtr(associatedInterfacePtrInfo) {
    this.ptr = new associatedBindings.AssociatedInterfacePtrController(
        SharedRemoteSyncTest, associatedInterfacePtrInfo);
  }

  SharedRemoteSyncTestAssociatedPtr.prototype =
      Object.create(SharedRemoteSyncTestPtr.prototype);
  SharedRemoteSyncTestAssociatedPtr.prototype.constructor =
      SharedRemoteSyncTestAssociatedPtr;

  function SharedRemoteSyncTestProxy(receiver) {
    this.receiver_ = receiver;
  }
  SharedRemoteSyncTestPtr.prototype.fetch = function() {
    return SharedRemoteSyncTestProxy.prototype.fetch
        .apply(this.ptr.getProxy(), arguments);
  };

  SharedRemoteSyncTestProxy.prototype.fetch = function() {
    var params_ = new SharedRemoteSyncTest_Fetch_Params();
    return new Promise(function(resolve, reject) {
      var builder = new codec.MessageV1Builder(
          kSharedRemoteSyncTest_Fetch_Name,
          codec.align(SharedRemoteSyncTest_Fetch_Params.encodedSize),
          codec.kMessageExpectsResponse, 0);
      builder.encodeStruct(SharedRemoteSyncTest_Fetch_Params, params_);
      var message = builder.finish();
      this.receiver_.acceptAndExpectResponse(message).then(function(message) {
        var reader = new codec.MessageReader(message);
        var responseParams =
            reader.decodeStruct(SharedRemoteSyncTest_Fetch_ResponseParams);
        resolve(responseParams);
      }).catch(function(result) {
        reject(Error("Connection error: " + result));
      });
    }.bind(this));
  };

  function SharedRemoteSyncTestStub(delegate) {
    this.delegate_ = delegate;
  }
  SharedRemoteSyncTestStub.prototype.fetch = function() {
    return this.delegate_ && this.delegate_.fetch && this.delegate_.fetch();
  }

  SharedRemoteSyncTestStub.prototype.accept = function(message) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  SharedRemoteSyncTestStub.prototype.acceptWithResponder =
      function(message, responder) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    case kSharedRemoteSyncTest_Fetch_Name:
      var params = reader.decodeStruct(SharedRemoteSyncTest_Fetch_Params);
      this.fetch().then(function(response) {
        var responseParams =
            new SharedRemoteSyncTest_Fetch_ResponseParams();
        responseParams.value = response.value;
        var builder = new codec.MessageV1Builder(
            kSharedRemoteSyncTest_Fetch_Name,
            codec.align(SharedRemoteSyncTest_Fetch_ResponseParams.encodedSize),
            codec.kMessageIsResponse, reader.requestID);
        builder.encodeStruct(SharedRemoteSyncTest_Fetch_ResponseParams,
                             responseParams);
        var message = builder.finish();
        responder.accept(message);
      });
      return true;
    default:
      return false;
    }
  };

  function validateSharedRemoteSyncTestRequest(messageValidator) {
    var message = messageValidator.message;
    var paramsClass = null;
    switch (message.getName()) {
      case kSharedRemoteSyncTest_Fetch_Name:
        if (message.expectsResponse())
          paramsClass = SharedRemoteSyncTest_Fetch_Params;
      break;
    }
    if (paramsClass === null)
      return validator.validationError.NONE;
    return paramsClass.validate(messageValidator, messageValidator.message.getHeaderNumBytes());
  }

  function validateSharedRemoteSyncTestResponse(messageValidator) {
   var message = messageValidator.message;
   var paramsClass = null;
   switch (message.getName()) {
      case kSharedRemoteSyncTest_Fetch_Name:
        if (message.isResponse())
          paramsClass = SharedRemoteSyncTest_Fetch_ResponseParams;
        break;
    }
    if (paramsClass === null)
      return validator.validationError.NONE;
    return paramsClass.validate(messageValidator, messageValidator.message.getHeaderNumBytes());
  }

  var SharedRemoteSyncTest = {
    name: 'mojo.test.remote_unittest.mojom.SharedRemoteSyncTest',
    kVersion: 0,
    ptrClass: SharedRemoteSyncTestPtr,
    proxyClass: SharedRemoteSyncTestProxy,
    stubClass: SharedRemoteSyncTestStub,
    validateRequest: validateSharedRemoteSyncTestRequest,
    validateResponse: validateSharedRemoteSyncTestResponse,
  };
  SharedRemoteSyncTestStub.prototype.validator = validateSharedRemoteSyncTestRequest;
  SharedRemoteSyncTestProxy.prototype.validator = validateSharedRemoteSyncTestResponse;
  var kLargeMessageTest_ProcessData_Name = 1798604899;
  var kLargeMessageTest_ProcessLotsOfData_Name = 938167658;
  var kLargeMessageTest_GetLotsOfData_Name = 1545831854;

  function LargeMessageTestPtr(handleOrPtrInfo) {
    this.ptr = new bindings.InterfacePtrController(LargeMessageTest,
                                                   handleOrPtrInfo);
  }

  function LargeMessageTestAssociatedPtr(associatedInterfacePtrInfo) {
    this.ptr = new associatedBindings.AssociatedInterfacePtrController(
        LargeMessageTest, associatedInterfacePtrInfo);
  }

  LargeMessageTestAssociatedPtr.prototype =
      Object.create(LargeMessageTestPtr.prototype);
  LargeMessageTestAssociatedPtr.prototype.constructor =
      LargeMessageTestAssociatedPtr;

  function LargeMessageTestProxy(receiver) {
    this.receiver_ = receiver;
  }
  LargeMessageTestPtr.prototype.processData = function() {
    return LargeMessageTestProxy.prototype.processData
        .apply(this.ptr.getProxy(), arguments);
  };

  LargeMessageTestProxy.prototype.processData = function(data) {
    var params_ = new LargeMessageTest_ProcessData_Params();
    params_.data = data;
    return new Promise(function(resolve, reject) {
      var builder = new codec.MessageV1Builder(
          kLargeMessageTest_ProcessData_Name,
          codec.align(LargeMessageTest_ProcessData_Params.encodedSize),
          codec.kMessageExpectsResponse, 0);
      builder.encodeStruct(LargeMessageTest_ProcessData_Params, params_);
      var message = builder.finish();
      this.receiver_.acceptAndExpectResponse(message).then(function(message) {
        var reader = new codec.MessageReader(message);
        var responseParams =
            reader.decodeStruct(LargeMessageTest_ProcessData_ResponseParams);
        resolve(responseParams);
      }).catch(function(result) {
        reject(Error("Connection error: " + result));
      });
    }.bind(this));
  };
  LargeMessageTestPtr.prototype.processLotsOfData = function() {
    return LargeMessageTestProxy.prototype.processLotsOfData
        .apply(this.ptr.getProxy(), arguments);
  };

  LargeMessageTestProxy.prototype.processLotsOfData = function(data) {
    var params_ = new LargeMessageTest_ProcessLotsOfData_Params();
    params_.data = data;
    return new Promise(function(resolve, reject) {
      var builder = new codec.MessageV1Builder(
          kLargeMessageTest_ProcessLotsOfData_Name,
          codec.align(LargeMessageTest_ProcessLotsOfData_Params.encodedSize),
          codec.kMessageExpectsResponse, 0);
      builder.encodeStruct(LargeMessageTest_ProcessLotsOfData_Params, params_);
      var message = builder.finish();
      this.receiver_.acceptAndExpectResponse(message).then(function(message) {
        var reader = new codec.MessageReader(message);
        var responseParams =
            reader.decodeStruct(LargeMessageTest_ProcessLotsOfData_ResponseParams);
        resolve(responseParams);
      }).catch(function(result) {
        reject(Error("Connection error: " + result));
      });
    }.bind(this));
  };
  LargeMessageTestPtr.prototype.getLotsOfData = function() {
    return LargeMessageTestProxy.prototype.getLotsOfData
        .apply(this.ptr.getProxy(), arguments);
  };

  LargeMessageTestProxy.prototype.getLotsOfData = function(dataSize) {
    var params_ = new LargeMessageTest_GetLotsOfData_Params();
    params_.dataSize = dataSize;
    return new Promise(function(resolve, reject) {
      var builder = new codec.MessageV1Builder(
          kLargeMessageTest_GetLotsOfData_Name,
          codec.align(LargeMessageTest_GetLotsOfData_Params.encodedSize),
          codec.kMessageExpectsResponse, 0);
      builder.encodeStruct(LargeMessageTest_GetLotsOfData_Params, params_);
      var message = builder.finish();
      this.receiver_.acceptAndExpectResponse(message).then(function(message) {
        var reader = new codec.MessageReader(message);
        var responseParams =
            reader.decodeStruct(LargeMessageTest_GetLotsOfData_ResponseParams);
        resolve(responseParams);
      }).catch(function(result) {
        reject(Error("Connection error: " + result));
      });
    }.bind(this));
  };

  function LargeMessageTestStub(delegate) {
    this.delegate_ = delegate;
  }
  LargeMessageTestStub.prototype.processData = function(data) {
    return this.delegate_ && this.delegate_.processData && this.delegate_.processData(data);
  }
  LargeMessageTestStub.prototype.processLotsOfData = function(data) {
    return this.delegate_ && this.delegate_.processLotsOfData && this.delegate_.processLotsOfData(data);
  }
  LargeMessageTestStub.prototype.getLotsOfData = function(dataSize) {
    return this.delegate_ && this.delegate_.getLotsOfData && this.delegate_.getLotsOfData(dataSize);
  }

  LargeMessageTestStub.prototype.accept = function(message) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  LargeMessageTestStub.prototype.acceptWithResponder =
      function(message, responder) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    case kLargeMessageTest_ProcessData_Name:
      var params = reader.decodeStruct(LargeMessageTest_ProcessData_Params);
      this.processData(params.data).then(function(response) {
        var responseParams =
            new LargeMessageTest_ProcessData_ResponseParams();
        responseParams.dataSize = response.dataSize;
        var builder = new codec.MessageV1Builder(
            kLargeMessageTest_ProcessData_Name,
            codec.align(LargeMessageTest_ProcessData_ResponseParams.encodedSize),
            codec.kMessageIsResponse, reader.requestID);
        builder.encodeStruct(LargeMessageTest_ProcessData_ResponseParams,
                             responseParams);
        var message = builder.finish();
        responder.accept(message);
      });
      return true;
    case kLargeMessageTest_ProcessLotsOfData_Name:
      var params = reader.decodeStruct(LargeMessageTest_ProcessLotsOfData_Params);
      this.processLotsOfData(params.data).then(function(response) {
        var responseParams =
            new LargeMessageTest_ProcessLotsOfData_ResponseParams();
        responseParams.dataSize = response.dataSize;
        var builder = new codec.MessageV1Builder(
            kLargeMessageTest_ProcessLotsOfData_Name,
            codec.align(LargeMessageTest_ProcessLotsOfData_ResponseParams.encodedSize),
            codec.kMessageIsResponse, reader.requestID);
        builder.encodeStruct(LargeMessageTest_ProcessLotsOfData_ResponseParams,
                             responseParams);
        var message = builder.finish();
        responder.accept(message);
      });
      return true;
    case kLargeMessageTest_GetLotsOfData_Name:
      var params = reader.decodeStruct(LargeMessageTest_GetLotsOfData_Params);
      this.getLotsOfData(params.dataSize).then(function(response) {
        var responseParams =
            new LargeMessageTest_GetLotsOfData_ResponseParams();
        responseParams.data = response.data;
        var builder = new codec.MessageV1Builder(
            kLargeMessageTest_GetLotsOfData_Name,
            codec.align(LargeMessageTest_GetLotsOfData_ResponseParams.encodedSize),
            codec.kMessageIsResponse, reader.requestID);
        builder.encodeStruct(LargeMessageTest_GetLotsOfData_ResponseParams,
                             responseParams);
        var message = builder.finish();
        responder.accept(message);
      });
      return true;
    default:
      return false;
    }
  };

  function validateLargeMessageTestRequest(messageValidator) {
    var message = messageValidator.message;
    var paramsClass = null;
    switch (message.getName()) {
      case kLargeMessageTest_ProcessData_Name:
        if (message.expectsResponse())
          paramsClass = LargeMessageTest_ProcessData_Params;
      break;
      case kLargeMessageTest_ProcessLotsOfData_Name:
        if (message.expectsResponse())
          paramsClass = LargeMessageTest_ProcessLotsOfData_Params;
      break;
      case kLargeMessageTest_GetLotsOfData_Name:
        if (message.expectsResponse())
          paramsClass = LargeMessageTest_GetLotsOfData_Params;
      break;
    }
    if (paramsClass === null)
      return validator.validationError.NONE;
    return paramsClass.validate(messageValidator, messageValidator.message.getHeaderNumBytes());
  }

  function validateLargeMessageTestResponse(messageValidator) {
   var message = messageValidator.message;
   var paramsClass = null;
   switch (message.getName()) {
      case kLargeMessageTest_ProcessData_Name:
        if (message.isResponse())
          paramsClass = LargeMessageTest_ProcessData_ResponseParams;
        break;
      case kLargeMessageTest_ProcessLotsOfData_Name:
        if (message.isResponse())
          paramsClass = LargeMessageTest_ProcessLotsOfData_ResponseParams;
        break;
      case kLargeMessageTest_GetLotsOfData_Name:
        if (message.isResponse())
          paramsClass = LargeMessageTest_GetLotsOfData_ResponseParams;
        break;
    }
    if (paramsClass === null)
      return validator.validationError.NONE;
    return paramsClass.validate(messageValidator, messageValidator.message.getHeaderNumBytes());
  }

  var LargeMessageTest = {
    name: 'mojo.test.remote_unittest.mojom.LargeMessageTest',
    kVersion: 0,
    ptrClass: LargeMessageTestPtr,
    proxyClass: LargeMessageTestProxy,
    stubClass: LargeMessageTestStub,
    validateRequest: validateLargeMessageTestRequest,
    validateResponse: validateLargeMessageTestResponse,
  };
  LargeMessageTestStub.prototype.validator = validateLargeMessageTestRequest;
  LargeMessageTestProxy.prototype.validator = validateLargeMessageTestResponse;
  exports.SharedRemoteSyncTest = SharedRemoteSyncTest;
  exports.SharedRemoteSyncTestPtr = SharedRemoteSyncTestPtr;
  exports.SharedRemoteSyncTestAssociatedPtr = SharedRemoteSyncTestAssociatedPtr;
  exports.LargeMessageTest = LargeMessageTest;
  exports.LargeMessageTestPtr = LargeMessageTestPtr;
  exports.LargeMessageTestAssociatedPtr = LargeMessageTestAssociatedPtr;
})();