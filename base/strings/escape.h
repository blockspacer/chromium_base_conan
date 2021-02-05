// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_STRINGS_ESCAPE_H_
#define BASE_STRINGS_ESCAPE_H_

#include <cstdint>

#include <set>
#include <string>

#include "base/base_export.h"
#include "base/strings/string16.h"
#include "base/strings/string_piece.h"
#include "base/strings/utf_offset_string_conversions.h"

namespace base {

class UnescapeRule {
 public:
  // A combination of the following flags that is passed to the unescaping
  // functions.
  typedef uint32_t Type;

  enum {
    // Don't unescape anything at all.
    NONE = 0,

    // Don't unescape anything special, but all normal unescaping will happen.
    // This is a placeholder and can't be combined with other flags (since it's
    // just the absence of them). All other unescape rules imply "normal" in
    // addition to their special meaning. Things like escaped letters, digits,
    // and most symbols will get unescaped with this mode.
    NORMAL = 1 << 0,

    // Convert %20 to spaces. In some places where we're showing URLs, we may
    // want this. In places where the URL may be copied and pasted out, then
    // you wouldn't want this since it might not be interpreted in one piece
    // by other applications.  Other UTF-8 spaces will not be unescaped.
    SPACES = 1 << 1,

    // Unescapes '/' and '\\'. If these characters were unescaped, the resulting
    // URL won't be the same as the source one. Moreover, they are dangerous to
    // unescape in strings that will be used as file paths or names. This value
    // should only be used when slashes don't have special meaning, like data
    // URLs.
    PATH_SEPARATORS = 1 << 2,

    // Unescapes various characters that will change the meaning of URLs,
    // including '%', '+', '&', '#'. Does not unescape path separators.
    // If these characters were unescaped, the resulting URL won't be the same
    // as the source one. This flag is used when generating final output like
    // filenames for URLs where we won't be interpreting as a URL and want to do
    // as much unescaping as possible.
    URL_SPECIAL_CHARS_EXCEPT_PATH_SEPARATORS = 1 << 3,

