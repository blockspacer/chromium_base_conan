#include "basic/term_color/term_color.h"

#include "base/notreached.h"

#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_APPLE)
#include <cstdio>
#endif

#if defined(OS_WINDOWS)
#include <windows.h>
#endif

namespace basic {

void TermColorManager::Set(TermColor color, TermColor background)
{
#if defined(OS_LINUX) || defined(OS_CHROMEOS) || defined(OS_APPLE)
  const char* colors[] =
  {
    "\033[22;30m",  // Black color
    "\033[22;34m",  // Blue color
    "\033[22;32m",  // Green color
    "\033[22;36m",  // Cyan color
    "\033[22;31m",  // Red color
    "\033[22;35m",  // Magenta color
    "\033[22;33m",  // Brown color
    "\033[22;37m",  // Grey color
    "\033[01;30m",  // Dark grey color
    "\033[01;34m",  // Light blue color
    "\033[01;32m",  // Light green color
    "\033[01;36m",  // Light cyan color
    "\033[01;31m",  // Light red color
    "\033[01;35m",  // Light magenta color
    "\033[01;33m",  // Yellow color
    "\033[01;37m"   // White color
  };
  const char* backgrounds[] =
  {
    "\033[00000m",  // Black color
    "\033[02;44m",  // Blue color
    "\033[02;42m",  // Green color
    "\033[02;46m",  // Cyan color
    "\033[02;41m",  // Red color
    "\033[02;45m",  // Magenta color
    "\033[02;43m",  // Brown color
    "\033[02;47m",  // Grey color
    "\033[00;40m",  // Dark grey color
    "\033[00;44m",  // Light blue color
    "\033[00;42m",  // Light green color
    "\033[00;46m",  // Light cyan color
    "\033[00;41m",  // Light red color
    "\033[00;45m",  // Light magenta color
    "\033[00;43m",  // Yellow color
    "\033[00;47m"   // White color
  };
  std::fwrite(backgrounds[(int)background - (int)TermColor::BLACK], 1, 8, stdout);
  std::fwrite(colors[(int)color - (int)TermColor::BLACK], 1, 8, stdout);
#elif defined(OS_WINDOWS)
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, (((WORD)color) & 0x0F) + ((((WORD)background) & 0x0F) << 4));
#else
  NOTIMPLEMENTED();
#endif
}

} // namespace basic
