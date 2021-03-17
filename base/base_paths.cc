// Copyright (c) 2006-2008 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/base_paths.h"

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/path_service.h"
#include "base/command_line.h"

const char kTestDataDirFlag[] = "test-data-dir";
const char kAssetsDirFlag[] = "assets-dir";

namespace base {

bool PathProvider(int key, FilePath* result) {
  // NOTE: DIR_CURRENT is a special case in PathService::Get

  switch (key) {
    case DIR_EXE:
      if (!PathService::Get(FILE_EXE, result))
        return false;
      *result = result->DirName();
      return true;
    case DIR_MODULE:
      if (!PathService::Get(FILE_MODULE, result))
        return false;
      *result = result->DirName();
      return true;
    case DIR_ASSETS: {

      // try to set from command-line flag
      {
        base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
        const bool use_assets_path = command_line->HasSwitch(kAssetsDirFlag);
        FilePath assets_path;
        if(use_assets_path) {
          assets_path = command_line->GetSwitchValuePath(kAssetsDirFlag);
          if (!PathExists(assets_path)) { // We don't want to create this.
            CHECK(false)
              << "Unable to find path to test data (provide --assets-dir argument): "
              << assets_path
              << " Current --assets-dir argument is:"
              << assets_path;
            return false;
          }
          *result = assets_path;
          return true;
        }
      }

      return PathService::Get(DIR_MODULE, result);
    }
    case DIR_TEMP:
      return GetTempDir(result);
    case base::DIR_HOME:
      *result = GetHomeDir();
      return true;
    case DIR_TEST_DATA: {
      FilePath source_path;
      if (!PathService::Get(DIR_SOURCE_ROOT, &source_path))
        return false;

      FilePath test_data_path;
      test_data_path = source_path.Append(FILE_PATH_LITERAL("base"));
      test_data_path = test_data_path.Append(FILE_PATH_LITERAL("test"));
      test_data_path = test_data_path.Append(FILE_PATH_LITERAL("data"));

      // try to set from command-line flag
      {
        base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
        const bool use_test_data_path = command_line->HasSwitch(kTestDataDirFlag);
        if(use_test_data_path) {
          test_data_path = command_line->GetSwitchValuePath(kTestDataDirFlag);
          if (!PathExists(test_data_path)) { // We don't want to create this.
            CHECK(false)
              << "Unable to find path to test data (provide --test-data-dir argument): "
              << test_data_path
              << " Current --test-data-dir argument is:"
              << test_data_path;
            return false;
          }
        }
      }

      *result = test_data_path;
      return true;
    }
    default:
      return false;
  }
}

}  // namespace base
