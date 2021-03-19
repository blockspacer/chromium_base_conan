// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" basic,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "basic/log/spacer.h" // IWYU pragma: associated

#include <cstddef>
#include <iostream>

namespace basic {

std::ostream& operator<<(std::ostream& stream, const Spacer& spacer) {
  for (size_t i = 0; i < spacer.repeat; ++i) {
    stream << spacer.repeated_char;
  }
  return stream;
}

}  // namespace basic
