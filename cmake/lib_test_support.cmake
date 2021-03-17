﻿#
# See https://source.chromium.org/chromium/chromium/src/+/master:base/test/BUILD.gn

# see static_library("test_support") in /test/BUILD.gn
list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
  "../power_monitor/test/fake_power_monitor_source.cc"
  "../power_monitor/test/fake_power_monitor_source.h"
  "../task/sequence_manager/test/fake_task.cc"
  "../task/sequence_manager/test/fake_task.h"
  "../task/sequence_manager/test/mock_time_domain.cc"
  "../task/sequence_manager/test/mock_time_domain.h"
  "../task/sequence_manager/test/mock_time_message_pump.cc"
  "../task/sequence_manager/test/mock_time_message_pump.h"
  "../task/sequence_manager/test/sequence_manager_for_test.cc"
  "../task/sequence_manager/test/sequence_manager_for_test.h"
  "../task/sequence_manager/test/test_task_queue.cc"
  "../task/sequence_manager/test/test_task_queue.h"
  "../task/sequence_manager/test/test_task_time_observer.h"
  "../timer/mock_timer.cc"
  "../timer/mock_timer.h"
  "bind.cc"
  "bind.h"
  "copy_only_int.cc"
  "copy_only_int.h"
  "gmock_callback_support.h"
  "gmock_move_support.h"
  "gtest_links.cc"
  "gtest_links.h"
  "gtest_util.cc"
  "gtest_util.h"
  "gtest_xml_unittest_result_printer.cc"
  "gtest_xml_unittest_result_printer.h"
  "gtest_xml_util.cc"
  "gtest_xml_util.h"
  "icu_test_util.cc"
  "icu_test_util.h"
  "launcher/test_result.cc"
  "launcher/test_result.h"
  "launcher/test_results_tracker.h"
  "launcher/unit_test_launcher.h"
  "metrics/histogram_enum_reader.cc"
  "metrics/histogram_enum_reader.h"
  "metrics/histogram_tester.cc"
  "metrics/histogram_tester.h"
  "metrics/user_action_tester.cc"
  "metrics/user_action_tester.h"
  "mock_callback.h"
  "mock_devices_changed_observer.cc"
  "mock_devices_changed_observer.h"
  "mock_entropy_provider.cc"
  "mock_entropy_provider.h"
  "mock_log.cc"
  "mock_log.h"
  "move_only_int.h"
  "multiprocess_test.h"
  "null_task_runner.cc"
  "null_task_runner.h"
  "perf_log.cc"
  "perf_log.h"
  "perf_test_suite.cc"
  "perf_test_suite.h"
  "perf_time_logger.cc"
  "perf_time_logger.h"
  "power_monitor_test_base.cc"
  "power_monitor_test_base.h"
  "scoped_command_line.cc"
  "scoped_command_line.h"
  "scoped_environment_variable_override.cc"
  "scoped_environment_variable_override.h"
  "scoped_feature_list.cc"
  "scoped_feature_list.h"
  "scoped_field_trial_list_resetter.cc"
  "scoped_field_trial_list_resetter.h"
  "scoped_mock_clock_override.cc"
  "scoped_mock_clock_override.h"
  "scoped_mock_time_message_loop_task_runner.cc"
  "scoped_mock_time_message_loop_task_runner.h"
  "scoped_path_override.cc"
  "scoped_path_override.h"
  "scoped_run_loop_timeout.cc"
  "scoped_run_loop_timeout.h"
  "sequenced_task_runner_test_template.cc"
  "sequenced_task_runner_test_template.h"
  "simple_test_clock.cc"
  "simple_test_clock.h"
  "simple_test_tick_clock.cc"
  "simple_test_tick_clock.h"
  "task_environment.cc"
  "task_environment.h"
  "task_runner_test_template.cc"
  "task_runner_test_template.h"
  "test_discardable_memory_allocator.cc"
  "test_discardable_memory_allocator.h"
  "test_file_util.cc"
  "test_file_util.h"
  "test_io_thread.cc"
  "test_io_thread.h"
  "test_message_loop.cc"
  "test_message_loop.h"
  "test_mock_time_task_runner.cc"
  "test_mock_time_task_runner.h"
  "test_pending_task.cc"
  "test_pending_task.h"
  "test_shared_memory_util.cc"
  "test_shared_memory_util.h"
  "test_simple_task_runner.cc"
  "test_simple_task_runner.h"
  "test_suite.cc"
  "test_suite.h"
  "test_waitable_event.cc"
  "test_waitable_event.h"
  "thread_test_helper.cc"
  "thread_test_helper.h"
  "values_test_util.cc"
  "values_test_util.h"
  "with_feature_override.cc"
  "with_feature_override.h"
)

if(TARGET_WINDOWS)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "async_results_test_values_win.h"
    "fake_iasync_operation_win.h"
    "scoped_os_info_override_win.cc"
    "scoped_os_info_override_win.h"
    "test_file_util_win.cc"
    "test_reg_util_win.cc"
    "test_reg_util_win.h"
    "test_shortcut_win.cc"
    "test_shortcut_win.h"
  )
