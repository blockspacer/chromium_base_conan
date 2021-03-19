// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <string>

#include <base/files/file_path.h>
#include <base/logging.h>
#include <base/macros.h>
#include <base/location.h>
#include <basic/rvalue_cast.h>
#include <base/files/file_path.h>
#include <base/strings/string_piece.h>

namespace basic {

// Returns the provided MIME type without the subtype component.
//
// EXAMPLE
//
// "video/mp4" -> "video"
// "video/" -> ""
// "/abc/xyz" -> ""
std::string StripMimeSubType(const std::string& mime_type);

// If |path| is relative, returns the path created by prepending HOME directory
// to |path| (e.g. {HOME}/|path|). If |path| is absolute, returns |path|.
base::FilePath GetHomePath(const base::FilePath& path);
base::FilePath GetHomePathASCII(const std::string& path);

// If |path| is relative, returns the path created by prepending BIN directory
// to |path| (e.g. {BIN}/|path|). If |path| is absolute, returns |path|.
base::FilePath GetBinPath(const base::FilePath& path);
base::FilePath GetBinPathASCII(const std::string& path);

// If |path| is relative, returns the path created by prepending TMP directory
// to |path| (e.g. {TMP}/|path|). If |path| is absolute, returns |path|.
base::FilePath GetTmpPath(const base::FilePath& path);
base::FilePath GetTmpPathASCII(const std::string& path);

// Escapes a partial or complete file/pathname.  This includes:
// non-printable, non-7bit, and (including space)  "#%:<>?[\]^`{|}
//
// EXAMPLE
//
// // Not-escaped
//
// "\x02\n\x1d !\"#$%&'()*+,-./0123456789:;"
// "<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// "[\\]^_`abcdefghijklmnopqrstuvwxyz"
// "{|}~\x7f\x80\xff"
//
// // Escaped
//
// "%02%0A%1D%20!%22%23$%25&'()*+,-./0123456789%3A;"
// "%3C=%3E%3F@ABCDEFGHIJKLMNOPQRSTUVWXYZ"
// "%5B%5C%5D%5E_%60abcdefghijklmnopqrstuvwxyz"
// "%7B%7C%7D~%7F%80%FF"
//
std::string EscapePath(base::StringPiece path);

// Returns whether the specified file name is a reserved name on Windows.
// This includes names like "com2.zip" (which correspond to devices) and
// desktop.ini and thumbs.db which have special meaning to the Windows shell.
// Even on other platforms, this will return whether or not a file name is
// reserved on Windows.
bool IsReservedNameOnWindows(
    const base::FilePath::StringType& filename);

} // namespace basic
