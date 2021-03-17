#pragma once

#include "base/strings/string_number_conversions.h"

namespace basic {

BASE_EXPORT bool StringToInt32(base::StringPiece input, int32_t* output);
BASE_EXPORT bool StringToUint32(base::StringPiece input, uint32_t* output);

// Return a std::string of binary data represented by the hex string |input|.
// For example, HexDecode("48656c6c6f20776f726c6421") == "Hello world!"
// This is the inverse function of base::HexEncode().
BASE_EXPORT std::string HexDecode(base::StringPiece input);

// Return a std::string containing hex and ASCII representations of the binary
// buffer |input|, with offsets at the beginning of each line, in the style of
// hexdump.  Non-printable characters will be shown as '.' in the ASCII output.
// Example output:
// "0x0000:  0090 69bd 5400 000d 610f 0189 0800 4500  ..i.T...a.....E.\n"
// "0x0010:  001c fb98 4000 4001 7e18 d8ef 2301 455d  ....@.@.~...#.E]\n"
// "0x0020:  7fe2 0800 6bcb 0bc6 806e                 ....k....n\n"
BASE_EXPORT std::string HexDump(base::StringPiece input);

inline std::string IntToString(int value) {
  return base::NumberToString(value);
}
inline base::string16 IntToString16(int value) {
  return base::NumberToString16(value);
}
inline std::string UintToString(unsigned value) {
  return base::NumberToString(value);
}
inline base::string16 UintToString16(unsigned value) {
  return base::NumberToString16(value);
}
inline std::string Int32ToString(int32_t value) {
  return base::NumberToString(value);
}
inline std::string Uint64ToString(int64_t value) {
  return base::NumberToString(value);
}
inline std::string Int64ToString(int64_t value) {
  return base::NumberToString(value);
}
inline base::string16 Int64ToString16(int64_t value) {
  return base::NumberToString16(value);
}

}  // namespace basic
