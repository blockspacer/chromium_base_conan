// Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#include "basic/varint/varint.h" // IWYU pragma: associated
#include "basic/core/pointer_cast.h"

#include "basic/strings/substitute.h"
#include "base/strings/string_number_conversions.h"
#include "base/macros.h"
#include <base/numerics/safe_conversions.h>

#include <openssl/bn.h>
#include <openssl/err.h>

namespace basic {

void BigNumDeleter::operator()(BIGNUM* bn) const {
  if(bn) {
    BN_free(DCHECK_VALID_PTR_OR(bn));
  }
}

UBSAN_IGNORE_UNDEF
VarInt::VarInt(int64_t int64_val) : impl_(BN_new()) {
  DCHECK(impl_)
    << "BN_new failure: " << ERR_get_error()
    << " " << ERR_error_string(ERR_get_error(), nullptr);

  if (int64_val >= 0) {
    int ret = BN_set_word(impl_.get(), int64_val);
    DCHECK(ret)
      << "BN_set_word failure: " << ERR_get_error()
      << " " << ERR_error_string(ERR_get_error(), nullptr);
    DCHECK(BN_is_negative(impl_.get()) == 0)
      << "BN_is_negative failure: " << ERR_get_error()
      << " " << ERR_error_string(ERR_get_error(), nullptr);
  } else {
    int ret = BN_set_word(impl_.get(), -int64_val);
    DCHECK(ret)
      << "BN_set_word failure: " << ERR_get_error()
      << " " << ERR_error_string(ERR_get_error(), nullptr);
    BN_set_negative(impl_.get(), 1);
    DCHECK(BN_is_negative(impl_.get()) == 1)
      << "BN_is_negative failure: " << ERR_get_error()
      << " " << ERR_error_string(ERR_get_error(), nullptr);
  }
}

VarInt::VarInt() : impl_(BN_new()) {}

VarInt::VarInt(const VarInt& var_int)
  // BN_dup - copy BIGNUMs.
  // BN_dup() returns the new BIGNUM, and NULL on error.
  // The error codes can be obtained by ERR_get_error
  : impl_(BN_dup(var_int.impl_.get()))
  {
    DCHECK(impl_)
      << "BN_dup failure: " << ERR_get_error()
      << " " << ERR_error_string(ERR_get_error(), nullptr);
  }

VarInt& VarInt::operator=(const VarInt& rhs) {
  // BN_dup - copy BIGNUMs.
  // BN_dup() returns the new BIGNUM, and NULL on error.
  // The error codes can be obtained by ERR_get_error
  impl_.reset(BN_dup(rhs.impl_.get()));
  DCHECK(impl_)
    << "BN_dup failure: " << ERR_get_error()
    << " " << ERR_error_string(ERR_get_error(), nullptr);
  return *this;
}

std::string VarInt::ToString() const {
  if(!impl_) return "";

  char* temp = BN_bn2dec(impl_.get());
  DCHECK(temp)
    << "BN_bn2dec failure: " << ERR_get_error()
    << " " << ERR_error_string(ERR_get_error(), nullptr);
  if(temp) {
    std::string result(DCHECK_VALID_PTR_OR(temp));
    OPENSSL_free(temp);
    return result;
  }
  return "";
}

basic::StatusOr<int64_t> VarInt::ToInt64() const {
  using namespace ::basic::error;

  RETURN_ERROR_IF(!impl_, INVALID_ARGUMENT)
    << basic::Substitute("VarInt $1 cannot be converted"
                        " to int64 due to invalid stored pointer", *this);

  DCHECK_VALID_PTR(impl_.get());

#if DCHECK_IS_ON()
  // Validates for overflow, invalid chars etc.
  // because BN_* may have Undefined Behavior (tested in openssl_1_1_1)
  // with values -99999999999999999999999 and 99999999999999999999999
  int64_t expected_output;
  const bool expected_without_overflow
    = base::StringToInt64(ToString(), &expected_output);

  // RETURN_ERROR_IF(!expected_without_overflow, INVALID_ARGUMENT)
  //   << basic::Substitute("VarInt $1 cannot be converted to int64"
  //                       " due to numeric range", *this);
#endif // DCHECK_IS_ON()

  // BN_ULONG is a macro that will be an unsigned integral type
  // optimied for the most efficient implementation on the local platform.
  BN_ULONG value
    // BN_get_word () returns the value a,
    // or a number with all bits set if a cannot be represented as a BN_ULONG.
    // If a BIGNUM is equal to the value of all-bits-set,
    // it will collide with the error condition returned by BN_get_word()
    // which uses that as an error value.
    = BN_get_word(impl_.get());

  const bool negative = BN_is_negative(impl_.get());

  int64_t detected_output = negative ? -value : value;

  // If `checked_cast` fails, then BN_ULONG is not big enough to store int64_t
  // (platform dependent).
  const BN_ULONG max
    = ::base::checked_cast<BN_ULONG>(std::numeric_limits<int64_t>::max());

  // Note that BN_ULONG usually unsigned long and int64_t is long,
  // so it can not hold negative values i.e. int64_t::min()
  // We need to cast it without checked_cast.
  // The conversion is valid and well-defined.
  const BN_ULONG min
    = static_cast<BN_ULONG>(std::numeric_limits<int64_t>::min());

  // On my platform (ubuntu 64bit)
  // min is 9223372036854775808u and max is 9223372036854775807u
  // Note that they differ by 1 because if the value is negative,
  // then UINT_MAX + 1 is added to it so that the value
  // is a valid unsigned quantity.
  // (Technically, 2N is added to it, where N is the number of bits used
  // to represent the unsigned type.)
  const BN_ULONG limit
    = negative ? min : max;

  const bool has_overflow = value > limit;

#if DCHECK_IS_ON()
  CHECK_EQ(expected_without_overflow, !has_overflow)
    << basic::Substitute("VarInt $1 has wrong overflow check. "
                        "Because limit is $2."
                        , *this, limit);
#endif // DCHECK_IS_ON()

  RETURN_ERROR_IF(has_overflow, INVALID_ARGUMENT)
    << basic::Substitute("VarInt $1 cannot be converted"
                        " to int64 due to overflow", *this);

#if DCHECK_IS_ON()
  CHECK_EQ(expected_output, detected_output)
    << basic::Substitute("VarInt $1 has wrong value after type conversions. "
                        "Detected output $2, but expected $3."
                        , *this,  detected_output, expected_output);
#endif // DCHECK_IS_ON()

  return {RVALUE_CAST(detected_output)};
}

basic::Status VarInt::FromString(const char* cstr) {
  using namespace ::basic::error;

  const auto cstr_len = strlen(cstr);

  if (*DCHECK_VALID_PTR_OR(cstr) == '+') {
    ++cstr;
  }
  BIGNUM* temp = nullptr;
  int parsed = BN_dec2bn(&temp, cstr);
  impl_.reset(temp);
  RETURN_ERROR_IF(parsed == 0 || parsed != cstr_len, INVALID_ARGUMENT)
    << basic::Substitute("Cannot parse varint: $1", cstr);
  RETURN_OK();
}

int VarInt::CompareTo(const VarInt& other) const {
  return BN_cmp(DCHECK_VALID_PTR_OR(impl_.get()), DCHECK_VALID_PTR_OR(other.impl_.get()));
}

template <class T>
void FlipBits(T* data, size_t count) {
  for (auto end = data + count; data != end; ++data) {
    *data = ~*data;
  }
}

constexpr auto kWordSize = sizeof(uint8_t);
constexpr auto kBitsPerWord = 8 * kWordSize;

std::string VarInt::EncodeToComparable(size_t num_reserved_bits) const {
  // Actually we use EncodeToComparable with num_reserved_bits equals to 0 or 2, so don't have
  // to handle complex case when it wraps byte.
  DCHECK_LT(num_reserved_bits, 8);

  if (BN_is_zero(DCHECK_VALID_PTR_OR(impl_.get()))) {
    // Zero is encoded as positive value of length 0.
    return std::string(1, 0x80 >> num_reserved_bits);
  }

  auto num_bits = BN_num_bits(impl_.get());
  // The minimal number of bits that is required to encode this number:
  // sign bit, bits in value representation and reserved bits.
  size_t total_num_bits = num_bits + 1 + num_reserved_bits;

  // Number of groups of 7 becomes number of bytes, because of the unary size prefix.
  size_t num_bytes = (total_num_bits + 6) / 7;
  // If total_num_bits is not a multiple of seven, then the numerical part is prefixed with zeros.
  size_t rounding_padding = num_bytes * 7 - total_num_bits;
  // Header consists of sign bit, then number of ones that equals to num_bytes and padding zeroes.
  size_t header_length = 1 + num_bytes + rounding_padding;

  // Number of words required to encode this, i.e. header and bits in value rounded up to word size.
  auto words_count = (num_bits + header_length + kBitsPerWord - 1) / kBitsPerWord;
  // Offset of the first byte that would contain number representation.
  auto offset = words_count - (num_bits + kBitsPerWord - 1) / kBitsPerWord;
  std::string result(words_count, 0);
  if (offset > 0) {
    // This value could be merged with ones, so should cleanup it.
    result[offset - 1] = 0;
  }
  auto data = basic::pointer_cast<unsigned char*>(const_cast<char*>(result.data()));
  BN_bn2bin(impl_.get(), DCHECK_VALID_PTR_OR(data) + offset);
  size_t idx = 0;
  // Fill header with ones. We also fill reserved bits with ones for simplicity, then it will be
  // reset to zero.
  size_t num_ones = num_bytes + num_reserved_bits;
  // Fill complete bytes with ones.
  while (num_ones > 8) {
    data[idx] = 0xff;
    num_ones -= 8;
    ++idx;
  }
  // Merge last byte of header with possible first byte of number body.
  data[idx] |= 0xff ^ ((1 << (8 - num_ones)) - 1);
  // Negative number is inverted.
  if (BN_is_negative(impl_.get())) {
    FlipBits(data, result.size());
  }
  // Set reserved bits to 0.
  if (num_reserved_bits) {
    data[0] &= (1 << (8 - num_reserved_bits)) - 1;
  }

  return result;
}

basic::Status VarInt::DecodeFromComparable(const base::StringPiece& slice, size_t *num_decoded_bytes,
                                    size_t num_reserved_bits) {
  using namespace ::basic::error;

  DCHECK_LT(num_reserved_bits, 8);

  size_t len = slice.size();
  RETURN_ERROR_IF(len == 0, INVALID_ARGUMENT)
    << "Cannot decode varint from empty slice";
  bool negative = (slice[0] & (0x80 >> num_reserved_bits)) == 0;
  std::vector<uint8_t> buffer(slice.data(), slice.end());
  if (negative) {
    FlipBits(buffer.data(), buffer.size());
  }
  if (num_reserved_bits) {
    buffer[0] |= ~((1 << (8 - num_reserved_bits)) - 1);
  }
  size_t idx = 0;
  size_t num_ones = 0;
  while (buffer[idx] == 0xff) {
    ++idx;
    RETURN_ERROR_IF(idx >= len)
      << basic::Substitute("Encoded varint failure, no prefix termination: $1", base::HexEncode(slice.data(), slice.size()));
    num_ones += 8;
  }
  uint8_t temp = 0x80;
  while (buffer[idx] & temp) {
    buffer[idx] ^= temp;
    ++num_ones;
    temp >>= 1;
  }
  num_ones -= num_reserved_bits;
  RETURN_ERROR_IF(num_ones > len)
    << basic::Substitute("Not enough data in encoded varint: $1, $2",
         base::HexEncode(slice.data(), slice.size()), num_ones);
  *num_decoded_bytes = num_ones;
  impl_.reset(BN_bin2bn(buffer.data() + idx, num_ones - idx, nullptr /* ret */));
  if (negative) {
    BN_set_negative(DCHECK_VALID_PTR_OR(impl_.get()), 1);
  }

  RETURN_OK();
}

basic::Status VarInt::DecodeFromComparable(const base::StringPiece& slice) {
  size_t num_decoded_bytes;
  return DecodeFromComparable(slice, &num_decoded_bytes);
}

basic::Status VarInt::DecodeFromComparable(const std::string& str) {
  return DecodeFromComparable(base::StringPiece(str));
}

std::string VarInt::EncodeToTwosComplement() const {
  if (BN_is_zero(DCHECK_VALID_PTR_OR(impl_.get()))) {
    return std::string(1, 0);
  }
  size_t num_bits = BN_num_bits(impl_.get());
  size_t offset = num_bits % kBitsPerWord == 0 ? 1 : 0;
  size_t count = (num_bits + kBitsPerWord - 1) / kBitsPerWord + offset;
  std::string result(count, 0);
  auto data = basic::pointer_cast<unsigned char*>(const_cast<char*>(result.data()));
  if (offset) {
    *data = 0;
  }
  BN_bn2bin(impl_.get(), data + offset);
  if (BN_is_negative(impl_.get())) {
    FlipBits(data, result.size());
    unsigned char* back = data + result.size();
    while (--back >= data && *back == 0xff) {
      *back = 0;
    }
    ++*back;
    // The case when number has form of 10000000 00000000 ...
    // It is easier to detect it at this point, instead of doing preallocation check.
    if (offset == 1 && back > data && (data[1] & 0x80)) {
      result.erase(0, 1);
    }
  }
  return result;
}

basic::Status VarInt::DecodeFromTwosComplement(const std::string& input) {
  using namespace ::basic::error;

  RETURN_ERROR_IF(input.size() == 0, INVALID_ARGUMENT)
    << "Cannot decode varint from empty slice";

  bool negative = (input[0] & 0x80) != 0;
  if (!negative) {
    impl_.reset(BN_bin2bn(
        basic::pointer_cast<const unsigned char*>(input.data()), input.size(), nullptr /* ret */));
    RETURN_OK();
  }
  std::string copy(input);
  auto data = basic::pointer_cast<unsigned char*>(const_cast<char*>(copy.data()));
  unsigned char* back = data + copy.size();
  while (--back >= data && *back == 0x00) {
    *back = 0xff;
  }
  --*back;
  FlipBits(data, copy.size());
  impl_.reset(BN_bin2bn(data, input.size(), nullptr /* ret */));
  BN_set_negative(DCHECK_VALID_PTR_OR(impl_.get()), 1);

  RETURN_OK();
}

const VarInt& VarInt::Negate() {
  BN_set_negative(DCHECK_VALID_PTR_OR(impl_.get()), 1 - BN_is_negative(impl_.get()));
  return *this;
}

int VarInt::Sign() const {
  if (BN_is_zero(DCHECK_VALID_PTR_OR(impl_.get()))) {
    return 0;
  }
  return BN_is_negative(impl_.get()) ? -1 : 1;
}

std::ostream& operator<<(std::ostream& os, const VarInt& v) {
  os << v.ToString();
  return os;
}

VarInt operator+(const VarInt& lhs, const VarInt& rhs) {
  BigNumPtr temp(BN_new());
  DCHECK(temp)
    << "BN_new failure: " << ERR_get_error()
    << " " << ERR_error_string(ERR_get_error(), nullptr);
  CHECK(BN_add(temp.get(), DCHECK_VALID_PTR_OR(lhs.impl_.get()), DCHECK_VALID_PTR_OR(rhs.impl_.get())));
  return VarInt(std::move(temp));
}

VarInt operator-(const VarInt& lhs, const VarInt& rhs) {
  BigNumPtr temp(BN_new());
  DCHECK(temp)
    << "BN_new failure: " << ERR_get_error()
    << " " << ERR_error_string(ERR_get_error(), nullptr);
  CHECK(BN_sub(temp.get(), DCHECK_VALID_PTR_OR(lhs.impl_.get()), DCHECK_VALID_PTR_OR(rhs.impl_.get())));
  return VarInt(std::move(temp));
}

} // namespace basic
