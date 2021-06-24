#pragma once

#include <string>

#include "base/base_export.h"
#include "base/containers/span.h"
#include "base/strings/string_piece.h"

namespace base {

// Uses RFC-4648 standard
// Uses only characters 'A'-'Z' + '2'-'7' and some padding character.
/// \note you can use '\0' to strip padding entirely
bool BASE_EXPORT Base32Encode(const void* input,
  uint32_t inputLength, char* output,
  uint32_t outputSize, char paddingChar = '=');

// Encodes the input string in base32.
BASE_EXPORT void Base32Encode(const StringPiece& input, std::string* output);

}  // namespace base
