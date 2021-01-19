// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_BASE64_H_
#define BASE_BASE64_H_

#include <string>

#include "base/base_export.h"
#include "base/strings/string_piece.h"

// Base64 encoding: turning binary data into ASCII text
// for the purpose of saving it to text files like XML,
// or transmitting it over protocols like HTTP,
// or embedding it into web page files, and many other purposed.
// That’s the basic idea behind it.
// For every 3 bytes of input you get 4 bytes of output,
// so it’s not crazy inflated.
//
// BEFORE
//
// "Man is distinguished, not only by his reason, but by this singular passion from other animals, "
// "which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable "
// "generation of knowledge, exceeds the short vehemence of any carnal pleasure."
//
// AFTER
//
// "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"
// "IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
// "dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"
// "dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
// "ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4="
//
namespace base {

// Encodes the input string in base64. The encoding can be done in-place.
BASE_EXPORT void Base64Encode(const StringPiece& input, std::string* output);

// Decodes the base64 input string.  Returns true if successful and false
// otherwise. The output string is only modified if successful. The decoding can
// be done in-place.
BASE_EXPORT bool Base64Decode(const StringPiece& input, std::string* output);

// Decodes the base64 input string. Returns true if successful and false
// otherwise.  The output vector is only modified if successful.
BASE_EXPORT bool Base64Decode(const StringPiece& input,
                              std::vector<uint8_t>* output);

}  // namespace base

#endif  // BASE_BASE64_H_
