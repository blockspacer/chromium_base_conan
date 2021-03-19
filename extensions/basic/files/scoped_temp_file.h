// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <string>

#include "base/files/file_path.h"
#include "base/macros.h"

namespace basic {

// Creates a temporary file that is deleted when this object is destroyed,
// unless the underlying file has been moved or deleted.
// Warning: This class uses CHECKs, and should only be used for testing.
class ScopedTempFile {
 public:
  ScopedTempFile();
  ~ScopedTempFile();

  // Return the path to the temporary file. Note that if the underlying file has
  // been moved or deleted, this will still return the original path.
  base::FilePath path() const { return path_; }

  // Returns true if the underlying file exists, false otherwise. This will
  // return false, for example, if the file has been moved or deleted.
  bool FileExists() const;

  // Write the contents of |str| to the file. Return the number of characters
  // written, or -1 on error. CHECKs that FileExists() returns true.
  int Write(const std::string& str);

  // Read the file and return the contents. CHECKs that FileExists() returns
  // true.
  std::string Read() const;

 private:
  base::FilePath path_;

  DISALLOW_COPY_AND_ASSIGN(ScopedTempFile);
};

}  // namespace basic
