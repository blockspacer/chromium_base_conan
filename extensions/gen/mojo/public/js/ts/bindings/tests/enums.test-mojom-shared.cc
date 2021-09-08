// mojo/public/js/ts/bindings/tests/enums.test-mojom-shared.cc is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/js/ts/bindings/tests/enums.test-mojom-shared.h"

#include <utility>

#include "base/stl_util.h"  // for base::size()
#include "base/strings/stringprintf.h"
#include "mojo/public/cpp/bindings/lib/validate_params.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/lib/validation_util.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

#include "mojo/public/js/ts/bindings/tests/enums.test-mojom-params-data.h"
namespace mojo {
namespace tstest {

std::string EmptyEnumToString(EmptyEnum value) {
  return base::StringPrintf("Unknown EmptyEnum value: %i", static_cast<int32_t>(value));
}

std::ostream& operator<<(std::ostream& os, EmptyEnum value) {
  return os << EmptyEnumToString(value);
}

std::string EnumWithNoValuesToString(EnumWithNoValues value) {
  switch(value) {
    case EnumWithNoValues::ZERO:
      return "ZERO";
    case EnumWithNoValues::ONE:
      return "ONE";
    case EnumWithNoValues::TWO:
      return "TWO";
    default:
      return base::StringPrintf("Unknown EnumWithNoValues value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, EnumWithNoValues value) {
  return os << EnumWithNoValuesToString(value);
}

std::string EnumWithFirstValueToString(EnumWithFirstValue value) {
  switch(value) {
    case EnumWithFirstValue::FIVE:
      return "FIVE";
    case EnumWithFirstValue::SIX:
      return "SIX";
    case EnumWithFirstValue::SEVEN:
      return "SEVEN";
    default:
      return base::StringPrintf("Unknown EnumWithFirstValue value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, EnumWithFirstValue value) {
  return os << EnumWithFirstValueToString(value);
}

std::string EnumWithLastValueToString(EnumWithLastValue value) {
  switch(value) {
    case EnumWithLastValue::ZERO:
      return "ZERO";
    case EnumWithLastValue::ONE:
      return "ONE";
    case EnumWithLastValue::TEN:
      return "TEN";
    default:
      return base::StringPrintf("Unknown EnumWithLastValue value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, EnumWithLastValue value) {
  return os << EnumWithLastValueToString(value);
}

std::string EnumWithInterspersedValuesToString(EnumWithInterspersedValues value) {
  switch(value) {
    case EnumWithInterspersedValues::ZERO:
      return "ZERO";
    case EnumWithInterspersedValues::THREE:
      return "THREE";
    case EnumWithInterspersedValues::FOUR:
      return "FOUR";
    case EnumWithInterspersedValues::EIGHT:
      return "EIGHT";
    case EnumWithInterspersedValues::NINE:
      return "NINE";
    default:
      return base::StringPrintf("Unknown EnumWithInterspersedValues value: %i", static_cast<int32_t>(value));
  }
}

std::ostream& operator<<(std::ostream& os, EnumWithInterspersedValues value) {
  return os << EnumWithInterspersedValuesToString(value);
}

namespace internal {

}  // namespace internal
}  // namespace tstest
}  // namespace mojo

namespace perfetto {

// static
void TraceFormatTraits<::mojo::tstest::EmptyEnum>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo::tstest::EmptyEnum value) {
  return std::move(context).WriteString(::mojo::tstest::EmptyEnumToString(value));
}

} // namespace perfetto

namespace perfetto {

// static
void TraceFormatTraits<::mojo::tstest::EnumWithNoValues>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo::tstest::EnumWithNoValues value) {
  return std::move(context).WriteString(::mojo::tstest::EnumWithNoValuesToString(value));
}

} // namespace perfetto

namespace perfetto {

// static
void TraceFormatTraits<::mojo::tstest::EnumWithFirstValue>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo::tstest::EnumWithFirstValue value) {
  return std::move(context).WriteString(::mojo::tstest::EnumWithFirstValueToString(value));
}

} // namespace perfetto

namespace perfetto {

// static
void TraceFormatTraits<::mojo::tstest::EnumWithLastValue>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo::tstest::EnumWithLastValue value) {
  return std::move(context).WriteString(::mojo::tstest::EnumWithLastValueToString(value));
}

} // namespace perfetto

namespace perfetto {

// static
void TraceFormatTraits<::mojo::tstest::EnumWithInterspersedValues>::WriteIntoTracedValue(
   perfetto::TracedValue context, ::mojo::tstest::EnumWithInterspersedValues value) {
  return std::move(context).WriteString(::mojo::tstest::EnumWithInterspersedValuesToString(value));
}

} // namespace perfetto