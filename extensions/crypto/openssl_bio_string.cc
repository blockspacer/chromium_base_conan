// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "crypto/openssl_bio_string.h"

#include <openssl/bio.h>
#include <string.h>

#if OPENSSL_VERSION_NUMBER < 0x10100000L

void BIO_set_data(BIO* a, void* ptr) { a->ptr = ptr; }

void* BIO_get_data(BIO* a) { return a ? a->ptr : nullptr; }

void BIO_set_init(BIO* a, int init) { a->init = init; }

int BIO_get_init(BIO* a) { return a->init; }

void BIO_set_shutdown(BIO* a, int shut) { a->shutdown = shut; }

#endif

namespace crypto {

namespace {

int bio_string_write(BIO* bio, const char* data, int len) {
  reinterpret_cast<std::string*>(BIO_get_data(bio))->append(data, len);
  return len;
}

int bio_string_puts(BIO* bio, const char* data) {
  // Note: unlike puts(), BIO_puts does not add a newline.
  return bio_string_write(bio, data, strlen(data));
}

long bio_string_ctrl(BIO* bio, int cmd, long num, void* ptr) {
  std::string* str = reinterpret_cast<std::string*>(BIO_get_data(bio));
  switch (cmd) {
    case BIO_CTRL_RESET:
      str->clear();
      return 1;
    case BIO_C_FILE_SEEK:
      return -1;
    case BIO_C_FILE_TELL:
      return str->size();
    case BIO_CTRL_FLUSH:
      return 1;
    default:
      return 0;
  }
}

int bio_string_new(BIO* bio) {

  // By default do not close underlying stream on shutdown.
  // BIO_set_shutdown(bio, 0);

  BIO_set_data(bio, nullptr);
  BIO_set_init(bio, 0);
  return 1;
}

int bio_string_free(BIO* bio) {
  // The string is owned by the caller, so there's nothing to do here.
  return bio != NULL;
}

#if OPENSSL_VERSION_NUMBER < 0x10100000L

BIO_METHOD* stream_get_method() {
  static BIO_METHOD stream_method = {
      0x7F |
          BIO_TYPE_SOURCE_SINK,  // type: 0x7F is an arbitrary unused type ID.
      "bio_string",              // name
      bio_string_write,          // write function
      nullptr,                   // read function
      bio_string_puts,           // puts function
      nullptr,                   // gets function
      bio_string_ctrl,           // control function
      bio_string_new,            // creation
      bio_string_free,           // free
      nullptr,                   // callback function
  };

  return &stream_method;
}

#else

BIO_METHOD* stream_get_method() {
  static BIO_METHOD* stream_method;

  if (!stream_method) {
    stream_method = BIO_meth_new(0x7F | BIO_TYPE_SOURCE_SINK, "bio_string");
    BIO_meth_set_write(stream_method, bio_string_write);
    BIO_meth_set_puts(stream_method, bio_string_puts);
    BIO_meth_set_ctrl(stream_method, bio_string_ctrl);
    BIO_meth_set_create(stream_method, bio_string_free);
    BIO_meth_set_destroy(stream_method, bio_string_free);
  }

  return stream_method;
}

#endif

}  // namespace

BIO* BIO_new_string(std::string* out) {
  BIO* bio = BIO_new(stream_get_method());
  if (!bio)
    return bio;
  BIO_set_data(bio, out);
  BIO_set_init(bio, 1);
  return bio;
}

}  // namespace crypto
