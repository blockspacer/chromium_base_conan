// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "crypto/signature_verifier.h"

#include <cryptohi.h>
#include <keyhi.h>
#include <pk11pub.h>
#include <secerr.h>
#include <sechash.h>
#include <stdint.h>
#include <stdlib.h>

#include "base/logging.h"
#include "crypto/nss_util.h"
#include "crypto/third_party/nss/chromium-nss.h"

namespace crypto {

namespace {

HASH_HashType ToNSSHashType(SignatureVerifier::HashAlgorithm hash_alg) {
  switch (hash_alg) {
    case SignatureVerifier::SHA1:
      return HASH_AlgSHA1;
    case SignatureVerifier::SHA256:
      return HASH_AlgSHA256;
  }
  return HASH_AlgNULL;
}

SECOidTag ToNSSSignatureType(SignatureVerifier::SignatureAlgorithm sig_alg) {
  switch (sig_alg) {
    case SignatureVerifier::RSA_PKCS1_SHA1:
      return SEC_OID_PKCS1_SHA1_WITH_RSA_ENCRYPTION;
    case SignatureVerifier::RSA_PKCS1_SHA256:
      return SEC_OID_PKCS1_SHA256_WITH_RSA_ENCRYPTION;
    case SignatureVerifier::ECDSA_SHA256:
      return SEC_OID_ANSIX962_ECDSA_SHA256_SIGNATURE;
  }
  return SEC_OID_UNKNOWN;
}

SECStatus VerifyRSAPSS_End(SECKEYPublicKey* public_key,
                           HASHContext* hash_context,
                           HASH_HashType mask_hash_alg,
                           unsigned int salt_len,
                           const unsigned char* signature,
                           unsigned int signature_len) {
  unsigned int hash_len = HASH_ResultLenContext(hash_context);
  std::vector<unsigned char> hash(hash_len);
  HASH_End(hash_context, &hash[0], &hash_len, hash.size());

  unsigned int modulus_len = SECKEY_PublicKeyStrength(public_key);
  if (signature_len != modulus_len) {
    PORT_SetError(SEC_ERROR_BAD_SIGNATURE);
    return SECFailure;
  }
  std::vector<unsigned char> enc(signature_len);
  SECStatus rv = PK11_PubEncryptRaw(public_key, &enc[0],
                                    const_cast<unsigned char*>(signature),
                                    signature_len, NULL);
  if (rv != SECSuccess) {
    LOG(WARNING) << "PK11_PubEncryptRaw failed";
    return rv;
  }
  return emsa_pss_verify(&hash[0], &enc[0], enc.size(),
                         HASH_GetType(hash_context), mask_hash_alg,
                         salt_len);
}

}  // namespace

SignatureVerifier::SignatureVerifier()
    : vfy_context_(NULL),
      hash_alg_(SHA1),
      mask_hash_alg_(SHA1),
      salt_len_(0),
      public_key_(NULL),
      hash_context_(NULL) {
  EnsureNSSInit();
}

SignatureVerifier::~SignatureVerifier() {
  Reset();
}

bool SignatureVerifier::VerifyInit(SignatureAlgorithm signature_algorithm,
                                   const uint8_t* signature,
                                   int signature_len,
                                   const uint8_t* public_key_info,
                                   int public_key_info_len) {
  if (vfy_context_ || hash_context_)
    return false;

  signature_.assign(signature, signature + signature_len);

  SECKEYPublicKey* public_key = DecodePublicKeyInfo(public_key_info,
                                                    public_key_info_len);
  if (!public_key)
    return false;

  SECItem sig;
  sig.type = siBuffer;
  sig.data = const_cast<uint8_t*>(signature);
  sig.len = signature_len;
  vfy_context_ = VFY_CreateContext(
      public_key, &sig, ToNSSSignatureType(signature_algorithm), nullptr);
  SECKEY_DestroyPublicKey(public_key);  // Done with public_key.
  if (!vfy_context_) {
    // A corrupted RSA signature could be detected without the data, so
    // VFY_CreateContextWithAlgorithmID may fail with SEC_ERROR_BAD_SIGNATURE
    // (-8182).
    return false;
  }

  if (VFY_Begin(vfy_context_) != SECSuccess) {
    NOTREACHED();
    return false;
  }
  return true;
}

bool SignatureVerifier::VerifyInitRSAPSS(HashAlgorithm hash_alg,
                                         HashAlgorithm mask_hash_alg,
                                         int salt_len,
                                         const uint8_t* signature,
                                         int signature_len,
                                         const uint8_t* public_key_info,
                                         int public_key_info_len) {
  if (vfy_context_ || hash_context_)
    return false;

  signature_.assign(signature, signature + signature_len);

  SECKEYPublicKey* public_key = DecodePublicKeyInfo(public_key_info,
                                                    public_key_info_len);
  if (!public_key)
    return false;

  public_key_ = public_key;
  hash_alg_ = hash_alg;
  mask_hash_alg_ = mask_hash_alg;
  salt_len_ = salt_len;
  hash_context_ = HASH_Create(ToNSSHashType(hash_alg_));
  if (!hash_context_)
    return false;
  HASH_Begin(hash_context_);
  return true;
}

void SignatureVerifier::VerifyUpdate(const uint8_t* data_part,
                                     int data_part_len) {
  if (vfy_context_) {
    SECStatus rv = VFY_Update(vfy_context_, data_part, data_part_len);
    DCHECK_EQ(SECSuccess, rv);
  } else {
    HASH_Update(hash_context_, data_part, data_part_len);
  }
}

bool SignatureVerifier::VerifyFinal() {
  SECStatus rv;
  if (vfy_context_) {
    rv = VFY_End(vfy_context_);
  } else {
    rv = VerifyRSAPSS_End(public_key_, hash_context_,
                          ToNSSHashType(mask_hash_alg_), salt_len_,
                          signature_.data(),
                          signature_.size());
  }
  Reset();

  // If signature verification fails, the error code is
  // SEC_ERROR_BAD_SIGNATURE (-8182).
  return (rv == SECSuccess);
}

// static
SECKEYPublicKey* SignatureVerifier::DecodePublicKeyInfo(
    const uint8_t* public_key_info,
    int public_key_info_len) {
  CERTSubjectPublicKeyInfo* spki = NULL;
  SECItem spki_der;
  spki_der.type = siBuffer;
  spki_der.data = const_cast<uint8_t*>(public_key_info);
  spki_der.len = public_key_info_len;
  spki = SECKEY_DecodeDERSubjectPublicKeyInfo(&spki_der);
  if (!spki)
    return NULL;
  SECKEYPublicKey* public_key = SECKEY_ExtractPublicKey(spki);
  SECKEY_DestroySubjectPublicKeyInfo(spki);  // Done with spki.
  return public_key;
}

void SignatureVerifier::Reset() {
  if (vfy_context_) {
    VFY_DestroyContext(vfy_context_, PR_TRUE);
    vfy_context_ = NULL;
  }
  if (hash_context_) {
    HASH_Destroy(hash_context_);
    hash_context_ = NULL;
  }
  if (public_key_) {
    SECKEY_DestroyPublicKey(public_key_);
    public_key_ = NULL;
  }
  signature_.clear();
}

}  // namespace crypto
