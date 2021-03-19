// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

// long long macros to be used because gcc and vc++ use different suffixes,
// and different size specifiers in format strings
#undef LONGLONG
#undef ULONGLONG

#ifdef _MSC_VER /* if Visual C++ */

// VC++ long long suffixes
#define LONGLONG(x) x##I64
#define ULONGLONG(x) x##UI64

#else /* not Visual C++ */

#define LONGLONG(x) x##LL
#define ULONGLONG(x) x##ULL

#endif // _MSC_VER
