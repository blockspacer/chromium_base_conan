// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/test/icu_test_util.h"

#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/i18n/icu_util.h"
#include "base/i18n/rtl.h"
#include "base/path_service.h"
#include "base/files/file_util.h"
#include "third_party/icu/source/common/unicode/uloc.h"

namespace base {
namespace test {

ScopedRestoreICUDefaultLocale::ScopedRestoreICUDefaultLocale()
    : ScopedRestoreICUDefaultLocale(std::string()) {}

ScopedRestoreICUDefaultLocale::ScopedRestoreICUDefaultLocale(
    const std::string& locale)
    : default_locale_(uloc_getDefault()) {
  if (!locale.empty())
    i18n::SetICUDefaultLocale(locale.data());
}

ScopedRestoreICUDefaultLocale::~ScopedRestoreICUDefaultLocale() {
  i18n::SetICUDefaultLocale(default_locale_.data());
}

static const base::FilePath::CharType kIcuDataFileName[]
  = FILE_PATH_LITERAL("./resources/icu/optimal/icudt64l.dat");

void InitializeICUForTesting() {
  i18n::AllowMultipleInitializeCallsForTesting();

  base::FilePath dir_exe;
  if (!base::PathService::Get(base::DIR_EXE, &dir_exe)) {
    NOTREACHED();
  }
  if(!base::PathExists(dir_exe.Append(kIcuDataFileName))) {
    LOG(WARNING)
      << "unable to find icu i18n file: "
      << dir_exe.Append(kIcuDataFileName);
  } else {
    DVLOG(9)
      << "loading icu i18n file: "
      << dir_exe.Append(kIcuDataFileName);
  }
  bool icu_initialized
    = base::i18n::InitializeICUWithPath(
        dir_exe.Append(kIcuDataFileName));
  if(!icu_initialized) {
    LOG(WARNING)
      << "unable to initialize icu i18n file: "
      << dir_exe.Append(kIcuDataFileName);
  }
}

}  // namespace test
}  // namespace base