    // URL queries use "+" for space. This flag controls that replacement.
    REPLACE_PLUS_WITH_SPACE = 1 << 4,
  };
};

// Unescapes |escaped_text| and returns the result.
// Unescaping consists of looking for the exact pattern "%XX", where each X is
// a hex digit, and converting to the character with the numerical value of
// those digits. Thus "i%20=%203%3b" unescapes to "i = 3;", if the
// "UnescapeRule::SPACES" used.
//
// This method does not ensure that the output is a valid string using any
// character encoding. However, it does leave escaped certain byte sequences
// that would be dangerous to display to the user, because if interpreted as
// UTF-8, they could be used to mislead the user. Callers that want to
// unconditionally unescape everything for uses other than displaying data to
// the user should use UnescapeBinaryURLComponent().
BASE_EXPORT std::string UnescapeURLComponent(StringPiece escaped_text,
                                             UnescapeRule::Type rules);

// Unescapes the given substring as a URL, and then tries to interpret the
// result as being encoded as UTF-8. If the result is convertible into UTF-8, it
// will be returned as converted. If it is not, the original escaped string will
// be converted into a string16 and returned.  |adjustments| provides
// information on how the original string was adjusted to get the string
// returned.
BASE_EXPORT string16 UnescapeAndDecodeUTF8URLComponentWithAdjustments(
    StringPiece text,
    UnescapeRule::Type rules,
    OffsetAdjuster::Adjustments* adjustments);

// Unescapes a component of a URL for use as binary data. Unlike
// UnescapeURLComponent, leaves nothing unescaped, including nulls, invalid
// characters, characters that are unsafe to display, etc. This should *not*
// be used when displaying the decoded data to the user.
//
// Only the NORMAL and REPLACE_PLUS_WITH_SPACE rules are allowed.
BASE_EXPORT std::string UnescapeBinaryURLComponent(
    StringPiece escaped_text,
    UnescapeRule::Type rules = UnescapeRule::NORMAL);

// Variant of UnescapeBinaryURLComponent().  Writes output to |unescaped_text|.
// Returns true on success, returns false and clears |unescaped_text| on
// failure. Fails on characters escaped that are unsafe to unescape in some
// contexts, which are defined as characters "\0" through "\x1F" (Which includes
// CRLF but not space), and optionally path separators. Path separators include
// both forward and backward slashes on all platforms. Does not fail if any of
// those characters appear unescaped in the input string.
BASE_EXPORT bool UnescapeBinaryURLComponentSafe(StringPiece escaped_text,
                                                bool fail_on_path_separators,
                                                std::string* unescaped_text);

// Returns true if |escaped_text| contains any element of |bytes| in
// percent-encoded form.
//
// For example, if |bytes| is {'%', '/'}, returns true if |escaped_text|
// contains "%25" or "%2F", but not if it just contains bare '%' or '/'
// characters.
BASE_EXPORT bool ContainsEncodedBytes(StringPiece escaped_text,
                                      const std::set<unsigned char>& bytes);

// Normalize all line-endings in the given string to CRLF.
BASE_EXPORT std::string NormalizeLineEndingsToCRLF(const std::string& from);

// Normalize all line-endings in the given string to LF and append the result to
// the given buffer.
BASE_EXPORT void NormalizeLineEndingsToLF(const std::string& from,
                                         std::vector<char>& result);

// Normalize all line-endings in the given string to the native line-endings and
// append the result to the given buffer.
// (Normalize to CRLF on Windows and normalize to LF on all other platforms.)
BASE_EXPORT void NormalizeLineEndingsToNative(const std::string& from,
                                             std::vector<char>& result);

// Escapes all characters except unreserved characters. Unreserved characters,
// as defined in RFC 3986, include alphanumerics and -._~
BASE_EXPORT std::string EscapeAllExceptUnreserved(base::StringPiece text);

// Escapes characters in text suitable for use as a query parameter value.
// We %XX everything except alphanumerics and -_.!~*'()
// Spaces change to "+" unless you pass usePlus=false.
// This is basically the same as encodeURIComponent in javascript.
BASE_EXPORT std::string EscapeQueryParamValue(base::StringPiece text,
                                             bool use_plus);

// Escapes a partial or complete file/pathname.  This includes:
// non-printable, non-7bit, and (including space)  "#%:<>?[\]^`{|}
BASE_EXPORT std::string EscapePath(base::StringPiece path);

#if defined(OS_APPLE)
// Escapes characters as per expectations of NSURL. This includes:
// non-printable, non-7bit, and (including space)  "#%<>[\]^`{|}
BASE_EXPORT std::string EscapeNSURLPrecursor(base::StringPiece precursor);
#endif  // defined(OS_APPLE)

// Escapes application/x-www-form-urlencoded content.  This includes:
// non-printable, non-7bit, and (including space)  ?>=<;+'&%$#"![\]^`{|}
// Space is escaped as + (if use_plus is true) and other special characters
// as %XX (hex).
BASE_EXPORT std::string EscapeUrlEncodedData(base::StringPiece path,
                                            bool use_plus);

// Escapes all non-ASCII input, as well as escaping % to %25.
BASE_EXPORT std::string EscapeNonASCIIAndPercent(base::StringPiece input);

// Escapes all non-ASCII input. Note this function leaves % unescaped, which
// means the unescaping the resulting string will not give back the original
// input.
BASE_EXPORT std::string EscapeNonASCII(base::StringPiece input);

// Escapes characters in text suitable for use as an external protocol handler
// command.
// We %XX everything except alphanumerics and -_.!~*'() and the restricted
// characters (;/?:@&=+$,#[]) and a valid percent escape sequence (%XX).
BASE_EXPORT std::string EscapeExternalHandlerValue(base::StringPiece text);

// Appends the given character to the output string, escaping the character if
// the character would be interpreted as an HTML delimiter.
BASE_EXPORT void AppendEscapedCharForHTML(char c, std::string* output);

// Escapes chars that might cause this text to be interpreted as HTML tags.
BASE_EXPORT std::string EscapeForHTML(base::StringPiece text);
BASE_EXPORT base::string16 EscapeForHTML(base::StringPiece16 text);

// Unescaping ------------------------------------------------------------------

// Unescapes the following ampersand character codes from |text|:
// &lt; &gt; &amp; &quot; &#39;
BASE_EXPORT base::string16 UnescapeForHTML(base::StringPiece16 text);

// Return a string as a quoted value, escaping quotes and line breaks.
BASE_EXPORT std::string PercentEscapeString(const std::string& unescaped_string);

// Compute and return application/x-www-form-urlencoded POST body for share
// target.
BASE_EXPORT std::string ComputeUrlEncodedBody(const std::vector<std::string>& names,
                                  const std::vector<std::string>& values);

}  // namespace base

#endif  // BASE_STRINGS_ESCAPE_H_
