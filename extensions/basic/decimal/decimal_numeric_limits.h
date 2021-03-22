#pragma once

#include "basic/decimal/decimal.h"

namespace basic
{

// Redefine this inside the decimal namespace so it doesn't clash with the standard library.
template<typename T> class numeric_limits;

template<> class numeric_limits<decimal32> {
public:
  static constexpr int digits = 7;
  static constexpr int min_exponent = -94;
  static constexpr int max_exponent = 97;
};


template<> class numeric_limits<decimal64> {
public:
  static constexpr int digits = 16;
  static constexpr int min_exponent = -382;
  static constexpr int max_exponent = 385;
};

/*
template<> class numeric_limits<decimal128> {
public:
  static constexpr int digits = 34;
  static constexpr int min_exponent = -6142;
  static constexpr int max_exponent = 6145;
};*/

} // namespace basic
