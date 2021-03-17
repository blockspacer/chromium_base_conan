// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/strings/string_number_conversions.h"

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <wctype.h>

#include <limits>
#include <type_traits>

#include "base/logging.h"
#include "base/numerics/safe_math.h"
#include "base/scoped_clear_last_error.h"
#include "base/strings/utf_string_conversions.h"
#include "base/strings/stringprintf.h"

#include "basic/macros.h"

using namespace base;

namespace basic {

// Utility to convert a character to a digit in a given base
template<typename CHAR, int BASE, bool BASE_LTE_10> class BaseCharToDigit {
};

// Faster specialization for bases <= 10
template<typename CHAR, int BASE> class BaseCharToDigit<CHAR, BASE, true> {
 public:
  static bool Convert(CHAR c, uint8_t* digit) {
    if (c >= '0' && c < '0' + BASE) {
      *digit = static_cast<uint8_t>(c - '0');
      return true;
    }
    return false;
  }
};

// Specialization for bases where 10 < base <= 36
template<typename CHAR, int BASE> class BaseCharToDigit<CHAR, BASE, false> {
 public:
  static bool Convert(CHAR c, uint8_t* digit) {
    if (c >= '0' && c <= '9') {
      *digit = c - '0';
    } else if (c >= 'a' && c < 'a' + BASE - 10) {
      *digit = c - 'a' + 10;
    } else if (c >= 'A' && c < 'A' + BASE - 10) {
      *digit = c - 'A' + 10;
    } else {
      return false;
    }
    return true;
  }
};

template <int BASE, typename CHAR>
bool CharToDigit(CHAR c, uint8_t* digit) {
  return BaseCharToDigit<CHAR, BASE, BASE <= 10>::Convert(c, digit);
}

// There is an IsUnicodeWhitespace for wchars defined in string_util.h, but it
// is locale independent, whereas the functions we are replacing were
// locale-dependent. TBD what is desired, but for the moment let's not
// introduce a change in behaviour.
template<typename CHAR> class WhitespaceHelper {
};

template<> class WhitespaceHelper<char> {
 public:
  static bool Invoke(char c) {
    return 0 != isspace(static_cast<unsigned char>(c));
  }
};

template<> class WhitespaceHelper<char16> {
 public:
  static bool Invoke(char16 c) {
    return 0 != iswspace(c);
  }
};

template<typename CHAR> bool LocalIsWhitespace(CHAR c) {
  return WhitespaceHelper<CHAR>::Invoke(c);
}


// IteratorRangeToNumberTraits should provide:
//  - a typedef for iterator_type, the iterator type used as input.
//  - a typedef for value_type, the target numeric type.
//  - static functions min, max (returning the minimum and maximum permitted
//    values)
//  - constant kBase, the base in which to interpret the input
template<typename IteratorRangeToNumberTraits>
class IteratorRangeToNumber {
 public:
  typedef IteratorRangeToNumberTraits traits;
  typedef typename traits::iterator_type const_iterator;
  typedef typename traits::value_type value_type;

  // Generalized iterator-range-to-number conversion.
  //
  static bool Invoke(const_iterator begin,
                     const_iterator end,
                     value_type* output) {
    bool valid = true;

    while (begin != end && LocalIsWhitespace(*begin)) {
      valid = false;
      ++begin;
    }

    if (begin != end && *begin == '-') {
      if (!std::numeric_limits<value_type>::is_signed) {
        *output = 0;
        valid = false;
      } else if (!Negative::Invoke(begin + 1, end, output)) {
        valid = false;
      }
    } else {
      if (begin != end && *begin == '+') {
        ++begin;
      }
      if (!Positive::Invoke(begin, end, output)) {
        valid = false;
      }
    }

    return valid;
  }

