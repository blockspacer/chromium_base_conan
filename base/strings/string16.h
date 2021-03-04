// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_STRINGS_STRING16_H_
#define BASE_STRINGS_STRING16_H_

// WHAT:
// A version of std::basic_string that provides 2-byte characters even when
// wchar_t is not implemented as a 2-byte type. You can access this class as
// string16. We also define char16, which string16 is based upon.
//
// WHY:
// On Windows, wchar_t is 2 bytes, and it can conveniently handle UTF-16/UCS-2
// data. Plenty of existing code operates on strings encoded as UTF-16.
//
// On many other platforms, sizeof(wchar_t) is 4 bytes by default. We can make
// it 2 bytes by using the GCC flag -fshort-wchar. But then std::wstring fails
// at run time, because it calls some functions (like wcslen) that come from
// the system's native C library -- which was built with a 4-byte wchar_t!
// It's wasteful to use 4-byte wchar_t strings to carry UTF-16 data, and it's
// entirely improper on those systems where the encoding of wchar_t is defined
// as UTF-32.
//
// Here, we define string16, which is similar to std::wstring but replaces all
// libc functions with custom, 2-byte-char compatible routines. It is capable
// of carrying UTF-16-encoded data.

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <functional>
#include <string>

#include "base/base_export.h"
#include "build/build_config.h"

// WHAT:
// Type aliases for string and character types supporting UTF-16 data. Prior to
// C++11 there was no standard library solution for this, which is why wstring
// was used where possible (i.e. where wchar_t holds UTF-16 encoded data).
//
// In C++11 we gained std::u16string, which is a cross-platform solution for
// UTF-16 strings. This is now the string16 type where ever wchar_t does not
// hold UTF16 data (i.e. commonly non-Windows platforms). Eventually this should
// be used everywhere, at which point this type alias and this file should be
// removed. https://crbug.com/911896 tracks the migration effort.

// Define a macro for wrapping construction of char16 arrays and string16s from
// a literal string. This indirection allows for an easier migration of
// base::char16 to char16_t on platforms where WCHAR_T_IS_UTF16, as only a one
// character change to the macro will be necessary.
// TODO(https://crbug.com/911896): Remove this macro once base::char16 is
// char16_t on all platforms.
#define STRING16_LITERAL(x) u##x

namespace base {
using char16 = char16_t;
using string16 = std::u16string;
}  // namespace base

#endif  // BASE_STRINGS_STRING16_H_
