#include "basic/log/table_printer.h"

#include <base/strings/string_number_conversions.h>
#include <base/strings/strcat.h>
#include <base/strings/string_util.h>

#include "testing/gtest/include/gtest/gtest.h"

#include <cstddef>
#include <sstream>
#include <string>

namespace basic {
namespace {

TEST(TablePrinterBuilder, SimpleTable) {
  TablePrinterBuilder builder;
  TablePrinter writer = builder
           .AddColumn(TablePrinter::Column{"ID1", 16})
           .AddColumn(TablePrinter::Column{"ID2", 16})
           .AddColumn(TablePrinter::Column{"ID3", 16})
           .AddColumn(TablePrinter::Column{"ID4", 16})
           .Build();
  for(int row = 0; row < 6; row++) {
    for(int col = 0; col < 4; col++) {
      std::string str = ::base::StrCat({"row(", base::NumberToString(row),
        ") col(", base::NumberToString(col), ")",});
      writer.SetElement(row, col, str);
    }
  }
  std::string expected =
    "ID1             ID2             ID3             ID4             \n\
row(0) col(0)   row(0) col(1)   row(0) col(2)   row(0) col(3)   \n\
row(1) col(0)   row(1) col(1)   row(1) col(2)   row(1) col(3)   \n\
row(2) col(0)   row(2) col(1)   row(2) col(2)   row(2) col(3)   \n\
row(3) col(0)   row(3) col(1)   row(3) col(2)   row(3) col(3)   \n\
row(4) col(0)   row(4) col(1)   row(4) col(2)   row(4) col(3)   \n\
row(5) col(0)   row(5) col(1)   row(5) col(2)   row(5) col(3)   \n";
  EXPECT_EQ(writer.ToString(), expected);
}

}  // namespace
}  // namespace basic
