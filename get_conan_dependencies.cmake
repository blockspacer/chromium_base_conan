if(EXISTS "${CURRENT_SCRIPT_DIR}/.tmp")
  cmake_remove_directory("${CURRENT_SCRIPT_DIR}/.tmp")
endif()

cmake_make_dir("${CURRENT_SCRIPT_DIR}/.tmp")

# conan_build_helper

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_build_helper")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_build_helper"
      "http://github.com/blockspacer/conan_build_helper.git"
      "")
endif()
conan_build_target_if(
  "conan_build_helper" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_build_helper" # target to build
  ALWAYS_BUILD
  "")

# cmake_platform_detection_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/cmake_platform_detection_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/cmake_platform_detection_conan"
      "http://github.com/blockspacer/cmake_platform_detection_conan.git"
      "")
endif()
conan_build_target_if(
  "cmake_platform_detection" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/cmake_platform_detection_conan" # target to build
  ALWAYS_BUILD
  "")

# cmake_build_options_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/cmake_build_options_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/cmake_build_options_conan"
      "http://github.com/blockspacer/cmake_build_options_conan.git"
      "")
endif()
conan_build_target_if(
  "cmake_build_options" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/cmake_build_options_conan" # target to build
  ALWAYS_BUILD
  "")

# cmake_helper_utils_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/cmake_helper_utils_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/cmake_helper_utils_conan"
      "http://github.com/blockspacer/cmake_helper_utils_conan.git"
      "")
endif()
conan_build_target_if(
  "cmake_helper_utils" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/cmake_helper_utils_conan" # target to build
  ALWAYS_BUILD
  "")

# cmake_sanitizers_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/cmake_sanitizers_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/cmake_sanitizers_conan"
      "http://github.com/blockspacer/cmake_sanitizers_conan.git"
      "")
endif()
conan_build_target_if(
  "cmake_sanitizers" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/cmake_sanitizers_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_build_util_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_build_util_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_build_util_conan"
      "http://github.com/blockspacer/chromium_build_util_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_build_util" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_build_util_conan" # target to build
  ALWAYS_BUILD
  "")

# conan_gtest

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_gtest")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_gtest"
      "http://github.com/blockspacer/conan_gtest.git"
      "")
endif()
conan_build_target_if(
  "conan_gtest" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_gtest" # target to build
  ALWAYS_BUILD
  "")

# conan_abseil

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_abseil")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_abseil"
      "http://github.com/blockspacer/conan_abseil.git"
      "")
endif()
conan_build_target_if(
  "conan_abseil" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_abseil" # target to build
  ALWAYS_BUILD
  "")

# conan_google_benchmark

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_google_benchmark")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_google_benchmark"
      "http://github.com/blockspacer/conan_google_benchmark.git"
      "")
endif()
conan_build_target_if(
  "conan_google_benchmark" # target to clean
  "dev/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_google_benchmark" # target to build
  ALWAYS_BUILD
  "")

# conan_fmtlib

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_fmtlib")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_fmtlib"
      "https://github.com/blockspacer/conan_fmtlib.git"
      "")
endif()
conan_build_target_if(
  "conan_fmtlib" # target to clean
  "dev/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_fmtlib" # target to build
  ALWAYS_BUILD
  "")

# conan_zlib

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_zlib")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_zlib"
      "http://github.com/blockspacer/conan_zlib.git"
      "")
endif()
conan_build_target_if(
  "zlib" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_zlib" # target to build
  ALWAYS_BUILD
  "")

# conan_openssl

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_openssl")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_openssl"
      "http://github.com/blockspacer/conan_openssl.git"
      "")
endif()
conan_build_target_if(
  "openssl" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_openssl" # target to build
  ALWAYS_BUILD
  "")

# conan_libevent

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_libevent")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_libevent"
      "http://github.com/blockspacer/conan_libevent.git"
      "")
endif()
conan_build_target_if(
  "libevent" # target to clean
  "dev/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_libevent" # target to build
  ALWAYS_BUILD
  "")

# chromium_libevent_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_libevent_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_libevent_conan"
      "http://github.com/blockspacer/chromium_libevent_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_libevent" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_libevent_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_dynamic_annotations_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_dynamic_annotations_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_dynamic_annotations_conan"
      "http://github.com/blockspacer/chromium_dynamic_annotations_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_dynamic_annotations" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_dynamic_annotations_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_tcmalloc_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_tcmalloc_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_tcmalloc_conan"
      "http://github.com/blockspacer/chromium_tcmalloc_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_tcmalloc" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_tcmalloc_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_xdg_user_dirs_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_xdg_user_dirs_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_xdg_user_dirs_conan"
      "http://github.com/blockspacer/chromium_xdg_user_dirs_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_xdg_user_dirs" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_xdg_user_dirs_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_xdg_mime_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_xdg_mime_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_xdg_mime_conan"
      "http://github.com/blockspacer/chromium_xdg_mime_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_xdg_mime" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_xdg_mime_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_modp_b64_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_modp_b64_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_modp_b64_conan"
      "http://github.com/blockspacer/chromium_modp_b64_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_modp_b64" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_modp_b64_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_icu_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_icu_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_icu_conan"
      "http://github.com/blockspacer/chromium_icu_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_icu" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_icu_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_compact_enc_det_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_compact_enc_det_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_compact_enc_det_conan"
      "http://github.com/blockspacer/chromium_compact_enc_det_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_compact_enc_det" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_compact_enc_det_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_zlib_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_zlib_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_zlib_conan"
      "http://github.com/blockspacer/chromium_zlib_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_zlib" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_zlib_conan" # target to build
  ALWAYS_BUILD
  "")

# chromium_libxml_conan

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/chromium_libxml_conan")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/chromium_libxml_conan"
      "http://github.com/blockspacer/chromium_libxml_conan.git"
      "")
endif()
conan_build_target_if(
  "chromium_libxml" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/chromium_libxml_conan" # target to build
  ALWAYS_BUILD
  "")

# conan_bzip2

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_bzip2")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_bzip2"
      "http://github.com/blockspacer/conan_bzip2.git"
      "")
endif()
conan_build_target_if(
  "bzip2" # target to clean
  "dev/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_bzip2" # target to build
  ALWAYS_BUILD
  "")

# conan_protobuf

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_protobuf")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_protobuf"
      "https://github.com/blockspacer/conan_protobuf.git"
      "")
endif()
conan_build_target_if(
  "protobuf" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_protobuf" # target to build
  ALWAYS_BUILD
  "")

# conan_google_gn

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_google_gn")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_google_gn"
      "http://github.com/blockspacer/conan_google_gn.git"
      "")
endif()
conan_build_target_if(
  "google_gn" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_google_gn" # target to build
  ALWAYS_BUILD
  "")

# conan_perfetto

if(NOT EXISTS "${CURRENT_SCRIPT_DIR}/.tmp/conan_perfetto")
  git_clone("${CURRENT_SCRIPT_DIR}/.tmp/conan_perfetto"
      "http://github.com/blockspacer/conan_perfetto.git"
      "")
endif()
conan_build_target_if(
  "perfetto" # target to clean
  "conan/stable"
  "${CURRENT_SCRIPT_DIR}/.tmp/conan_perfetto" # target to build
  ALWAYS_BUILD
  "")
