// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <cstdint>

namespace basic {

// This is a POD form of uint128 which can be used for static variables which
// need to be operated on as uint128.
//
// USAGE
//
// #include <basic/numerics/integral_macros.hpp>
// const uint128_pod kuint128max = {static_cast<uint64_t>(LONGLONG(0xFFFFFFFFFFFFFFFF)),
//                                  static_cast<uint64_t>(LONGLONG(0xFFFFFFFFFFFFFFFF))};
//
struct uint128_pod {
    // Note: The ordering of fields is different than 'class uint128' but the
    // same as its 2-arg constructor.  This enables more obvious initialization
    // of static instances, which is the primary reason for this struct in the
    // first place.  This does not seem to defeat any optimizations wrt
    // operations involving this struct.
    uint64_t hi;
    uint64_t lo;
};

/// \note GCC and Clang (but not Microsoft VS) support __int128 only for 64-bit architectures.
/// \todo make interoperable with __int128 (if supported),
/// signed 128-bit integer types and overloads for std::numeric_limits,
/// type traits (aka std::is_integral<uint128>::value, std::is_arithmetic<uint128>::value)
/// like in abseil.io/docs/cpp/guides/numeric
/// i.e. chromium.googlesource.com/external/github.com/abseil/abseil-cpp/+/refs/heads/master/absl/numeric/int128.h
//
// An unsigned 128-bit integer type. Thread-compatible.
class Uint128 {
 public:
  constexpr Uint128();  // Sets to 0, but don't trust on this behavior.
  constexpr Uint128(uint64_t top, uint64_t bottom);
  Uint128(int bottom);
  constexpr Uint128(uint32_t bottom);  // Top 96 bits = 0
  constexpr Uint128(uint64_t bottom);  // hi_ = 0
  constexpr Uint128(const Uint128& val);
  Uint128(const uint128_pod& val);

  void Initialize(uint64_t top, uint64_t bottom);

  Uint128& operator=(const Uint128& b);

  // Arithmetic operators.
  // TODO: division, etc.
  Uint128& operator+=(const Uint128& b);
  Uint128& operator-=(const Uint128& b);
  Uint128& operator*=(const Uint128& b);
  Uint128 operator++(int);
  Uint128 operator--(int);
  Uint128& operator<<=(int);
  Uint128& operator>>=(int);
  Uint128& operator&=(const Uint128& b);
  Uint128& operator|=(const Uint128& b);
  Uint128& operator^=(const Uint128& b);
  Uint128& operator++();
  Uint128& operator--();

  friend uint64_t QuicUint128Low64Impl(const Uint128& v);
  friend uint64_t QuicUint128High64Impl(const Uint128& v);

 private:
  // Little-endian memory order optimizations can benefit from
  // having lo_ first, hi_ last.
  // See util/endian/endian.h and Load128/Store128 for storing a
  // Uint128.
  uint64_t lo_;
  uint64_t hi_;

