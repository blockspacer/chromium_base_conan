// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/files/file_path_util.h" // IWYU pragma: associated

#include <base/files/file_path.h>
#include <base/files/file_util.h>
#include <base/path_service.h>
#include <base/strings/string_util.h>
#include <base/strings/sys_string_conversions.h>
#include <base/strings/utf_string_conversions.h>

namespace {

base::FilePath GetPath(base::BasePathKey default_dir_key,
                       const base::FilePath& path)
{
  if (path.IsAbsolute()) {
    // If |path| is absolute, returns |path|.
    return path;
  }

  base::FilePath default_dir;
  if (!base::PathService::Get(default_dir_key, &default_dir))
    LOG(DFATAL) << "Cannot get default dir: " << default_dir_key;

  // prepends directory to |path| (e.g. {HOME}/|path| or {BIN}/|path|).
  base::FilePath adjusted_path(default_dir.Append(path));
  DVLOG(1) << "Path adjusted from " << path.value() << " to "
           << adjusted_path.value();

  return adjusted_path;
}

const char kHexString[] = "0123456789ABCDEF";

inline char IntToHex(int i) {
  DCHECK_GE(i, 0) << i << " not a hex value";
  DCHECK_LE(i, 15) << i << " not a hex value";
  return kHexString[i];
}

// A fast bit-vector map for ascii characters.
//
// Internally stores 256 bits in an array of 8 ints.
// Does quick bit-flicking to lookup needed characters.
struct Charmap {
  bool Contains(unsigned char c) const {
    return ((map[c >> 5] & (1 << (c & 31))) != 0);
  }

  uint32_t map[8];
};

// Given text to escape and a Charmap defining which values to escape,
// return an escaped string.  If use_plus is true, spaces are converted
// to +, otherwise, if spaces are in the charmap, they are converted to
// %20. And if keep_escaped is true, %XX will be kept as it is, otherwise, if
// '%' is in the charmap, it is converted to %25.
std::string Escape(base::StringPiece text,
                   const Charmap& charmap,
                   bool use_plus,
                   bool keep_escaped = false) {
  std::string escaped;
  escaped.reserve(text.length() * 3);
  for (unsigned int i = 0; i < text.length(); ++i) {
    unsigned char c = static_cast<unsigned char>(text[i]);
    if (use_plus && ' ' == c) {
      escaped.push_back('+');
    } else if (keep_escaped && '%' == c && i + 2 < text.length() &&
               base::IsHexDigit(text[i + 1]) && base::IsHexDigit(text[i + 2])) {
      escaped.push_back('%');
    } else if (charmap.Contains(c)) {
      escaped.push_back('%');
      escaped.push_back(IntToHex(c >> 4));
      escaped.push_back(IntToHex(c & 0xf));
    } else {
      escaped.push_back(c);
    }
  }
  return escaped;
}

}  // namespace

namespace basic {

std::string StripMimeSubType(const std::string& mime_type)
{
  if (mime_type.empty()) {
    return mime_type;
  }

  size_t index = mime_type.find_first_of('/', 0);

  if (index == 0 || index == mime_type.size() - 1 ||
      index == std::string::npos)
  {
    // This looks malformed, return an empty string.
    return std::string();
  }

  return mime_type.substr(0, index);
}

base::FilePath GetHomePath(const base::FilePath& path)
{
  return GetPath(base::DIR_HOME, path);
}

base::FilePath GetHomePathASCII(const std::string& path)
{
  return GetHomePath(base::FilePath(path));
}

base::FilePath GetBinPath(const base::FilePath& path)
{
  return GetPath(base::DIR_EXE, path);
}

base::FilePath GetBinPathASCII(const std::string& path)
{
  return GetBinPath(base::FilePath(path));
}

base::FilePath GetTmpPath(const base::FilePath& path)
{
  return GetPath(base::DIR_TEMP, path);
}

base::FilePath GetTmpPathASCII(const std::string& path)
{
  return GetTmpPath(base::FilePath(path));
}

std::string EscapePath(base::StringPiece path) {
  // non-printable, non-7bit, and (including space)  "#%:<>?[\]^`{|}
  static const Charmap kPathCharmap = {{
    0xffffffffL, 0xd400002dL, 0x78000000L, 0xb8000001L,
    0xffffffffL, 0xffffffffL, 0xffffffffL, 0xffffffffL
  }};
  return Escape(path, kPathCharmap, false);
}

bool IsReservedNameOnWindows(const base::FilePath::StringType& filename) {
  // This list is taken from the MSDN article "Naming a file"
  // http://msdn2.microsoft.com/en-us/library/aa365247(VS.85).aspx
  // I also added clock$ because GetSaveFileName seems to consider it as a
  // reserved name too.
  static const char* const known_devices[] = {
      "con",  "prn",  "aux",  "nul",  "com1", "com2", "com3",  "com4",
      "com5", "com6", "com7", "com8", "com9", "lpt1", "lpt2",  "lpt3",
      "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9", "clock$"};
#if defined(OS_WIN)
  std::string filename_lower = base::ToLowerASCII(base::WideToUTF8(filename));
#elif defined(OS_POSIX) || defined(OS_FUCHSIA)
  std::string filename_lower = base::ToLowerASCII(filename);
#endif

  for (const char* const device : known_devices) {
    // Exact match.
    if (filename_lower == device)
      return true;
    // Starts with "DEVICE.".
    if (base::StartsWith(filename_lower, std::string(device) + ".",
                         base::CompareCase::SENSITIVE)) {
      return true;
    }
  }

  static const char* const magic_names[] = {
      // These file names are used by the "Customize folder" feature of the
      // shell.
      "desktop.ini",
      "thumbs.db",
  };

  for (const char* const magic_name : magic_names) {
    if (filename_lower == magic_name)
      return true;
  }

  return false;
}

} // namespace basic
