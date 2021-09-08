// ipc/ipc.mojom.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

'use strict';

(function() {
  var mojomId = 'ipc/ipc.mojom';
  if (mojo.internal.isMojomLoaded(mojomId)) {
    console.warn('The following mojom is loaded multiple times: ' + mojomId);
    return;
  }
  mojo.internal.markMojomLoaded(mojomId);
  var bindings = mojo;
  var associatedBindings = mojo;
  var codec = mojo.internal;
  var validator = mojo.internal;

  var exports = mojo.internal.exposeNamespace('iPC.mojom');
  var native_struct$ =
      mojo.internal.exposeNamespace('mojo.native');
  if (mojo.config.autoLoadMojomDeps) {
    mojo.internal.loadMojomIfNecessary(
        'mojo/public/interfaces/bindings/native_struct.mojom', '../mojo/public/interfaces/bindings/native_struct.mojom.js');
  }



  function Message(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  Message.prototype.initDefaults_ = function() {
    this.bytes = null;
    this.handles = null;
  };
  Message.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  Message.validate = function(messageValidator, offset) {
    var err;
    err = messageValidator.validateStructHeader(offset, codec.kStructHeaderSize);
    if (err !== validator.validationError.NONE)
        return err;

    var kVersionSizes = [
      {version: 0, numBytes: 24}
    ];
    err = messageValidator.validateStructVersion(offset, kVersionSizes);
    if (err !== validator.validationError.NONE)
        return err;


    // validate Message.bytes
    err = messageValidator.validateArrayPointer(offset + codec.kStructHeaderSize + 0, 1, codec.Uint8, false, [0], 0);
    if (err !== validator.validationError.NONE)
        return err;


    // validate Message.handles
    err = messageValidator.validateArrayPointer(offset + codec.kStructHeaderSize + 8, 8, new codec.PointerTo(native_struct$.SerializedHandle), true, [0], 0);
    if (err !== validator.validationError.NONE)
        return err;

    return validator.validationError.NONE;
  };

  Message.encodedSize = codec.kStructHeaderSize + 16;

  Message.decode = function(decoder) {
    var packed;
    var val = new Message();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.bytes =
        decoder.decodeArrayPointer(codec.Uint8);
    val.handles =
        decoder.decodeArrayPointer(new codec.PointerTo(native_struct$.SerializedHandle));
    return val;
  };

  Message.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(Message.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeArrayPointer(codec.Uint8, val.bytes);
    encoder.encodeArrayPointer(new codec.PointerTo(native_struct$.SerializedHandle), val.handles);
  };
  function Channel_SetPeerPid_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  Channel_SetPeerPid_Params.prototype.initDefaults_ = function() {
    this.pid = 0;
  };
  Channel_SetPeerPid_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  Channel_SetPeerPid_Params.validate = function(messageValidator, offset) {
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

  Channel_SetPeerPid_Params.encodedSize = codec.kStructHeaderSize + 8;

  Channel_SetPeerPid_Params.decode = function(decoder) {
    var packed;
    var val = new Channel_SetPeerPid_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.pid =
        decoder.decodeStruct(codec.Int32);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    return val;
  };

  Channel_SetPeerPid_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(Channel_SetPeerPid_Params.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStruct(codec.Int32, val.pid);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
  };
  function Channel_Receive_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  Channel_Receive_Params.prototype.initDefaults_ = function() {
    this.message = null;
  };
  Channel_Receive_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  Channel_Receive_Params.validate = function(messageValidator, offset) {
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


    // validate Channel_Receive_Params.message
    err = messageValidator.validateStructPointer(offset + codec.kStructHeaderSize + 0, Message, false);
    if (err !== validator.validationError.NONE)
        return err;

    return validator.validationError.NONE;
  };

  Channel_Receive_Params.encodedSize = codec.kStructHeaderSize + 8;

  Channel_Receive_Params.decode = function(decoder) {
    var packed;
    var val = new Channel_Receive_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.message =
        decoder.decodeStructPointer(Message);
    return val;
  };

  Channel_Receive_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(Channel_Receive_Params.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStructPointer(Message, val.message);
  };
  function Channel_GetAssociatedInterface_Params(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  Channel_GetAssociatedInterface_Params.prototype.initDefaults_ = function() {
    this.name = null;
    this.receiver = new associatedBindings.AssociatedInterfaceRequest();
  };
  Channel_GetAssociatedInterface_Params.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  Channel_GetAssociatedInterface_Params.validate = function(messageValidator, offset) {
    var err;
    err = messageValidator.validateStructHeader(offset, codec.kStructHeaderSize);
    if (err !== validator.validationError.NONE)
        return err;

    var kVersionSizes = [
      {version: 0, numBytes: 24}
    ];
    err = messageValidator.validateStructVersion(offset, kVersionSizes);
    if (err !== validator.validationError.NONE)
        return err;


    // validate Channel_GetAssociatedInterface_Params.name
    err = messageValidator.validateStringPointer(offset + codec.kStructHeaderSize + 0, false)
    if (err !== validator.validationError.NONE)
        return err;


    // validate Channel_GetAssociatedInterface_Params.receiver
    err = messageValidator.validateAssociatedInterfaceRequest(offset + codec.kStructHeaderSize + 8, false)
    if (err !== validator.validationError.NONE)
        return err;

    return validator.validationError.NONE;
  };

  Channel_GetAssociatedInterface_Params.encodedSize = codec.kStructHeaderSize + 16;

  Channel_GetAssociatedInterface_Params.decode = function(decoder) {
    var packed;
    var val = new Channel_GetAssociatedInterface_Params();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    val.name =
        decoder.decodeStruct(codec.String);
    val.receiver =
        decoder.decodeStruct(codec.AssociatedInterfaceRequest);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    return val;
  };

  Channel_GetAssociatedInterface_Params.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(Channel_GetAssociatedInterface_Params.encodedSize);
    encoder.writeUint32(0);
    encoder.encodeStruct(codec.String, val.name);
    encoder.encodeStruct(codec.AssociatedInterfaceRequest, val.receiver);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
  };

  function GenericInterfacePtr(handleOrPtrInfo) {
    this.ptr = new bindings.InterfacePtrController(GenericInterface,
                                                   handleOrPtrInfo);
  }

  function GenericInterfaceAssociatedPtr(associatedInterfacePtrInfo) {
    this.ptr = new associatedBindings.AssociatedInterfacePtrController(
        GenericInterface, associatedInterfacePtrInfo);
  }

  GenericInterfaceAssociatedPtr.prototype =
      Object.create(GenericInterfacePtr.prototype);
  GenericInterfaceAssociatedPtr.prototype.constructor =
      GenericInterfaceAssociatedPtr;

  function GenericInterfaceProxy(receiver) {
    this.receiver_ = receiver;
  }

  function GenericInterfaceStub(delegate) {
    this.delegate_ = delegate;
  }

  GenericInterfaceStub.prototype.accept = function(message) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  GenericInterfaceStub.prototype.acceptWithResponder =
      function(message, responder) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  function validateGenericInterfaceRequest(messageValidator) {
    return validator.validationError.NONE;
  }

  function validateGenericInterfaceResponse(messageValidator) {
    return validator.validationError.NONE;
  }

  var GenericInterface = {
    name: 'IPC.mojom.GenericInterface',
    kVersion: 0,
    ptrClass: GenericInterfacePtr,
    proxyClass: GenericInterfaceProxy,
    stubClass: GenericInterfaceStub,
    validateRequest: validateGenericInterfaceRequest,
    validateResponse: null,
  };
  GenericInterfaceStub.prototype.validator = validateGenericInterfaceRequest;
  GenericInterfaceProxy.prototype.validator = null;
  var kChannel_SetPeerPid_Name = 1007272179;
  var kChannel_Receive_Name = 973219859;
  var kChannel_GetAssociatedInterface_Name = 810452750;

  function ChannelPtr(handleOrPtrInfo) {
    this.ptr = new bindings.InterfacePtrController(Channel,
                                                   handleOrPtrInfo);
  }

  function ChannelAssociatedPtr(associatedInterfacePtrInfo) {
    this.ptr = new associatedBindings.AssociatedInterfacePtrController(
        Channel, associatedInterfacePtrInfo);
  }

  ChannelAssociatedPtr.prototype =
      Object.create(ChannelPtr.prototype);
  ChannelAssociatedPtr.prototype.constructor =
      ChannelAssociatedPtr;

  function ChannelProxy(receiver) {
    this.receiver_ = receiver;
  }
  ChannelPtr.prototype.setPeerPid = function() {
    return ChannelProxy.prototype.setPeerPid
        .apply(this.ptr.getProxy(), arguments);
  };

  ChannelProxy.prototype.setPeerPid = function(pid) {
    var params_ = new Channel_SetPeerPid_Params();
    params_.pid = pid;
    var builder = new codec.MessageV0Builder(
        kChannel_SetPeerPid_Name,
        codec.align(Channel_SetPeerPid_Params.encodedSize));
    builder.encodeStruct(Channel_SetPeerPid_Params, params_);
    var message = builder.finish();
    this.receiver_.accept(message);
  };
  ChannelPtr.prototype.receive = function() {
    return ChannelProxy.prototype.receive
        .apply(this.ptr.getProxy(), arguments);
  };

  ChannelProxy.prototype.receive = function(message) {
    var params_ = new Channel_Receive_Params();
    params_.message = message;
    var builder = new codec.MessageV0Builder(
        kChannel_Receive_Name,
        codec.align(Channel_Receive_Params.encodedSize));
    builder.encodeStruct(Channel_Receive_Params, params_);
    var message = builder.finish();
    this.receiver_.accept(message);
  };
  ChannelPtr.prototype.getAssociatedInterface = function() {
    return ChannelProxy.prototype.getAssociatedInterface
        .apply(this.ptr.getProxy(), arguments);
  };

  ChannelProxy.prototype.getAssociatedInterface = function(name, receiver) {
    var params_ = new Channel_GetAssociatedInterface_Params();
    params_.name = name;
    params_.receiver = receiver;
    var builder = new codec.MessageV2Builder(
        kChannel_GetAssociatedInterface_Name,
        codec.align(Channel_GetAssociatedInterface_Params.encodedSize));
    builder.setPayload(Channel_GetAssociatedInterface_Params, params_);
    var message = builder.finish();
    this.receiver_.accept(message);
  };

  function ChannelStub(delegate) {
    this.delegate_ = delegate;
  }
  ChannelStub.prototype.setPeerPid = function(pid) {
    return this.delegate_ && this.delegate_.setPeerPid && this.delegate_.setPeerPid(pid);
  }
  ChannelStub.prototype.receive = function(message) {
    return this.delegate_ && this.delegate_.receive && this.delegate_.receive(message);
  }
  ChannelStub.prototype.getAssociatedInterface = function(name, receiver) {
    return this.delegate_ && this.delegate_.getAssociatedInterface && this.delegate_.getAssociatedInterface(name, receiver);
  }

  ChannelStub.prototype.accept = function(message) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    case kChannel_SetPeerPid_Name:
      var params = reader.decodeStruct(Channel_SetPeerPid_Params);
      this.setPeerPid(params.pid);
      return true;
    case kChannel_Receive_Name:
      var params = reader.decodeStruct(Channel_Receive_Params);
      this.receive(params.message);
      return true;
    case kChannel_GetAssociatedInterface_Name:
      var params = reader.decodeStruct(Channel_GetAssociatedInterface_Params);
      this.getAssociatedInterface(params.name, params.receiver);
      return true;
    default:
      return false;
    }
  };

  ChannelStub.prototype.acceptWithResponder =
      function(message, responder) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  function validateChannelRequest(messageValidator) {
    var message = messageValidator.message;
    var paramsClass = null;
    switch (message.getName()) {
      case kChannel_SetPeerPid_Name:
        if (!message.expectsResponse() && !message.isResponse())
          paramsClass = Channel_SetPeerPid_Params;
      break;
      case kChannel_Receive_Name:
        if (!message.expectsResponse() && !message.isResponse())
          paramsClass = Channel_Receive_Params;
      break;
      case kChannel_GetAssociatedInterface_Name:
        if (!message.expectsResponse() && !message.isResponse())
          paramsClass = Channel_GetAssociatedInterface_Params;
      break;
    }
    if (paramsClass === null)
      return validator.validationError.NONE;
    return paramsClass.validate(messageValidator, messageValidator.message.getHeaderNumBytes());
  }

  function validateChannelResponse(messageValidator) {
    return validator.validationError.NONE;
  }

  var Channel = {
    name: 'IPC.mojom.Channel',
    kVersion: 0,
    ptrClass: ChannelPtr,
    proxyClass: ChannelProxy,
    stubClass: ChannelStub,
    validateRequest: validateChannelRequest,
    validateResponse: null,
  };
  ChannelStub.prototype.validator = validateChannelRequest;
  ChannelProxy.prototype.validator = null;

  function ChannelBootstrapPtr(handleOrPtrInfo) {
    this.ptr = new bindings.InterfacePtrController(ChannelBootstrap,
                                                   handleOrPtrInfo);
  }

  function ChannelBootstrapAssociatedPtr(associatedInterfacePtrInfo) {
    this.ptr = new associatedBindings.AssociatedInterfacePtrController(
        ChannelBootstrap, associatedInterfacePtrInfo);
  }

  ChannelBootstrapAssociatedPtr.prototype =
      Object.create(ChannelBootstrapPtr.prototype);
  ChannelBootstrapAssociatedPtr.prototype.constructor =
      ChannelBootstrapAssociatedPtr;

  function ChannelBootstrapProxy(receiver) {
    this.receiver_ = receiver;
  }

  function ChannelBootstrapStub(delegate) {
    this.delegate_ = delegate;
  }

  ChannelBootstrapStub.prototype.accept = function(message) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  ChannelBootstrapStub.prototype.acceptWithResponder =
      function(message, responder) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  function validateChannelBootstrapRequest(messageValidator) {
    return validator.validationError.NONE;
  }

  function validateChannelBootstrapResponse(messageValidator) {
    return validator.validationError.NONE;
  }

  var ChannelBootstrap = {
    name: 'IPC.mojom.ChannelBootstrap',
    kVersion: 0,
    ptrClass: ChannelBootstrapPtr,
    proxyClass: ChannelBootstrapProxy,
    stubClass: ChannelBootstrapStub,
    validateRequest: validateChannelBootstrapRequest,
    validateResponse: null,
  };
  ChannelBootstrapStub.prototype.validator = validateChannelBootstrapRequest;
  ChannelBootstrapProxy.prototype.validator = null;
  exports.Message = Message;
  exports.GenericInterface = GenericInterface;
  exports.GenericInterfacePtr = GenericInterfacePtr;
  exports.GenericInterfaceAssociatedPtr = GenericInterfaceAssociatedPtr;
  exports.Channel = Channel;
  exports.ChannelPtr = ChannelPtr;
  exports.ChannelAssociatedPtr = ChannelAssociatedPtr;
  exports.ChannelBootstrap = ChannelBootstrap;
  exports.ChannelBootstrapPtr = ChannelBootstrapPtr;
  exports.ChannelBootstrapAssociatedPtr = ChannelBootstrapAssociatedPtr;
})();