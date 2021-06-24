#include "basic/algorithm/base32.h"

#include <basic/portability/portability.h>

#include <cstddef>
#include <climits>
#include <cstdint>
#include <cstring>

namespace base {

static constexpr uint32_t kEncodeBits = 5;
static constexpr uint32_t kByteSize = 8;
static constexpr char kStrEnd = '\0';

static inline uint32_t quickCeilDiv(uint32_t num, uint32_t div)
{
  return (num + (div - 1)) / div;
}

static inline uint8_t maxBase32OutputSize(const size_t len) {
  // Base32 allows to encode each 5 bits ( as 32 = 2^5 ) using single character.
  // It means that you need output buffer size for encoding:
  // dst_size = src_size * kByteSize / kEncodeBits
  return quickCeilDiv(len, kEncodeBits) * kByteSize + 1;
}

bool Base32Encode(const void* input, uint32_t inputSize, char* output,
  uint32_t outputSize, char paddingChar)
{
  static const char charTable[33] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

  // Output len should be >= 1 + ceil( inputSize / 5 ) * 8
  if (UNLIKELY(outputSize < maxBase32OutputSize(inputSize)))
  {
    return false;
  }

  const uint8_t* ptr = static_cast<const uint8_t*>(input);
  uint32_t sizeRemaining = inputSize;
  while (sizeRemaining >= kEncodeBits)
  {
    uint64_t packedBits = 0;
    uint32_t bitPos = kEncodeBits * kByteSize - kByteSize;
    for (uint32_t i = 0; i < kEncodeBits; ++i, bitPos -= kByteSize)
      packedBits += static_cast<uint64_t>(ptr[i]) << bitPos;

    for (uint32_t i = 0; i < kByteSize; ++i, packedBits <<= kEncodeBits)
      *output++ = charTable[static_cast<uint32_t>((packedBits >> (40 - kEncodeBits)) & 0x1Fu)];

    ptr += kEncodeBits;
    sizeRemaining -= kEncodeBits;
  }

  // Can only be (inputSize % kEncodeBits) bytes left, so <= 4 bytes.
  if (sizeRemaining > 0)
  {
    // Pack remaining bytes into 32-bit word for easy encoding.
    uint32_t remaining = 0;
    uint32_t bitPos = 32 - kByteSize;
    for (uint32_t i = 0; i < sizeRemaining; ++i, bitPos -= kByteSize)
      remaining += static_cast<uint32_t>(ptr[i]) << bitPos;

    uint32_t remainingSize = quickCeilDiv(sizeRemaining * kByteSize, (uint32_t)kEncodeBits);
    for (uint32_t i = 0; i < remainingSize; ++i, remaining <<= kEncodeBits)
      *output++ = charTable[remaining >> (32 - kEncodeBits)];

    uint32_t paddingSize = (uint32_t)kByteSize - remainingSize;
    if (paddingChar != kStrEnd)
      for (uint32_t i = 0; i < paddingSize; ++i)
        *output++ = paddingChar;
  }

  *output++ = kStrEnd;
  return true;
}

void Base32Encode(const StringPiece& input, std::string* output) {
  static const char kPaddingChar = '=';

  output->resize(maxBase32OutputSize(input.size()));

  const bool result = Base32Encode(reinterpret_cast<const char*>(input.data()), input.size(),
    reinterpret_cast<char*>(output->data()), output->size(), kPaddingChar);
  CHECK(result) << "Encode to base32 failed";

  // rtrim '\0'
  output->resize(strlen(reinterpret_cast<char*>(output->data())));
}

}  // namespace base