endif(TARGET_WINDOWS)

# TODO
# if (is_chromeos_ash || is_chromeos_lacros) {
#   sources += [
#     "scoped_chromeos_version_info.cc"
#     "scoped_chromeos_version_info.h"
#     "scoped_running_on_chromeos.cc"
#     "scoped_running_on_chromeos.h"
#   ]
# }

if(TARGET_LINUX)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "test_file_util_linux.cc"
  )
endif(TARGET_LINUX)

if(TARGET_MACOS)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "mock_chrome_application_mac.h"
    "mock_chrome_application_mac.mm"
    "test_file_util_mac.cc"
  )
endif(TARGET_MACOS)

if(TARGET_ANDROID)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "android/java_handler_thread_helpers.cc"
    "android/java_handler_thread_helpers.h"
    "android/url_utils.cc"
    "android/url_utils.h"
    "multiprocess_test_android.cc"
    "reached_code_profiler_android.cc"
    "test_file_util_android.cc"
    "test_file_util_linux.cc"
    "test_support_android.cc"
    "test_support_android.h"
    "thread_pool_test_helpers_android.cc"
  )
endif(TARGET_ANDROID)

if(TARGET_IOS)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "../ios/weak_nsobject.h"
    "../ios/weak_nsobject.mm"
    "ios/wait_util.h"
    "ios/wait_util.mm"
    "launcher/unit_test_launcher_ios.cc"
    "test_file_util_mac.cc"
    "test_listener_ios.h"
    "test_listener_ios.mm"
    "test_support_ios.h"
    "test_support_ios.mm"
  )
endif(TARGET_IOS)

if(TARGET_POSIX)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "scoped_locale.cc"
    "scoped_locale.h"
    "test_file_util_posix.cc"
  )
endif(TARGET_POSIX)

# TODO
# if (is_fuchsia) {
#   deps += [ "//third_party/fuchsia-sdk/sdk/pkg/zx" ]
#   public_deps += [ "//third_party/fuchsia-sdk/sdk/pkg/sys_cpp" ]
#   sources += [
#     "../fuchsia/test_component_context_for_process.cc"
#     "../fuchsia/test_component_context_for_process.h"
#     "../fuchsia/test_component_controller.cc"
#     "../fuchsia/test_component_controller.h"
#   ]
# }
# if (is_nacl_nonsfi) {
#   sources += [
#     "launcher/test_launcher.h"
#     "launcher/test_result.h"
#     "launcher/unit_test_launcher.h"
#     "launcher/unit_test_launcher_nacl_nonsfi.cc"
#   ]
#   sources -= [
#     "gtest_xml_util.cc"
#     "gtest_xml_util.h"
#     "icu_test_util.cc"
#     "icu_test_util.h"
#     "metrics/histogram_enum_reader.cc"
#     "metrics/histogram_enum_reader.h"
#     "perf_test_suite.cc"
#     "perf_test_suite.h"
#     "scoped_path_override.cc"
#     "scoped_path_override.h"
#     "test_discardable_memory_allocator.cc"
#     "test_discardable_memory_allocator.h"
#     "test_file_util.cc"
#     "test_file_util.h"
#     "test_file_util_posix.cc"
#     "test_suite.cc"
#     "test_suite.h"
#   ]
#   public_deps -= [ "//base:i18n" ]
#   deps -= [
#     "//third_party/icu:icuuc"
#     "//third_party/libxml:libxml_utils"
#     "//third_party/libxml:xml_reader"
#   ]
# }

if(NOT TARGET_IOS)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "launcher/test_launcher.cc"
    "launcher/test_launcher.h"
    "launcher/test_launcher_test_utils.cc"
    "launcher/test_launcher_test_utils.h"
    "launcher/test_launcher_tracer.cc"
    "launcher/test_launcher_tracer.h"
    "launcher/test_results_tracker.cc"
    "launcher/unit_test_launcher.cc"
    "multiprocess_test.cc"
  )
endif()

if(ENABLE_BASE_TRACING)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "../trace_event/trace_config_memory_test_util.h"
    "trace_event_analyzer.cc"
    "trace_event_analyzer.h"
  )
  # if (!is_nacl_nonsfi)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "trace_to_file.cc"
    "trace_to_file.h"
  )
endif()

if(TARGET_LINUX OR TARGET_CHROMEOS)
  list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
    "fontconfig_util_linux.cc"
    "fontconfig_util_linux.h"
  )
endif()

# source_set("test_support_perf")
list(APPEND LIB_TEST_SUPPORT_UNPROCESSED
  "run_all_perftests.cc"
)

list(TRANSFORM LIB_TEST_SUPPORT_UNPROCESSED PREPEND "test/")
list(APPEND COMPONENT_BASE_SOURCES ${LIB_TEST_SUPPORT_UNPROCESSED})
