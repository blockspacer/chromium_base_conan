// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/threading/thread_local_storage.h"

#include "base/logging.h"

namespace base {

namespace internal {

bool PlatformThreadLocalStorage::AllocTLS(TLSKey* key) {
#if defined(DISABLE_PTHREADS) || defined(USE_FAKE_THREAD_LS)
  // see https://github.com/save7502/youkyoung/blob/master/Engine/Source/Runtime/Core/Public/HTML5/HTML5PlatformTLS.h
  //GetFakeTLSArray().push_back(0);
  *key = GetFakeTLSArray().size() + 1;
  GetFakeTLSArray()[*key] = 0;
  return true; // TODO
#else
  return !pthread_key_create(key,
      base::internal::PlatformThreadLocalStorage::OnThreadExit);
#endif
}

void PlatformThreadLocalStorage::FreeTLS(TLSKey key) {
#if defined(DISABLE_PTHREADS) || defined(USE_FAKE_THREAD_LS)
  // see https://github.com/save7502/youkyoung/blob/master/Engine/Source/Runtime/Core/Public/HTML5/HTML5PlatformTLS.h
  // see https://github.com/dhustkoder/Torque2DGameTest/blob/master/engine/source/platformEmscripten/EmscriptenThread.cpp

  // nothing to do, just grow the array forever
  return;
#else
  int ret = pthread_key_delete(key);
  DCHECK_EQ(ret, 0);
#endif
}

void PlatformThreadLocalStorage::SetTLSValue(TLSKey key, void* value) {
#if defined(DISABLE_PTHREADS) || defined(USE_FAKE_THREAD_LS)
  // see https://github.com/save7502/youkyoung/blob/master/Engine/Source/Runtime/Core/Public/HTML5/HTML5PlatformTLS.h
  //DCHECK_LT(key, GetFakeTLSArray().size());
  GetFakeTLSArray()[key] = value;
#else
  int ret = pthread_setspecific(key, value);
  DCHECK_EQ(ret, 0);
#endif
}

}  // namespace internal

}  // namespace base
