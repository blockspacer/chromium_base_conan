list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "type_id.cc"
  "type_id.h"
  "value_conversions.cc"
  "value_conversions.h"
  "wasm_util.h"
  "wasm_closure.h"
  "stl_util.h"
  "spin_lock.cc"
  "spin_lock.h"
  "rvalue_cast.h"
  "recursion_checker.h"
  "output_parameter.h"
  "macros.h"
  "logging.h"
  "enum_to_int.h"
  "crc32.h"
  "crc32.cc"
  "compiler_specific.h"
  "basictypes.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "containers/bounded_inline_vector_impl.h"
  "containers/bounded_inline_vector.h"
  "containers/unique_any.h"
  "containers/unique_any.cc"
  "containers/any_internal.h"
  "containers/any_internal.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "hash/city_hash.h"
  "hash/city_hash.cc"
  "hash/murmurhash.h"
  "hash/murmurhash.cc"
  "hash/xxhash.h"
  "hash/xxhash.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "debug/leak_tracker.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "ranges/enumerated.h"
  "ranges/pipelined.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "synchronization/spin_wait.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "strings/substitute.h"
  "strings/substitute.cc"
  "strings/string_number_conversions.h"
  "strings/string_number_conversions.cc"
  "strings/string_format.h"
  "strings/string_util.h"
  "strings/string_util.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "annnotations/guard_annotations_unittest.cc"
)


list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "numerics/floating_point_comparison.h"
  "numerics/double_summation.h"
  "numerics/double_summation.cc"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "algorithm/top_n.h"
)

list(APPEND EXTENSIONS_SOURCES_UNPROCESSED
  "bit_field/bit_field.h"
)

list(TRANSFORM EXTENSIONS_SOURCES_UNPROCESSED PREPEND "../extensions/basic/")
list(APPEND COMPONENT_BASE_SOURCES ${EXTENSIONS_SOURCES_UNPROCESSED})
