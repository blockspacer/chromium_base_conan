# see component("base") in BUILD.gn
list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
  allocator/allocator_shim.cc
  allocator/allocator_shim.h
  allocator/allocator_shim_default_dispatch_to_partition_alloc.cc
  allocator/allocator_shim_default_dispatch_to_partition_alloc.h
  allocator/allocator_shim_internals.h
)

if(TARGET_ANDROID)
  message(STATUS "Enabled allocator shim for ANDROID")
  list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
    allocator/allocator_shim_override_cpp_symbols.h
    allocator/allocator_shim_override_linker_wrapped_symbols.h
  )
elseif(TARGET_APPLE)
  message(STATUS "Enabled allocator shim for APPLE")
  list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
    allocator/allocator_shim_override_mac_symbols.h
  )
elseif(TARGET_WINDOWS)
  message(STATUS "Enabled allocator shim for Windows")
  list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
    allocator/winheap_stubs_win.cc
  )
elseif(TARGET_LINUX)
  message(STATUS "Enabled TCMALLOC allocator shim for Linux")
  list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
    allocator/allocator_shim_override_glibc_weak_symbols.h
  )
else()
  message(FATAL_ERROR "Platform not supported")
endif()

if(ALLOCATOR_TCMALLOC)
  message(STATUS "Enabled TCMALLOC allocator shim")
  list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
    allocator/allocator_shim_default_dispatch_to_tcmalloc.cc
  )
elseif(ALLOCATOR_NONE)
  message(STATUS "Enabled none allocator shim")
  if(TARGET_ANDROID)
    list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
      allocator/allocator_shim_default_dispatch_to_linker_wrapped_symbols.cc
    )
  elseif(TARGET_APPLE)
    list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
      allocator/allocator_shim_default_dispatch_to_mac_zoned_malloc.cc
    )
  elseif(TARGET_LINUX OR TARGET_EMSCRIPTEN OR TARGET_CHROMEOS)
    list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
      allocator/allocator_shim_default_dispatch_to_glibc.cc
    )
  elseif(TARGET_WINDOWS)
    message(STATUS "Enabled allocator shim for Windows")
    list(APPEND COMPONENT_BASE_SOURCES_ALLOC_SHIM_UNPROCESSED
      allocator/allocator_shim_default_dispatch_to_winheap.cc
    )
  endif()
else()
  message(FATAL_ERROR "You must specify allocator")
endif()

list(APPEND COMPONENT_BASE_SOURCES ${COMPONENT_BASE_SOURCES_IOS_UNPROCESSED})
