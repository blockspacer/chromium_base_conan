#pragma once

#include "build/build_config.h"

#include <ostream>
#include <utility>

namespace basic {

// Supported console colors
enum class TermColor
{
  BLACK,
  BLUE,
  GREEN,
  CYAN,
  RED,
  MAGENTA,
  BROWN,
  GREY,
  DARKGREY,
  LIGHTBLUE,
  LIGHTGREEN,
  LIGHTCYAN,
  LIGHTRED,
  LIGHTMAGENTA,
  YELLOW,
  WHITE
};

// Stream manipulator: change console text color
template <class TOutputStream>
TOutputStream& operator<<(TOutputStream& stream, TermColor color);

// Stream manipulator: change console text and background colors
template <class TOutputStream>
TOutputStream& operator<<(
  TOutputStream& stream, std::pair<TermColor, TermColor> colors);

// Console management static class
//
// Provides console management functionality such as setting
// text and background colors.
//
// Thread-safe.
//
class TermColorManager
{
public:
  TermColorManager() = delete;
  TermColorManager(const TermColorManager&) = delete;
  TermColorManager(TermColorManager&&) = delete;
  ~TermColorManager() = delete;

  TermColorManager& operator=(const TermColorManager&) = delete;
  TermColorManager& operator=(TermColorManager&&) = delete;

  // Set console text color
  static void Set(TermColor color, TermColor background = TermColor::BLACK);
};

} // namespace basic

template <class TOutputStream>
inline TOutputStream& operator<<(TOutputStream& stream, basic::TermColor color)
{
  basic::TermColorManager::Set(color);
  return stream;
}

template <class TOutputStream>
inline TOutputStream& operator<<(
  TOutputStream& stream, std::pair<basic::TermColor, basic::TermColor> colors)
{
  basic::TermColorManager::Set(colors.first, colors.second);
  return stream;
}

