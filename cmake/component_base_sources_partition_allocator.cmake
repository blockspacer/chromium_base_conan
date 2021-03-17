# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_PARTITION_ALLOC_UNPROCESSED
  # PartitionAlloc uses SpinLock, which doesn't work in NaCl (see below).
  "allocator/partition_allocator/address_pool_manager.cc"
  "allocator/partition_allocator/address_pool_manager.h"
  "allocator/partition_allocator/address_pool_manager_bitmap.cc"
  "allocator/partition_allocator/address_pool_manager_bitmap.h"
  "allocator/partition_allocator/address_pool_manager_types.h"
  "allocator/partition_allocator/address_space_randomization.cc"
  "allocator/partition_allocator/address_space_randomization.h"
  "allocator/partition_allocator/extended_api.cc"
  "allocator/partition_allocator/extended_api.h"
  "allocator/partition_allocator/memory_reclaimer.cc"
  "allocator/partition_allocator/memory_reclaimer.h"
  "allocator/partition_allocator/object_bitmap.h"
  "allocator/partition_allocator/oom.h"
  "allocator/partition_allocator/oom_callback.cc"
  "allocator/partition_allocator/oom_callback.h"
  "allocator/partition_allocator/page_allocator.cc"
  "allocator/partition_allocator/page_allocator.h"
  "allocator/partition_allocator/page_allocator_internal.h"
  "allocator/partition_allocator/partition_address_space.cc"
  "allocator/partition_allocator/partition_address_space.h"
  "allocator/partition_allocator/partition_alloc-inl.h"
  "allocator/partition_allocator/partition_alloc.cc"
  "allocator/partition_allocator/partition_alloc.h"
  "allocator/partition_allocator/partition_alloc_check.h"
  "allocator/partition_allocator/partition_alloc_constants.h"
  "allocator/partition_allocator/partition_alloc_features.cc"
  "allocator/partition_allocator/partition_alloc_features.h"
  "allocator/partition_allocator/partition_alloc_forward.h"
  "allocator/partition_allocator/partition_alloc_hooks.cc"
  "allocator/partition_allocator/partition_alloc_hooks.h"
  "allocator/partition_allocator/partition_bucket.cc"
  "allocator/partition_allocator/partition_bucket.h"
  "allocator/partition_allocator/partition_cookie.h"
  "allocator/partition_allocator/partition_direct_map_extent.h"
  "allocator/partition_allocator/partition_freelist_entry.h"
  "allocator/partition_allocator/partition_lock.cc"
  "allocator/partition_allocator/partition_lock.h"
  "allocator/partition_allocator/partition_oom.cc"
  "allocator/partition_allocator/partition_oom.h"
  "allocator/partition_allocator/partition_page.cc"
  "allocator/partition_allocator/partition_page.h"
  "allocator/partition_allocator/partition_ref_count.cc"
  "allocator/partition_allocator/partition_ref_count.h"
  "allocator/partition_allocator/partition_root.cc"
  "allocator/partition_allocator/partition_root.h"
  "allocator/partition_allocator/partition_stats.cc"
  "allocator/partition_allocator/partition_stats.h"
  "allocator/partition_allocator/partition_tls.h"
  "allocator/partition_allocator/pcscan.cc"
  "allocator/partition_allocator/pcscan.h"
  "allocator/partition_allocator/random.cc"
  "allocator/partition_allocator/random.h"
  "allocator/partition_allocator/spinning_mutex.cc"
  "allocator/partition_allocator/spinning_mutex.h"
  "allocator/partition_allocator/thread_cache.cc"
  "allocator/partition_allocator/thread_cache.h"
  "allocator/partition_allocator/yield_processor.h"
)

if(TARGET_WINDOWS)
  list(APPEND COMPONENT_BASE_SOURCES_PARTITION_ALLOC_UNPROCESSED
    "allocator/partition_allocator/page_allocator_internals_win.h"
    "allocator/partition_allocator/partition_tls_win.cc"
  )
elseif(TARGET_POSIX)
  list(APPEND COMPONENT_BASE_SOURCES_PARTITION_ALLOC_UNPROCESSED
    "allocator/partition_allocator/page_allocator_internals_posix.cc"
    "allocator/partition_allocator/page_allocator_internals_posix.h"
  )
elseif(TARGET_FUCHSIA)
  list(APPEND COMPONENT_BASE_SOURCES_PARTITION_ALLOC_UNPROCESSED
    "allocator/partition_allocator/page_allocator_internals_fuchsia.h"
  )
endif()

list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_PARTITION_ALLOC_UNPROCESSED})
