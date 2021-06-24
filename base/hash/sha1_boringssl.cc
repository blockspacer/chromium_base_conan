// Copyright (c) 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/hash/sha1.h"

#include <stdint.h>

#include "base/strings/string_util.h"
#include "openssl/crypto.h"
#include "openssl/sha.h"

#include "openssl/ssl.h"

namespace base {

SHA1Digest SHA1HashSpan(span<const uint8_t> data) {
#if defined(ENABLE_BORINGSSL)
  CRYPTO_library_init();
#else
  SSL_library_init();
#endif // ENABLE_BORINGSSL
  SHA1Digest digest;
  SHA1(data.data(), data.size(), digest.data());
  return digest;
}

std::string SHA1HashString(const std::string& str) {
#if defined(ENABLE_BORINGSSL)
  CRYPTO_library_init();
#else
  SSL_library_init();
#endif // ENABLE_BORINGSSL
  std::string digest;
  SHA1(reinterpret_cast<const uint8_t*>(str.data()), str.size(),
       reinterpret_cast<uint8_t*>(WriteInto(&digest, kSHA1Length + 1)));
  return digest;
}

void SHA1HashBytes(const unsigned char* data, size_t len, unsigned char* hash) {
#if defined(ENABLE_BORINGSSL)
  CRYPTO_library_init();
#else
  SSL_library_init();
#endif // ENABLE_BORINGSSL
  SHA1(data, len, hash);
}

}  // namespace base
