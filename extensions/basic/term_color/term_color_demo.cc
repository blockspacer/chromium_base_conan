/*!
    \file system_console.cpp
    \brief Console management example
    \author Ivan Shynkarenka
    \date 27.07.2016
    \copyright MIT License
*/

#include "basic/term_color/term_color.h"

#include <iostream>
#include <iomanip>

int main(int argc, char** argv)
{
  for (int i = (int)basic::Color::BLACK; i <= (int)basic::Color::WHITE; ++i)
  {
    for (int j = (int)basic::Color::BLACK; j <= (int)basic::Color::WHITE; ++j)
    {
      std::cout << std::make_pair((basic::Color)i, (basic::Color)j);
      std::cout << " ";
      std::cout << std::setfill('0') << std::setw(2) << i;
      std::cout << " / ";
      std::cout << std::setfill('0') << std::setw(2) << j;
      std::cout << " ";
      basic::TermColorManager::Set(basic::Color::WHITE, basic::Color::BLACK);
    }
    std::cout << std::endl;
  }
  return 0;
}