  // Not implemented, just declared for catching automatic type conversions.
  Uint128(uint8_t);
  Uint128(uint16_t);
  Uint128(float v);
  Uint128(double v);
};

inline Uint128 MakeUint128(uint64_t top, uint64_t bottom) {
  return Uint128(top, bottom);
}

// Methods to access low and high pieces of 128-bit value.
// Defined externally from Uint128 to facilitate conversion
// to native 128-bit types when compilers support them.
inline uint64_t QuicUint128Low64Impl(const Uint128& v) {
  return v.lo_;
}
inline uint64_t QuicUint128High64Impl(const Uint128& v) {
  return v.hi_;
}

// --------------------------------------------------------------------------
//                      Implementation details follow
// --------------------------------------------------------------------------
inline bool operator==(const Uint128& lhs, const Uint128& rhs) {
  return (QuicUint128Low64Impl(lhs) == QuicUint128Low64Impl(rhs) &&
          QuicUint128High64Impl(lhs) == QuicUint128High64Impl(rhs));
}
#if __cplusplus <= 201703L
inline bool operator!=(const Uint128& lhs, const Uint128& rhs) {
  return !(lhs == rhs);
}
#endif
inline Uint128& Uint128::operator=(const Uint128& b) {
  lo_ = b.lo_;
  hi_ = b.hi_;
  return *this;
}

constexpr Uint128::Uint128() : lo_(0), hi_(0) {}
constexpr Uint128::Uint128(uint64_t top, uint64_t bottom)
    : lo_(bottom), hi_(top) {}
constexpr Uint128::Uint128(const Uint128& v)
    : lo_(v.lo_), hi_(v.hi_) {}
inline Uint128::Uint128(const uint128_pod& v)
    : lo_(v.lo), hi_(v.hi) {}
constexpr Uint128::Uint128(uint64_t bottom)
    : lo_(bottom), hi_(0) {}
constexpr Uint128::Uint128(uint32_t bottom)
    : lo_(bottom), hi_(0) {}
inline Uint128::Uint128(int bottom) : lo_(bottom), hi_(0) {
  if (bottom < 0) {
    --hi_;
  }
}
inline void Uint128::Initialize(uint64_t top, uint64_t bottom) {
  hi_ = top;
  lo_ = bottom;
}

// Comparison operators.

#define CMP128(op)                                                           \
  inline bool operator op(const Uint128& lhs,                        \
                          const Uint128& rhs) {                      \
    return (QuicUint128High64Impl(lhs) == QuicUint128High64Impl(rhs))        \
               ? (QuicUint128Low64Impl(lhs) op QuicUint128Low64Impl(rhs))    \
               : (QuicUint128High64Impl(lhs) op QuicUint128High64Impl(rhs)); \
  }

CMP128(<)
CMP128(>)
CMP128(>=)
CMP128(<=)

#undef CMP128

// Unary operators

inline Uint128 operator-(const Uint128& val) {
  const uint64_t hi_flip = ~QuicUint128High64Impl(val);
  const uint64_t lo_flip = ~QuicUint128Low64Impl(val);
  const uint64_t lo_add = lo_flip + 1;
  if (lo_add < lo_flip) {
    return Uint128(hi_flip + 1, lo_add);
  }
  return Uint128(hi_flip, lo_add);
}

inline bool operator!(const Uint128& val) {
  return !QuicUint128High64Impl(val) && !QuicUint128Low64Impl(val);
}

// Logical operators.

inline Uint128 operator~(const Uint128& val) {
  return Uint128(~QuicUint128High64Impl(val),
                         ~QuicUint128Low64Impl(val));
}

#define LOGIC128(op)                                               \
  inline Uint128 operator op(const Uint128& lhs,   \
                                     const Uint128& rhs) { \
    return Uint128(                                        \
        QuicUint128High64Impl(lhs) op QuicUint128High64Impl(rhs),  \
        QuicUint128Low64Impl(lhs) op QuicUint128Low64Impl(rhs));   \
  }

LOGIC128(|)
LOGIC128(&)
LOGIC128(^)

#undef LOGIC128

#define LOGICASSIGN128(op)                              \
  inline Uint128& Uint128::operator op( \
      const Uint128& other) {                   \
    hi_ op other.hi_;                                   \
    lo_ op other.lo_;                                   \
    return *this;                                       \
  }

LOGICASSIGN128(|=)
LOGICASSIGN128(&=)
LOGICASSIGN128(^=)

#undef LOGICASSIGN128

// Shift operators.

inline Uint128 operator<<(const Uint128& val, int amount) {
  // uint64_t shifts of >= 64 are undefined, so we will need some
  // special-casing.
  if (amount < 64) {
    if (amount == 0) {
      return val;
    }
    uint64_t new_hi = (QuicUint128High64Impl(val) << amount) |
                      (QuicUint128Low64Impl(val) >> (64 - amount));
    uint64_t new_lo = QuicUint128Low64Impl(val) << amount;
    return Uint128(new_hi, new_lo);
  } else if (amount < 128) {
    return Uint128(QuicUint128Low64Impl(val) << (amount - 64), 0);
  } else {
    return Uint128(0, 0);
  }
}

inline Uint128 operator>>(const Uint128& val, int amount) {
  // uint64_t shifts of >= 64 are undefined, so we will need some
  // special-casing.
  if (amount < 64) {
    if (amount == 0) {
      return val;
    }
    uint64_t new_hi = QuicUint128High64Impl(val) >> amount;
    uint64_t new_lo = (QuicUint128Low64Impl(val) >> amount) |
                      (QuicUint128High64Impl(val) << (64 - amount));
    return Uint128(new_hi, new_lo);
  } else if (amount < 128) {
    return Uint128(0, QuicUint128High64Impl(val) >> (amount - 64));
  } else {
    return Uint128(0, 0);
  }
}

inline Uint128& Uint128::operator<<=(int amount) {
  // uint64_t shifts of >= 64 are undefined, so we will need some
  // special-casing.
  if (amount < 64) {
    if (amount != 0) {
      hi_ = (hi_ << amount) | (lo_ >> (64 - amount));
      lo_ = lo_ << amount;
    }
  } else if (amount < 128) {
    hi_ = lo_ << (amount - 64);
    lo_ = 0;
  } else {
    hi_ = 0;
    lo_ = 0;
  }
  return *this;
}

inline Uint128& Uint128::operator>>=(int amount) {
  // uint64_t shifts of >= 64 are undefined, so we will need some
  // special-casing.
  if (amount < 64) {
    if (amount != 0) {
      lo_ = (lo_ >> amount) | (hi_ << (64 - amount));
      hi_ = hi_ >> amount;
    }
  } else if (amount < 128) {
    hi_ = 0;
    lo_ = hi_ >> (amount - 64);
  } else {
    hi_ = 0;
    lo_ = 0;
  }
  return *this;
}

inline Uint128 operator+(const Uint128& lhs,
                                 const Uint128& rhs) {
  return Uint128(lhs) += rhs;
}

inline Uint128 operator-(const Uint128& lhs,
                                 const Uint128& rhs) {
  return Uint128(lhs) -= rhs;
}

inline Uint128 operator*(const Uint128& lhs,
                                 const Uint128& rhs) {
  return Uint128(lhs) *= rhs;
}

inline Uint128& Uint128::operator+=(const Uint128& b) {
  hi_ += b.hi_;
  uint64_t lolo = lo_ + b.lo_;
  if (lolo < lo_)
    ++hi_;
  lo_ = lolo;
  return *this;
}

inline Uint128& Uint128::operator-=(const Uint128& b) {
  hi_ -= b.hi_;
  if (b.lo_ > lo_)
    --hi_;
  lo_ -= b.lo_;
  return *this;
}

inline Uint128& Uint128::operator*=(const Uint128& b) {
  uint64_t a96 = hi_ >> 32;
  uint64_t a64 = hi_ & 0xffffffffu;
  uint64_t a32 = lo_ >> 32;
  uint64_t a00 = lo_ & 0xffffffffu;
  uint64_t b96 = b.hi_ >> 32;
  uint64_t b64 = b.hi_ & 0xffffffffu;
  uint64_t b32 = b.lo_ >> 32;
  uint64_t b00 = b.lo_ & 0xffffffffu;
  // multiply [a96 .. a00] x [b96 .. b00]
  // terms higher than c96 disappear off the high side
  // terms c96 and c64 are safe to ignore carry bit
  uint64_t c96 = a96 * b00 + a64 * b32 + a32 * b64 + a00 * b96;
  uint64_t c64 = a64 * b00 + a32 * b32 + a00 * b64;
  this->hi_ = (c96 << 32) + c64;
  this->lo_ = 0;
  // add terms after this one at a time to capture carry
  *this += Uint128(a32 * b00) << 32;
  *this += Uint128(a00 * b32) << 32;
  *this += a00 * b00;
  return *this;
}

inline Uint128 Uint128::operator++(int) {
  Uint128 tmp(*this);
  *this += 1;
  return tmp;
}

inline Uint128 Uint128::operator--(int) {
  Uint128 tmp(*this);
  *this -= 1;
  return tmp;
}

inline Uint128& Uint128::operator++() {
  *this += 1;
  return *this;
}

inline Uint128& Uint128::operator--() {
  *this -= 1;
  return *this;
}

}  // namespace basic

#if defined(basic_RUN_DOCTEST_TESTS) && !defined(DOCTEST_CONFIG_DISABLE)
#include <doctest/doctest.h>
DOCTEST_TEST_SUITE("Uint128"
  * doctest::description("should not take more than 500ms")
  * doctest::timeout(0.5))
{
  using namespace basic;
  DOCTEST_TEST_CASE("AllTests") {
    Uint128 zero(0);
    Uint128 one(1);
    DOCTEST_CHECK_EQ(zero, one & zero);
    DOCTEST_CHECK_EQ(one, one | zero);
    constexpr Uint128 kuint128max(std::numeric_limits<uint64_t>::max(),
                                        std::numeric_limits<uint64_t>::max());

    DOCTEST_CHECK_EQ(kuint128max, -one);
  }
}
#endif // DOCTEST_CONFIG_DISABLE
