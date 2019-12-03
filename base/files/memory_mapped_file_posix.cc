// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/files/memory_mapped_file.h"

#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/numerics/safe_conversions.h"
#include "base/threading/scoped_blocking_call.h"
#include "build/build_config.h"

namespace base {

MemoryMappedFile::MemoryMappedFile() : data_(nullptr), length_(0) {}

#if !defined(OS_NACL)
bool MemoryMappedFile::MapFileRegionToMemory(
    const MemoryMappedFile::Region& region,
    Access access) {
    printf("MemoryMappedFile::MapFileRegionToMemory 1\n");
  ScopedBlockingCall scoped_blocking_call(FROM_HERE, BlockingType::MAY_BLOCK);

    printf("MemoryMappedFile::MapFileRegionToMemory 2\n");
  off_t map_start = 0;
  size_t map_size = 0;
  int32_t data_offset = 0;

    printf("MemoryMappedFile::MapFileRegionToMemory 3\n");
  if (region == MemoryMappedFile::Region::kWholeFile) {
    printf("MemoryMappedFile::MapFileRegionToMemory 3.1\n");
    int64_t file_len = file_.GetLength();
    printf("MemoryMappedFile::MapFileRegionToMemory %ld 3.2\n", file_len);
    if (file_len < 0) {
      DPLOG(ERROR) << "fstat " << file_.GetPlatformFile();
      return false;
    }
    printf("MemoryMappedFile::MapFileRegionToMemory 3.2\n");
    if (!IsValueInRangeForNumericType<size_t>(file_len))
      return false;
    printf("MemoryMappedFile::MapFileRegionToMemory 3.3\n");
    map_size = static_cast<size_t>(file_len);
    length_ = map_size;
    printf("MemoryMappedFile::MapFileRegionToMemory 3.4\n");
  } else {
    printf("MemoryMappedFile::MapFileRegionToMemory 4.1\n");
    // The region can be arbitrarily aligned. mmap, instead, requires both the
    // start and size to be page-aligned. Hence, we map here the page-aligned
    // outer region [|aligned_start|, |aligned_start| + |size|] which contains
    // |region| and then add up the |data_offset| displacement.
    int64_t aligned_start = 0;
    size_t aligned_size = 0;
    CalculateVMAlignedBoundaries(region.offset,
                                 region.size,
                                 &aligned_start,
                                 &aligned_size,
                                 &data_offset);
    printf("MemoryMappedFile::MapFileRegionToMemory 4.2\n");

    // Ensure that the casts in the mmap call below are sane.
    if (aligned_start < 0 ||
        !IsValueInRangeForNumericType<off_t>(aligned_start)) {
      DLOG(ERROR) << "Region bounds are not valid for mmap";
      return false;
    }
    printf("MemoryMappedFile::MapFileRegionToMemory 4.3\n");

    map_start = static_cast<off_t>(aligned_start);
    map_size = aligned_size;
    length_ = region.size;
  }


    printf("MemoryMappedFile::MapFileRegionToMemory 5.1\n");
  DCHECK(length()>0);
  DCHECK(length_>0);

    printf("MemoryMappedFile::MapFileRegionToMemory 5\n");

  int flags = 0;
  switch (access) {
    case READ_ONLY:
      flags |= PROT_READ;
      break;

    case READ_WRITE:
      flags |= PROT_READ | PROT_WRITE;
      break;

    case READ_WRITE_EXTEND:
      flags |= PROT_READ | PROT_WRITE;

      if (!AllocateFileRegion(&file_, region.offset, region.size))
        return false;

      break;
  }
    printf("MemoryMappedFile::MapFileRegionToMemory 6\n");

  DCHECK(file_.GetPlatformFile() != base::kInvalidPlatformFile);

  data_ = static_cast<uint8_t*>(mmap(nullptr, map_size, flags, MAP_SHARED,
                                     file_.GetPlatformFile(), map_start));

    printf("MemoryMappedFile::MapFileRegionToMemory 7\n");
  if (data_ == MAP_FAILED) {
    printf("MemoryMappedFile::MapFileRegionToMemory 7.1\n");
    DPLOG(ERROR) << "mmap " << file_.GetPlatformFile();
    return false;
  }
    printf("MemoryMappedFile::MapFileRegionToMemory 8\n");

  data_ += data_offset;

  DCHECK(data_);
  DCHECK(length()>0);
  DCHECK(data());
  DCHECK(IsValid());

  printf("MemoryMappedFile::Initialize 9\n");

  return true;
}
#endif

void MemoryMappedFile::CloseHandles() {
  ScopedBlockingCall scoped_blocking_call(FROM_HERE, BlockingType::MAY_BLOCK);

  if (data_ != nullptr)
    munmap(data_, length_);
  file_.Close();

  data_ = nullptr;
  length_ = 0;
}

}  // namespace base
