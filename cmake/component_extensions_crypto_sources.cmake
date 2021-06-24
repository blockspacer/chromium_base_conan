list(APPEND COMPONENT_CRYPTO_SOURCES
  # TODO
  # "crypto_export.h"
  # "hmac.cc"
  # "hmac.h"
  # "secure_hash.cc"
  # "secure_hash.h"
  # "secure_util.cc"
  # "secure_util.h"
  # "sha2.cc"
  # "sha2.h"
  # "symmetric_key.cc"
  # "symmetric_key.h"
  # "random.cc"
  # "random.h"
  # "openssl_util.cc"
  # "openssl_util.h"
  # "p224.cc"
  # "p224.h"
  # "p224_spake.cc"
  # "p224_spake.h"
  # "rsa_private_key.cc"
  # "rsa_private_key.h"

  # TODO
  # "aead.cc"
  # "aead.h"
  # "curve25519.cc"
  # "curve25519.h"
  # "ec_private_key.cc"
  # "ec_private_key.h"
  # "ec_signature_creator.cc"
  # "ec_signature_creator.h"
  # "ec_signature_creator_impl.cc"
  # "ec_signature_creator_impl.h"
  # "encryptor.cc"
  # "encryptor.h"
  # "hkdf.cc"
  # "hkdf.h"
  # "hmac.cc"
  # "hmac.h"
  # "rsa_private_key.cc"
  # "rsa_private_key.h"
  # "openssl_bio_string.cc"
  # "openssl_bio_string.h"
  # "signature_creator.cc"
  # "signature_creator.h"
  # "signature_verifier.cc"
  # "signature_verifier.h"

  "auto_cbb.h"
  "crypto_export.h"

  "openssl_util.cc"
  "openssl_util.h"
  "p224.cc"
  "p224.h"
  "p224_spake.cc"
  "p224_spake.h"
  "random.cc"
  "random.h"
  "secure_hash.cc"
  "secure_hash.h"
  "secure_util.cc"
  "secure_util.h"
  "sha2.cc"
  "sha2.h"
  "symmetric_key.cc"
  "symmetric_key.h"
)

if (TARGET_APPLE)
  list(APPEND COMPONENT_CRYPTO_SOURCES
    "apple_keychain.h"
    "mock_apple_keychain.cc"
    "mock_apple_keychain.h"
  )
  list(APPEND COMPONENT_CRYPTO_SOURCES
    "cssm_init.cc"
    "cssm_init.h"
    "mac_security_services_lock.cc"
    "mac_security_services_lock.h"
  )
endif()

if (TARGET_MACOS)
  list(APPEND COMPONENT_CRYPTO_SOURCES
    "apple_keychain_mac.mm"
    "mock_apple_keychain_mac.cc"
  )
endif()

if (TARGET_IOS)
  list(APPEND COMPONENT_CRYPTO_SOURCES
    "apple_keychain_ios.mm"
    "mock_apple_keychain_ios.cc"
  )
endif()

if (TARGET_WINDOWS)
  list(APPEND COMPONENT_CRYPTO_SOURCES
    "capi_util.cc"
    "capi_util.h"
    "scoped_capi_types.h"
  )
endif()

if (USE_NSS_CERTS)
  list(APPEND COMPONENT_CRYPTO_SOURCES
    "nss_key_util.cc"
    "nss_key_util.h"
    "nss_util.cc"
    "nss_util.h"
    "nss_util_internal.h"
    "scoped_nss_types.h"
  )
endif()

if (USE_OPENSSL)
  list(APPEND BASE_DEFINES
    USE_OPENSSL
  )
endif()

if (USE_NSS_CERTS)
  list(APPEND BASE_DEFINES
    USE_NSS_CERTS
  )
endif()

list(APPEND BASE_PRIVATE_DEFINES
  CRYPTO_IMPLEMENTATION=1
)
