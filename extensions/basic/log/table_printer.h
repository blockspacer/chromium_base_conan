#pragma once

#include <cstddef>
#include <iosfwd>

#include <base/logging.h>
#include <base/strings/string_util.h>

namespace basic {

class TablePrinter {
 public:
  TablePrinter(const TablePrinter& other);
  ~TablePrinter();

  struct Column {
    Column(std::string title, int width);
    Column(const Column& other);
    ~Column();

    std::string title;
    size_t width = 16;
  };

  void SetElement(size_t row, size_t col, base::StringPiece element);
  std::string ToString(const bool with_heads = true) const;

 private:
  friend class TablePrinterBuilder;
  TablePrinter();

  std::vector<Column> heads_;
  std::vector<std::vector<std::string>> elements_;
};

class TablePrinterBuilder {
 public:
  TablePrinterBuilder();
  ~TablePrinterBuilder();

  TablePrinterBuilder& AddColumn(const TablePrinter::Column& column);

  TablePrinter Build() const;

 private:
  TablePrinter writer_;

  DISALLOW_COPY_AND_ASSIGN(TablePrinterBuilder);
};

}  // namespace basic
