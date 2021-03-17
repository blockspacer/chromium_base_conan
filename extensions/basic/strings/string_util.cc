#include "basic/strings/string_util.h" // IWYU pragma: associated

using namespace base;

namespace {

bool islatinalpha(const int c) {
  // isalpha() is locale-dependent.
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

} // namespace

namespace basic {

std::string ElideMiddle(const std::string& str, size_t width)
{
  switch (width) {
    case 0: return "";
    case 1: return ".";
    case 2: return "..";
    case 3: return "...";
  }
  const int kMargin = 3;  // Space for "...".
  std::string result = str;
  if (result.size() > width)
  {
    size_t elide_size = (width - kMargin) / 2;
    result = result.substr(0, elide_size)
      + "..."
      + result.substr(result.size() - elide_size, elide_size);
  }
  return result;
}

std::string StripAnsiEscapeCodes(const std::string& in) {
  std::string stripped;
  stripped.reserve(in.size());

  for (size_t i = 0; i < in.size(); ++i) {
    if (in[i] != '\33') {
      // Not an escape code.
      stripped.push_back(in[i]);
      continue;
    }

    // Only strip CSIs for now.
    if (i + 1 >= in.size()) break;
    if (in[i + 1] != '[') continue;  // Not a CSI.
    i += 2;

    // Skip everything up to and including the next [a-zA-Z].
    while (i < in.size() && !islatinalpha(in[i]))
      ++i;
  }
  return stripped;
}

} // namespace basic
