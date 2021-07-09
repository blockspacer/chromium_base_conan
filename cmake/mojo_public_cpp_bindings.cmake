set(ENABLE_MOJO_TACING FALSE CACHE BOOL "ENABLE_MOJO_TACING")

# enable_random_mojo_delays starts a task runner that periodically pauses
# random Mojo bindings and later resumes them, in order to test whether parts
# of the code implicitly rely on FIFO processing of messages sent on different
# message pipes (which they should not).
set(ENABLE_RANDOM_MOJO_DELAYS FALSE CACHE BOOL "ENABLE_RANDOM_MOJO_DELAYS")

# ~~~~~~~~~~~~~~~~~~~~~ component("bindings_base") ~~~~~~~~~~~~~~~~~~~~~~~~~~~

list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_BASE_SOURCES
  "array_data_view.h"
  "array_traits.h"
  "array_traits_span.h"
  "array_traits_stl.h"
  "associated_group.h"
  "associated_group_controller.h"
  "clone_traits.h"
  "connection_group.cc"
  "connection_group.h"
  "deprecated_interface_types_forward.h"
  "disconnect_reason.h"
  "enum_traits.h"
  "enum_utils.h"
  "equals_traits.h"
  "features.cc"
  "features.h"
  "interface_data_view.h"
  "interface_id.h"
  "lib/array_internal.cc"
  "lib/array_internal.h"
  "lib/array_serialization.h"
  "lib/associated_group.cc"
  "lib/associated_group_controller.cc"
  "lib/bindings_internal.h"
  "lib/buffer.cc"
  "lib/buffer.h"
  "lib/handle_serialization.cc"
  "lib/handle_serialization.h"
  "lib/hash_util.h"
  "lib/map_data_internal.h"
  "lib/map_serialization.h"
  "lib/may_auto_lock.h"
  "lib/message.cc"
  "lib/message_fragment.h"
  "lib/message_header_validator.cc"
  "lib/message_internal.cc"
  "lib/message_internal.h"
  "lib/pending_receiver_state.cc"
  "lib/pending_receiver_state.h"
  "lib/pending_remote_state.cc"
  "lib/pending_remote_state.h"
  "lib/scoped_interface_endpoint_handle.cc"
  "lib/serialization.h"
  "lib/serialization_forward.h"
  "lib/serialization_util.h"
  "lib/string_serialization.h"
  "lib/template_util.h"
  "lib/unserialized_message_context.cc"
  "lib/unserialized_message_context.h"
  "lib/validate_params.h"
  "lib/validation_context.cc"
  "lib/validation_context.h"
  "lib/validation_errors.cc"
  "lib/validation_errors.h"
  "lib/validation_util.cc"
  "lib/validation_util.h"
  "map_data_view.h"
  "map_traits.h"
  "map_traits_flat_map.h"
  "map_traits_stl.h"
  "message.h"
  "message_header_validator.h"
  "scoped_interface_endpoint_handle.h"
  "scoped_message_error_crash_key.cc"
  "scoped_message_error_crash_key.h"
  "string_data_view.h"
  "string_traits.h"
  "string_traits_stl.h"
  "string_traits_string_piece.h"
  "struct_forward.h"
  "struct_ptr.h"
  "struct_traits.h"
  "type_converter.h"
  "union_traits.h"
)

