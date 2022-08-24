// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/location.h"

#if defined(COMPILER_MSVC)
#include <intrin.h>
#endif

#include "base/compiler_specific.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/stringprintf.h"
#include "build/build_config.h"
#include "basic/wasm_util.h"

namespace base {

Location::Location() = default;
Location::Location(const Location& other) = default;

Location::Location(const char* file_name, const void* program_counter)
    : file_name_(file_name), program_counter_(program_counter) {}

Location::Location(const char* function_name,
                   const char* file_name,
                   int line_number,
                   const void* program_counter)
    : function_name_(function_name),
      file_name_(file_name),
      line_number_(line_number),
      program_counter_(program_counter) {
#if !defined(OS_NACL) && !defined(OS_EMSCRIPTEN)
  // The program counter should not be null except in a default constructed
  // (empty) Location object. This value is used for identity, so if it doesn't
  // uniquely identify a location, things will break.
  //
  // The program counter isn't supported in NaCl so location objects won't work
  // properly in that context.
  DCHECK(program_counter);
#endif
}

namespace {

std::string LocToString(const char* file_name,
  const char* function_name,
  int line_number,
  const void* program_counter,
  const bool has_source_info)
{
  if (has_source_info()) {
    return std::string(function_name_) + "@" + file_name_ + ":" +
           NumberToString(line_number_);
  }
  return StringPrintf("pc:%p", program_counter_);
}

} // namespace

std::string Location::ToString() const {
  return LocToString(file_name_, function_name_, line_number_, program_counter_, has_source_info());
}

std::string Location::ToShortString() const {
  const std::string file_name = file_name_
    ? std::filesystem::path{file_name_}.filename().string()
    : "";
  return LocToString(file_name.c_str(), function_name_, line_number_, program_counter_, has_source_info());
}

#if defined(OS_EMSCRIPTEN) && defined(USE_OFFSET_CONVERTER)
// __builtin_return_address requires -s USE_OFFSET_CONVERTER=1 to work. (#9073)
#define RETURN_ADDRESS() \
  __builtin_extract_return_addr(__builtin_return_address(0))
#elif defined(OS_EMSCRIPTEN) && !defined(USE_OFFSET_CONVERTER)
// emscripten_return_address implements the functionality of gcc/clang's __builtin_return_address. (#8617)
#define RETURN_ADDRESS() emscripten_return_address()
#elif defined(COMPILER_MSVC)
#define RETURN_ADDRESS() _ReturnAddress()
#elif defined(COMPILER_GCC) && !defined(OS_NACL)
#define RETURN_ADDRESS() \
  __builtin_extract_return_addr(__builtin_return_address(0))
#else
#define RETURN_ADDRESS() nullptr
#endif

#if !BUILDFLAG(FROM_HERE_USES_LOCATION_BUILTINS)
#if !BUILDFLAG(ENABLE_LOCATION_SOURCE)

// static
NOINLINE Location Location::CreateFromHere(const char* file_name) {
  return Location(file_name, RETURN_ADDRESS());
}

#else

// static
NOINLINE Location Location::CreateFromHere(const char* function_name,
                                           const char* file_name,
                                           int line_number) {
  return Location(function_name, file_name, line_number, RETURN_ADDRESS());
}

#endif
#endif

#if SUPPORTS_LOCATION_BUILTINS && BUILDFLAG(ENABLE_LOCATION_SOURCE)
// static
NOINLINE Location Location::Current(const char* function_name,
                                    const char* file_name,
                                    int line_number) {
  return Location(function_name, file_name, line_number, RETURN_ADDRESS());
}
#elif SUPPORTS_LOCATION_BUILTINS
// static
NOINLINE Location Location::Current(const char* file_name) {
  return Location(file_name, RETURN_ADDRESS());
}
#else
// static
NOINLINE Location Location::Current() {
  return Location(nullptr, RETURN_ADDRESS());
}
#endif

//------------------------------------------------------------------------------
NOINLINE const void* GetProgramCounter() {
  return RETURN_ADDRESS();
}

}  // namespace base
