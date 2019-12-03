// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/files/file_tracing.h"

#include "base/atomicops.h"
#include "base/files/file.h"

using base::subtle::AtomicWord;

namespace base {

namespace {
AtomicWord g_provider;
}

FileTracing::Provider* GetProvider() {
  AtomicWord provider = base::subtle::Acquire_Load(&g_provider);
  return reinterpret_cast<FileTracing::Provider*>(provider);
}

// static
bool FileTracing::IsCategoryEnabled() {
#if !defined(OS_EMSCRIPTEN)
  return false;
#else
  FileTracing::Provider* provider = GetProvider();
  return provider && provider->FileTracingCategoryIsEnabled();
#endif
}

// static
void FileTracing::SetProvider(FileTracing::Provider* provider) {
  base::subtle::Release_Store(&g_provider,
                              reinterpret_cast<AtomicWord>(provider));
}

FileTracing::ScopedEnabler::ScopedEnabler() {
  FileTracing::Provider* provider = GetProvider();
  if (provider)
    provider->FileTracingEnable(this);
}

FileTracing::ScopedEnabler::~ScopedEnabler() {
  FileTracing::Provider* provider = GetProvider();
  if (provider)
    provider->FileTracingDisable(this);
}

FileTracing::ScopedTrace::ScopedTrace() : id_(nullptr) {}

FileTracing::ScopedTrace::~ScopedTrace() {

#if !defined(OS_EMSCRIPTEN)
  if (id_) {
    FileTracing::Provider* provider = GetProvider();
    if (provider)
      provider->FileTracingEventEnd(name_, id_);
  }
#endif

}

void FileTracing::ScopedTrace::Initialize(const char* name,
                                          const File* file,
                                          int64_t size) {

#if !defined(OS_EMSCRIPTEN)
  id_ = &file->trace_enabler_;
  name_ = name;
  GetProvider()->FileTracingEventBegin(name_, id_, file->tracing_path_, size);
#endif

}

}  // namespace base
