// Copyright 2020 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "basic/secure_clear/secure_string.h"

#include <openssl/crypto.h>

#include <basic/portability/portability.h>

namespace basic {

NO_SANITIZE("address") void SecureClearBytes(void* v, size_t n) {
  OPENSSL_cleanse(v, n);
}

int SecureMemcmp(const void* s1, const void* s2, size_t n) {
  return CRYPTO_memcmp(s1, s2, n);
}

}  // namespace basic
