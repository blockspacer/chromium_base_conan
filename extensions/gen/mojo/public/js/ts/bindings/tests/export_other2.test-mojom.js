// mojo/public/js/ts/bindings/tests/export_other2.test-mojom.js is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

'use strict';

(function() {
  var mojomId = 'mojo/public/js/ts/bindings/tests/export_other2.test-mojom';
  if (mojo.internal.isMojomLoaded(mojomId)) {
    console.warn('The following mojom is loaded multiple times: ' + mojomId);
    return;
  }
  mojo.internal.markMojomLoaded(mojomId);
  var bindings = mojo;
  var associatedBindings = mojo;
  var codec = mojo.internal;
  var validator = mojo.internal;

  var exports = mojo.internal.exposeNamespace('mojo.tstest.exportedOther');


  var TWO = 2;

  function ExportedStructTwo(values) {
    this.initDefaults_();
    this.initFields_(values);
  }


  ExportedStructTwo.prototype.initDefaults_ = function() {
    this.value = false;
  };
  ExportedStructTwo.prototype.initFields_ = function(fields) {
    for(var field in fields) {
        if (this.hasOwnProperty(field))
          this[field] = fields[field];
    }
  };

  ExportedStructTwo.validate = function(messageValidator, offset) {
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

  ExportedStructTwo.encodedSize = codec.kStructHeaderSize + 8;

  ExportedStructTwo.decode = function(decoder) {
    var packed;
    var val = new ExportedStructTwo();
    var numberOfBytes = decoder.readUint32();
    var version = decoder.readUint32();
    packed = decoder.readUint8();
    val.value = (packed >> 0) & 1 ? true : false;
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    decoder.skip(1);
    return val;
  };

  ExportedStructTwo.encode = function(encoder, val) {
    var packed;
    encoder.writeUint32(ExportedStructTwo.encodedSize);
    encoder.writeUint32(0);
    packed = 0;
    packed |= (val.value & 1) << 0
    encoder.writeUint8(packed);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
    encoder.skip(1);
  };
  exports.TWO = TWO;
  exports.ExportedStructTwo = ExportedStructTwo;
})();