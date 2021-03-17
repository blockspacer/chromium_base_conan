#include "basic/strings/string_format.h"
#include "basic/test/test_macros.h"

#include "testing/gtest/include/gtest/gtest.h"

#include "base/test/task_environment.h"
#include <base/logging.h>
#include <base/strings/utf_string_conversions.h>
#include <base/strings/string_util.h>
#include <base/strings/string16.h>
#include <base/macros.h>
#include <base/stl_util.h>

#include <iostream>

using namespace base;

class Date
{
public:
    Date(int year, int month, int day) : _year(year), _month(month), _day(day) {}

    friend std::ostream& operator<<(std::ostream& os, const Date& date)
    {
      return os << date._year << '-' << date._month << '-' << date._day;
    }

private:
    int _year, _month, _day;
};

struct S {
  double value;
};

std::ostream& operator<<(std::ostream& os, S s) {
  return os << s.value;
}

#define SHOW(expression) LOG(INFO) << #expression << " = \"" << expression << "\"";

namespace basic {

class StringFormatDemo : public testing::Test {
 protected:
  base::test::TaskEnvironment task_environment;
};

TEST_F(StringFormatDemo, Simple) {
  using namespace fmt::literals;

  // base::fmt("no arguments") = "no arguments"
  SHOW(base::fmt("no arguments"));

  // base::fmt("{0}, {1}, {2}", -1, 0, 1) = "-1, 0, 1"
  SHOW(base::fmt("{0}, {1}, {2}", -1, 0, 1));

  // base::fmt("{0}, {1}, {2}", 'a', 'b', 'c') = "a, b, c"
  SHOW(base::fmt("{0}, {1}, {2}", 'a', 'b', 'c'));

  // base::fmt("{}, {}, {}", 'a', 'b', 'c') = "a, b, c"
  SHOW(base::fmt("{}, {}, {}", 'a', 'b', 'c'));

  // base::fmt("{2}, {1}, {0}", 'a', 'b', 'c') = "c, b, a"
  SHOW(base::fmt("{2}, {1}, {0}", 'a', 'b', 'c'));

  // base::fmt("{0}{1}{0}", "abra", "cad") = "abracadabra"
  SHOW(base::fmt("{0}{1}{0}", "abra", "cad"));

  // base::fmt("{:<30}", "left aligned") = "left aligned                  "
  SHOW(base::fmt("{:<30}", "left aligned"));

  // base::fmt("{:>30}", "right aligned") = "                 right aligned"
  SHOW(base::fmt("{:>30}", "right aligned"));

  // base::fmt("{:^30}", "centered") = "           centered           "
  SHOW(base::fmt("{:^30}", "centered"));

  // base::fmt("{:*^30}", "centered") = "***********centered***********"
  SHOW(base::fmt("{:*^30}", "centered"));

  // base::fmt("{:+f}; {:+f}", 3.14, -3.14) = "+3.140000; -3.140000"
  SHOW(base::fmt("{:+f}; {:+f}", 3.14, -3.14));

  // base::fmt("{: f}; {: f}", 3.14, -3.14) = " 3.140000; -3.140000"
  SHOW(base::fmt("{: f}; {: f}", 3.14, -3.14));

  // base::fmt("{:-f}; {:-f}", 3.14, -3.14) = "3.140000; -3.140000"
  SHOW(base::fmt("{:-f}; {:-f}", 3.14, -3.14));

  // base::fmt("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42) = "int: 42;  hex: 2a;  oct: 52; bin: 101010"
  SHOW(base::fmt("int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42));

  // base::fmt("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42) = "int: 42;  hex: 0x2a;  oct: 052;  bin: 0b101010"
  SHOW(base::fmt("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42));

  // base::fmt("The date is {}", Date(2012, 12, 9)) = "The date is 2012-12-9"
  SHOW(base::fmt("The date is {}", Date(2012, 12, 9)));

  // base::fmt("Elapsed time: {s:.2f} seconds", "s"_a = 1.23) = "Elapsed time: 1.23 seconds"
  SHOW(base::fmt("Elapsed time: {s:.2f} seconds", "s"_a = 1.23));

  // "The answer is {}"_format(42) = "The answer is 42"
  SHOW("The answer is {}"_format(42));

  // ┌────────────────────┐
  // │    Привет, мир!    │
  // └────────────────────┘
  SHOW(base::fmt(u8"┌{0:─^{2}}┐\n"
                  "│{1: ^{2}}│\n"
                  "└{0:─^{2}}┘\n", "", u8"Привет, мир!", 20));

  // 0,42
  SHOW(::fmt::format(std::locale("fr_FR.UTF-8"), "{}", S{0.42}));

  {
    // Привет мир! -1, 0, 1
    std::wstring hello_world = base::UTF8ToWide(u8"\u041F\u0440\u0438\u0432\u0435\u0442 {0}, {1}, {2}, {3}");
    SHOW(base::fmt(hello_world, base::UTF8ToWide(u8"\u043C\u0438\u0440!"), -1, 0, 1));
  }

  {
    // Привет мир! -1, 0, 1
    base::string16 hello_world = base::UTF8ToUTF16(u8"\u041F\u0440\u0438\u0432\u0435\u0442 {0}, {1}, {2}, {3}");
    SHOW(base::fmt(hello_world, base::UTF8ToUTF16(u8"\u043C\u0438\u0440!"), -1, 0, 1));
  }
}

} // namespace basic