 private:
  // Sign provides:
  //  - a static function, CheckBounds, that determines whether the next digit
  //    causes an overflow/underflow
  //  - a static function, Increment, that appends the next digit appropriately
  //    according to the sign of the number being parsed.
  template<typename Sign>
  class Base {
   public:
    static bool Invoke(const_iterator begin, const_iterator end,
                       typename traits::value_type* output) {
      *output = 0;

      if (begin == end) {
        return false;
      }

      // Note: no performance difference was found when using template
      // specialization to remove this check in bases other than 16
      if (traits::kBase == 16 && end - begin > 2 && *begin == '0' &&
          (*(begin + 1) == 'x' || *(begin + 1) == 'X')) {
        begin += 2;
      }

      for (const_iterator current = begin; current != end; ++current) {
        uint8_t new_digit = 0;

        if (!CharToDigit<traits::kBase>(*current, &new_digit)) {
          return false;
        }

        if (current != begin) {
          if (!Sign::CheckBounds(output, new_digit)) {
            return false;
          }
          *output *= traits::kBase;
        }

        Sign::Increment(new_digit, output);
      }
      return true;
    }
  };

  class Positive : public Base<Positive> {
   public:
    static bool CheckBounds(value_type* output, uint8_t new_digit) {
      if (*output > static_cast<value_type>(traits::max() / traits::kBase) ||
          (*output == static_cast<value_type>(traits::max() / traits::kBase) &&
           new_digit > traits::max() % traits::kBase)) {
        *output = traits::max();
        return false;
      }
      return true;
    }
    static void Increment(uint8_t increment, value_type* output) {
      *output += increment;
    }
  };

  class Negative : public Base<Negative> {
   public:
    static bool CheckBounds(value_type* output, uint8_t new_digit) {
      if (*output < traits::min() / traits::kBase ||
          (*output == traits::min() / traits::kBase &&
           new_digit > 0 - traits::min() % traits::kBase)) {
        *output = traits::min();
        return false;
      }
      return true;
    }
    static void Increment(uint8_t increment, value_type* output) {
      *output -= increment;
    }
  };
};

template<typename ITERATOR, typename VALUE, int BASE>
class BaseIteratorRangeToNumberTraits {
 public:
  typedef ITERATOR iterator_type;
  typedef VALUE value_type;
  static value_type min() {
    return std::numeric_limits<value_type>::min();
  }
  static value_type max() {
    return std::numeric_limits<value_type>::max();
  }
  static const int kBase = BASE;
};

template <typename VALUE, int BASE>
class StringPieceToNumberTraits
    : public BaseIteratorRangeToNumberTraits<StringPiece::const_iterator,
                                             VALUE,
                                             BASE> {
};

template <typename VALUE>
bool StringToIntImpl(StringPiece input, VALUE* output) {
  return IteratorRangeToNumber<StringPieceToNumberTraits<VALUE, 10> >::Invoke(
      input.begin(), input.end(), output);
}

bool StringToInt32(StringPiece input, int32_t* output) {
  return StringToIntImpl(input, output);
}

bool StringToUint32(StringPiece input, uint32_t* output) {
  return StringToIntImpl(input, output);
}

std::string HexDecode(base::StringPiece input) {
  std::vector<uint8_t> output;
  std::string result;
  if (base::HexStringToBytes(input, &output))
    result.assign(reinterpret_cast<const char*>(&output[0]), output.size());
  return result;
}

std::string HexDump(base::StringPiece input) {
  const int kBytesPerLine = 16;  // Maximum bytes dumped per line.
  int offset = 0;
  const char* buf = input.data();
  int bytes_remaining = input.size();
  std::string output;
  const char* p = buf;
  while (bytes_remaining > 0) {
    const int line_bytes = std::min(bytes_remaining, kBytesPerLine);
    base::StringAppendF(&output, "0x%04x:  ", offset);
    for (int i = 0; i < kBytesPerLine; ++i) {
      if (i < line_bytes) {
        base::StringAppendF(&output, "%02x", static_cast<unsigned char>(p[i]));
      } else {
        output += "  ";
      }
      if (i % 2) {
        output += ' ';
      }
    }
    output += ' ';
    for (int i = 0; i < line_bytes; ++i) {
      // Replace non-printable characters and 0x20 (space) with '.'
      output += (p[i] > 0x20 && p[i] < 0x7f) ? p[i] : '.';
    }

    bytes_remaining -= line_bytes;
    offset += line_bytes;
    p += line_bytes;
    output += '\n';
  }
  return output;
}

}  // namespace basic
