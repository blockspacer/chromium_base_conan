// mojo/public/cpp/bindings/tests/extra_cpp_template_unittest.test-mojom.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

'use strict';

(function() {
  var mojomId = 'mojo/public/cpp/bindings/tests/extra_cpp_template_unittest.test-mojom';
  if (mojo.internal.isMojomLoaded(mojomId)) {
    console.warn('The following mojom is loaded multiple times: ' + mojomId);
    return;
  }
  mojo.internal.markMojomLoaded(mojomId);
  var bindings = mojo;
  var associatedBindings = mojo;
  var codec = mojo.internal;
  var validator = mojo.internal;

  var exports = mojo.internal.exposeNamespace('mojo.test.extraCppTemplateUnittest.mojom');




  function ExtraCppInterfacePtr(handleOrPtrInfo) {
    this.ptr = new bindings.InterfacePtrController(ExtraCppInterface,
                                                   handleOrPtrInfo);
  }

  function ExtraCppInterfaceAssociatedPtr(associatedInterfacePtrInfo) {
    this.ptr = new associatedBindings.AssociatedInterfacePtrController(
        ExtraCppInterface, associatedInterfacePtrInfo);
  }

  ExtraCppInterfaceAssociatedPtr.prototype =
      Object.create(ExtraCppInterfacePtr.prototype);
  ExtraCppInterfaceAssociatedPtr.prototype.constructor =
      ExtraCppInterfaceAssociatedPtr;

  function ExtraCppInterfaceProxy(receiver) {
    this.receiver_ = receiver;
  }

  function ExtraCppInterfaceStub(delegate) {
    this.delegate_ = delegate;
  }

  ExtraCppInterfaceStub.prototype.accept = function(message) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  ExtraCppInterfaceStub.prototype.acceptWithResponder =
      function(message, responder) {
    var reader = new codec.MessageReader(message);
    switch (reader.messageName) {
    default:
      return false;
    }
  };

  function validateExtraCppInterfaceRequest(messageValidator) {
    return validator.validationError.NONE;
  }

  function validateExtraCppInterfaceResponse(messageValidator) {
    return validator.validationError.NONE;
  }

  var ExtraCppInterface = {
    name: 'mojo.test.extra_cpp_template_unittest.mojom.ExtraCppInterface',
    kVersion: 0,
    ptrClass: ExtraCppInterfacePtr,
    proxyClass: ExtraCppInterfaceProxy,
    stubClass: ExtraCppInterfaceStub,
    validateRequest: validateExtraCppInterfaceRequest,
    validateResponse: null,
  };
  ExtraCppInterfaceStub.prototype.validator = validateExtraCppInterfaceRequest;
  ExtraCppInterfaceProxy.prototype.validator = null;
  exports.ExtraCppInterface = ExtraCppInterface;
  exports.ExtraCppInterfacePtr = ExtraCppInterfacePtr;
  exports.ExtraCppInterfaceAssociatedPtr = ExtraCppInterfaceAssociatedPtr;
})();