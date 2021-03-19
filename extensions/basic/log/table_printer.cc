#include "basic/log/table_printer.h" // IWYU pragma: associated

#include <base/strings/strcat.h>

#include <cstddef>
#include <iostream>
#include <utility>
#include <iomanip>

namespace basic {

TablePrinter::TablePrinter() = default;

TablePrinter::TablePrinter(const TablePrinter& other) = default;

TablePrinter::~TablePrinter() = default;

TablePrinter::Column::Column(std::string title, int width)
    : title(title), width(width) {}

TablePrinter::Column::Column(const Column& other) = default;

TablePrinter::Column::~Column() = default;

void TablePrinter::SetElement(size_t row, size_t col,
                             base::StringPiece element) {
  if (elements_.size() <= row) {
    elements_.resize(row + 1);
  }
  if (elements_[row].size() <= col) {
    DCHECK_GE(heads_.size(), col);
    elements_[row].resize(heads_.size());
  }

  elements_[row][col] = std::string(element);
}

std::string TablePrinter::ToString(const bool with_heads) const {
  std::stringstream ss;
  if(with_heads) {
    for (auto& head : heads_) {
      ss << std::left << std::setw(head.width) << head.title;
    }
    ss << "\n";
  }

  for (auto& row : elements_) {
    size_t idx = 0;
    for (auto& element : row) {
      std::string content;
      if (element.length() > heads_[idx].width - 1) {
        if (heads_[idx].width > 4) {
          content =
              base::StrCat({element.substr(0, heads_[idx].width - 4), "..."});
        } else {
          DLOG(WARNING) << "Maybe you should set enough header width... "
                        << heads_[idx].title << "(" << heads_[idx].width << ")";
          content = element.substr(0, heads_[idx].width - 1);
        }
      } else {
        content = element;
      }

      ss << std::left << std::setw(heads_[idx].width) << content;
      idx++;
    }
    ss << "\n";
  }

  return ss.str();
}

TablePrinterBuilder::TablePrinterBuilder() = default;

TablePrinterBuilder::~TablePrinterBuilder() = default;

TablePrinterBuilder& TablePrinterBuilder::AddColumn(
    const TablePrinter::Column& column) {
  writer_.heads_.push_back(column);
  return *this;
}

TablePrinter TablePrinterBuilder::Build() const { return writer_; }

}  // namespace basic
