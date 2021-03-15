# NOTE (chromium_base_conan-specific): boringssl not supported, use openssl instead
remove_from_list(
  CHECK_EXISTS TRUE
  INPUT ${COMPONENT_BASE_SOURCES}
  OUTPUT COMPONENT_BASE_SOURCES
  ITEMS
  "hash/md5_boringssl.cc"
  "hash/md5_boringssl.h"
  "hash/sha1_boringssl.cc")