list(TRANSFORM COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_BASE_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/public/cpp/bindings/")

add_library(bindings_base
  ${COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_BASE_SOURCES}
)

add_dependencies(bindings_base
  ${MOJO_SOURCES_PATH}/public/cpp/bindings/mojo_buildflags.h
)

target_link_libraries(bindings_base PUBLIC
  ${BASE_LIB_NAME}
  mojo_public_system_cpp
)

# TODO
# if (enable_ipc_fuzzer) {
#   all_dependent_configs = [ "//tools/ipc_fuzzer:ipc_fuzzer_config" ]
# }
#
# if (!is_debug && !optimize_for_size) {
#   configs -= [ "//build/config/compiler:default_optimization" ]
#   configs += [ "//build/config/compiler:optimize_max" ]
# }

target_compile_definitions(bindings_base PRIVATE
  IS_MOJO_CPP_BINDINGS_BASE_IMPL=1
)

# ~~~~~~~~~~~~~~~~~~~~~ source_set("struct_traits") ~~~~~~~~~~~~~~~~~~~~~~~~~~~

list(APPEND MOJO_STRUCT_TRAITS
  "array_traits.h"
  "enum_traits.h"
  "lib/template_util.h"
  "map_traits.h"
  "string_traits.h"
  "struct_traits.h"
  "union_traits.h"
)

list(TRANSFORM MOJO_STRUCT_TRAITS
  PREPEND "${MOJO_SOURCES_PATH}/public/cpp/bindings/")

# ~~~~~~~~~~~~~~~~~~~~~ component("bindings") ~~~~~~~~~~~~~~~~~~~~~~~~~~~

list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_SOURCES
  "associated_interface_ptr_info.h"
  "associated_interface_request.h"
  "associated_receiver.h"
  "associated_receiver_set.h"
  "associated_remote.h"
  "async_flusher.cc"
  "async_flusher.h"
  "binder_map.h"
  "callback_helpers.h"
  "connection_error_callback.h"
  "connector.h"
  "generic_pending_receiver.cc"
  "generic_pending_receiver.h"
  "interface_endpoint_client.h"
  "interface_endpoint_controller.h"
  "interface_ptr.h"
  "interface_ptr_info.h"
  "interface_request.h"
  "lib/associated_interface_ptr_state.cc"
  "lib/associated_interface_ptr_state.h"
  "lib/associated_receiver.cc"
  "lib/binder_map_internal.h"
  "lib/binding_state.cc"
  "lib/binding_state.h"
  "lib/connector.cc"
  "lib/control_message_handler.cc"
  "lib/control_message_handler.h"
  "lib/control_message_proxy.cc"
  "lib/control_message_proxy.h"
  "lib/generated_code_util.cc"
  "lib/generated_code_util.h"
  "lib/interface_endpoint_client.cc"
  "lib/interface_ptr_state.cc"
  "lib/interface_ptr_state.h"
  "lib/interface_serialization.h"
  "lib/message_dispatcher.cc"
  "lib/message_quota_checker.cc"
  "lib/message_quota_checker.h"
  "lib/multiplex_router.cc"
  "lib/multiplex_router.h"
  "lib/native_enum_data.h"
  "lib/native_enum_serialization.h"
  "lib/native_struct_serialization.cc"
  "lib/native_struct_serialization.h"
  "lib/pipe_control_message_handler.cc"
  "lib/pipe_control_message_proxy.cc"
  "lib/sequence_local_sync_event_watcher.cc"
  "lib/sync_call_restrictions.cc"
  "lib/sync_event_watcher.cc"
  "lib/sync_handle_registry.cc"
  "lib/sync_handle_watcher.cc"
  "lib/task_runner_helper.cc"
  "lib/task_runner_helper.h"
  "lib/thread_safe_forwarder_base.cc"
  "lib/thread_safe_forwarder_base.h"
  "message_dispatcher.h"
  "native_enum.h"
  "pending_associated_receiver.h"
  "pending_associated_remote.h"
  "pending_flush.cc"
  "pending_flush.h"
  "pending_receiver.h"
  "pending_remote.h"
  "pipe_control_message_handler.h"
  "pipe_control_message_handler_delegate.h"
  "pipe_control_message_proxy.h"
  "raw_ptr_impl_ref_traits.h"
  "receiver.h"
  "receiver_set.h"
  "remote.h"
  "remote_set.h"
  "self_owned_associated_receiver.h"
  "self_owned_receiver.h"
  "sequence_local_sync_event_watcher.h"
  "service_factory.cc"
  "service_factory.h"
  "shared_associated_remote.h"
  "shared_remote.h"
  "sync_call_restrictions.h"
  "sync_event_watcher.h"
  "sync_handle_registry.h"
  "sync_handle_watcher.h"
  "unique_associated_receiver_set.h"
  "unique_ptr_impl_ref_traits.h"
  "unique_receiver_set.h"
)

if (ENABLE_RANDOM_MOJO_DELAYS)
  list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_SOURCES
    "lib/test_random_mojo_delays.cc"
    "lib/test_random_mojo_delays.h"
  )
endif()

# TODO
# if (enable_ipc_fuzzer && !is_nacl_nonsfi) {
#   sources += [
#     "lib/message_dumper.cc"
#     "message_dumper.h"
#   ]
# }

list(TRANSFORM COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_SOURCES
  PREPEND "${MOJO_SOURCES_PATH}/public/cpp/bindings/")

list(APPEND COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_SOURCES MOJO_STRUCT_TRAITS)

add_library(bindings
  ${COMPONENT_MOJO_PUBLIC_CPP_BINDINGS_SOURCES}
)

add_dependencies(bindings
  ${MOJO_SOURCES_PATH}/public/cpp/bindings/mojo_buildflags.h
)

# TODO
# "//ipc:message_support",
# "//ipc:param_traits",
# deps = [ "//ipc:native_handle_type_converters" ]
target_link_libraries(bindings PUBLIC
  ${BASE_LIB_NAME}
  bindings_base
  mojo_public_system_cpp
  mojo_public_interfaces_bindings
)

# TODO
# if (enable_ipc_fuzzer && !is_nacl_nonsfi) {
#   sources += [
#     "lib/message_dumper.cc"
#     "message_dumper.h"
#   ]
# }

target_compile_definitions(bindings PRIVATE
  IS_MOJO_CPP_BINDINGS_IMPL=1
)

# TODO
# if (!is_ios) {
#   component("wtf_support") {
#     sources = [
#       "array_traits_web_vector.h",
#       "array_traits_wtf_vector.h",
#       "lib/string_traits_wtf.cc",
#       "lib/wtf_clone_equals_util.h",
#       "lib/wtf_hash_util.h",
#       "lib/wtf_serialization.h",
#       "map_traits_wtf_hash_map.h",
#       "string_traits_wtf.h",
#     ]
#
#     defines = [ "IS_MOJO_CPP_BINDINGS_BASE_IMPL" ]
#
#     public_deps = [
#       ":bindings",
#       "//base",
#       "//third_party/blink/public:blink_headers",
#       "//third_party/blink/renderer/platform:platform_export",
#       "//third_party/blink/renderer/platform/wtf",
#     ]
#
#     public_configs = [ "//third_party/blink/renderer:config" ]
#   }
# }
