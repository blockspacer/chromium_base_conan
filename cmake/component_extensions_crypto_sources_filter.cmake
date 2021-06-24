#

if(NOT TARGET_MACOS AND NOT TARGET_IOS)
  # TODO
  # remove_from_list(
  #   CHECK_EXISTS TRUE
  #   INPUT ${COMPONENT_CRYPTO_SOURCES}
  #   OUTPUT COMPONENT_CRYPTO_SOURCES
  #   ITEMS
  #   "apple_keychain.h"
  #   "mock_apple_keychain.cc"
  #   "mock_apple_keychain.h"
  # )
endif()

if(NOT TARGET_MACOS)
  # TODO
  # remove_from_list(
  #   CHECK_EXISTS TRUE
  #   INPUT ${COMPONENT_CRYPTO_SOURCES}
  #   OUTPUT COMPONENT_CRYPTO_SOURCES
  #   ITEMS
  #   "cssm_init.cc"
  #   "cssm_init.h"
  #   "mac_security_services_lock.cc"
  #   "mac_security_services_lock.h"
  # )
endif()

if(NOT TARGET_WINDOWS)
  # TODO
  # remove_from_list(
  #   CHECK_EXISTS TRUE
  #   INPUT ${COMPONENT_CRYPTO_SOURCES}
  #   OUTPUT COMPONENT_CRYPTO_SOURCES
  #   ITEMS
  #   "capi_util.cc"
  #   "capi_util.h")
endif()

if(NOT USE_NSS_CERTS)
  # TODO
  # remove_from_list(
  #   CHECK_EXISTS TRUE
  #   INPUT ${COMPONENT_CRYPTO_SOURCES}
  #   OUTPUT COMPONENT_CRYPTO_SOURCES
  #   ITEMS
  #   "nss_key_util.cc"
  #   "nss_key_util.h"
  #   "nss_util.cc"
  #   "nss_util.h"
  #   "nss_util_internal.h")
endif()
