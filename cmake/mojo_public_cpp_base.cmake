list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BASE
  "big_buffer.cc"
  "big_buffer.h"
  "shared_memory_utils.cc"
  "shared_memory_utils.h"
)

# component("typemap_traits")
list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BASE
  "big_string_mojom_traits.cc"
  "big_string_mojom_traits.h"
  "memory_allocator_dump_cross_process_uid_mojom_traits.cc"
  "memory_allocator_dump_cross_process_uid_mojom_traits.h"
  "memory_pressure_level_mojom_traits.cc"
  "memory_pressure_level_mojom_traits.h"
  "message_pump_type_mojom_traits.cc"
  "message_pump_type_mojom_traits.h"
  "process_id_mojom_traits.cc"
  "process_id_mojom_traits.h"
  "ref_counted_memory_mojom_traits.cc"
  "ref_counted_memory_mojom_traits.h"
  "string16_mojom_traits.cc"
  "string16_mojom_traits.h"
  "text_direction_mojom_traits.cc"
  "text_direction_mojom_traits.h"
  "thread_priority_mojom_traits.cc"
  "thread_priority_mojom_traits.h"
)

if (TARGET_ANDROID)
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BASE
    "application_state_mojom_traits.cc"
    "application_state_mojom_traits.h"
  )
endif()

if (TARGET_WINDOWS)
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BASE
    "logfont_win_mojom_traits.cc"
    "logfont_win_mojom_traits.h"
  )
endif()

# component("shared_typemap_traits")
list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BASE
  "big_buffer_mojom_traits.cc"
  "big_buffer_mojom_traits.h"
  "file_info_mojom_traits.cc"
  "file_info_mojom_traits.h"
  "file_mojom_traits.cc"
  "file_mojom_traits.h"
  "file_path_mojom_traits.cc"
  "file_path_mojom_traits.h"
  "generic_pending_receiver_mojom_traits.cc"
  "generic_pending_receiver_mojom_traits.h"
  "read_only_buffer_mojom_traits.cc"
  "read_only_buffer_mojom_traits.h"
  "read_only_file_mojom_traits.cc"
  "read_only_file_mojom_traits.h"
  "shared_memory_mojom_traits.cc"
  "shared_memory_mojom_traits.h"
  "time_mojom_traits.cc"
  "time_mojom_traits.h"
  "token_mojom_traits.cc"
  "token_mojom_traits.h"
  "unguessable_token_mojom_traits.cc"
  "unguessable_token_mojom_traits.h"
  "values_mojom_traits.cc"
  "values_mojom_traits.h"
)

# if(NOT USE_NACL)
#   remove_from_list(
#     CHECK_EXISTS TRUE
#     INPUT ${COMPONENT_MOJO_PUBLIC_CPP_BASE}
#     OUTPUT COMPONENT_MOJO_PUBLIC_CPP_BASE
#     ITEMS
#     "file_data_source.cc"
#   )
# endif()

list(TRANSFORM COMPONENT_MOJO_PUBLIC_CPP_BASE
  PREPEND "${MOJO_SOURCES_PATH}/public/cpp/base/")

# mojom_component("base")
list(APPEND BASE_MOJOM_SOURCES
  "application_state.mojom-shared.cc"
  "big_buffer.mojom-shared.cc"
  "big_string.mojom-shared.cc"
  "binder.mojom-shared.cc"
  "file.mojom-shared.cc"
  "file_error.mojom-shared.cc"
  "file_info.mojom-shared.cc"
  "file_path.mojom-shared.cc"
  "generic_pending_receiver.mojom-shared.cc"
  "memory_allocator_dump_cross_process_uid.mojom-shared.cc"
  "memory_pressure_level.mojom-shared.cc"
  "message_pump_type.mojom-shared.cc"
  "process_id.mojom-shared.cc"
  "read_only_buffer.mojom-shared.cc"
  "read_only_file.mojom-shared.cc"
  "ref_counted_memory.mojom-shared.cc"
  "shared_memory.mojom-shared.cc"
  "string16.mojom-shared.cc"
  "text_direction.mojom-shared.cc"
  "thread_priority.mojom-shared.cc"
  "time.mojom-shared.cc"
  "token.mojom-shared.cc"
  "unguessable_token.mojom-shared.cc"
  "values.mojom-shared.cc"
)

list(APPEND BASE_MOJOM_SOURCES
  "application_state.mojom.cc"
  "big_buffer.mojom.cc"
  "big_string.mojom.cc"
  "binder.mojom.cc"
  "file.mojom.cc"
  "file_error.mojom.cc"
  "file_info.mojom.cc"
  "file_path.mojom.cc"
  "generic_pending_receiver.mojom.cc"
  "memory_allocator_dump_cross_process_uid.mojom.cc"
  "memory_pressure_level.mojom.cc"
  "message_pump_type.mojom.cc"
  "process_id.mojom.cc"
  "read_only_buffer.mojom.cc"
  "read_only_file.mojom.cc"
  "ref_counted_memory.mojom.cc"
  "shared_memory.mojom.cc"
  "string16.mojom.cc"
  "text_direction.mojom.cc"
  "thread_priority.mojom.cc"
  "time.mojom.cc"
  "token.mojom.cc"
  "unguessable_token.mojom.cc"
  "values.mojom.cc"
)

if (TARGET_WINDOWS)
  list(APPEND BASE_MOJOM_SOURCES
    "logfont_win.mojom.cc"
    "logfont_win.mojom-shared.cc"
  )
endif()

# TODO mojo/public/mojom/base/file_path.mojom
# [EnableIf=file_path_is_string]
# enabled_features = []
# if (is_win) {
#   enabled_features += [ "file_path_is_string16" ]
# } else {
#   enabled_features += [ "file_path_is_string" ]
# }

list(TRANSFORM BASE_MOJOM_SOURCES
  PREPEND "${IPC_SOURCES_PATH}/../gen/mojo/public/mojom/base/")

add_library(mojo_base_lib
  ${COMPONENT_MOJO_PUBLIC_CPP_BASE}
  ${BASE_MOJOM_SOURCES}
)

target_include_directories(mojo_base_lib PUBLIC
  "${MOJO_SOURCES_PATH}/../gen/"
)

target_link_libraries(mojo_base_lib PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system
  mojo_cpp_platform
  mojo_public_cpp_bindings
)

target_compile_definitions(mojo_base_lib PRIVATE
  IS_MOJO_BASE_IMPL=1
  IS_MOJO_BASE_TRAITS_IMPL=1
  IS_MOJO_BASE_SHARED_TRAITS_IMPL=1
)
