// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_PROCESS_DESCRIPTOR_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_PROCESS_DESCRIPTOR_PROTO_CPP_H_

#include <stdint.h>
#include <bitset>
#include <vector>
#include <string>
#include <type_traits>

#include "perfetto/protozero/cpp_message_obj.h"
#include "perfetto/protozero/copyable_ptr.h"
#include "perfetto/base/export.h"

namespace perfetto {
namespace protos {
namespace gen {
class ChromeProcessDescriptor;
enum ChromeProcessDescriptor_ProcessType : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {
enum ChromeProcessDescriptor_ProcessType : int {
  ChromeProcessDescriptor_ProcessType_PROCESS_UNSPECIFIED = 0,
  ChromeProcessDescriptor_ProcessType_PROCESS_BROWSER = 1,
  ChromeProcessDescriptor_ProcessType_PROCESS_RENDERER = 2,
  ChromeProcessDescriptor_ProcessType_PROCESS_UTILITY = 3,
  ChromeProcessDescriptor_ProcessType_PROCESS_ZYGOTE = 4,
  ChromeProcessDescriptor_ProcessType_PROCESS_SANDBOX_HELPER = 5,
  ChromeProcessDescriptor_ProcessType_PROCESS_GPU = 6,
  ChromeProcessDescriptor_ProcessType_PROCESS_PPAPI_PLUGIN = 7,
  ChromeProcessDescriptor_ProcessType_PROCESS_PPAPI_BROKER = 8,
};

class PERFETTO_EXPORT ChromeProcessDescriptor : public ::protozero::CppMessageObj {
 public:
  using ProcessType = ChromeProcessDescriptor_ProcessType;
  static constexpr auto PROCESS_UNSPECIFIED = ChromeProcessDescriptor_ProcessType_PROCESS_UNSPECIFIED;
  static constexpr auto PROCESS_BROWSER = ChromeProcessDescriptor_ProcessType_PROCESS_BROWSER;
  static constexpr auto PROCESS_RENDERER = ChromeProcessDescriptor_ProcessType_PROCESS_RENDERER;
  static constexpr auto PROCESS_UTILITY = ChromeProcessDescriptor_ProcessType_PROCESS_UTILITY;
  static constexpr auto PROCESS_ZYGOTE = ChromeProcessDescriptor_ProcessType_PROCESS_ZYGOTE;
  static constexpr auto PROCESS_SANDBOX_HELPER = ChromeProcessDescriptor_ProcessType_PROCESS_SANDBOX_HELPER;
  static constexpr auto PROCESS_GPU = ChromeProcessDescriptor_ProcessType_PROCESS_GPU;
  static constexpr auto PROCESS_PPAPI_PLUGIN = ChromeProcessDescriptor_ProcessType_PROCESS_PPAPI_PLUGIN;
  static constexpr auto PROCESS_PPAPI_BROKER = ChromeProcessDescriptor_ProcessType_PROCESS_PPAPI_BROKER;
  static constexpr auto ProcessType_MIN = ChromeProcessDescriptor_ProcessType_PROCESS_UNSPECIFIED;
  static constexpr auto ProcessType_MAX = ChromeProcessDescriptor_ProcessType_PROCESS_PPAPI_BROKER;
  enum FieldNumbers {
    kProcessTypeFieldNumber = 1,
    kProcessPriorityFieldNumber = 2,
    kLegacySortIndexFieldNumber = 3,
    kHostAppPackageNameFieldNumber = 4,
  };

  ChromeProcessDescriptor();
  ~ChromeProcessDescriptor() override;
  ChromeProcessDescriptor(ChromeProcessDescriptor&&) noexcept;
  ChromeProcessDescriptor& operator=(ChromeProcessDescriptor&&);
  ChromeProcessDescriptor(const ChromeProcessDescriptor&);
  ChromeProcessDescriptor& operator=(const ChromeProcessDescriptor&);
  bool operator==(const ChromeProcessDescriptor&) const;
  bool operator!=(const ChromeProcessDescriptor& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_process_type() const { return _has_field_[1]; }
  ChromeProcessDescriptor_ProcessType process_type() const { return process_type_; }
  void set_process_type(ChromeProcessDescriptor_ProcessType value) { process_type_ = value; _has_field_.set(1); }

  bool has_process_priority() const { return _has_field_[2]; }
  int32_t process_priority() const { return process_priority_; }
  void set_process_priority(int32_t value) { process_priority_ = value; _has_field_.set(2); }

  bool has_legacy_sort_index() const { return _has_field_[3]; }
  int32_t legacy_sort_index() const { return legacy_sort_index_; }
  void set_legacy_sort_index(int32_t value) { legacy_sort_index_ = value; _has_field_.set(3); }

  bool has_host_app_package_name() const { return _has_field_[4]; }
  const std::string& host_app_package_name() const { return host_app_package_name_; }
  void set_host_app_package_name(const std::string& value) { host_app_package_name_ = value; _has_field_.set(4); }

 private:
  ChromeProcessDescriptor_ProcessType process_type_{};
  int32_t process_priority_{};
  int32_t legacy_sort_index_{};
  std::string host_app_package_name_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<5> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_PROCESS_DESCRIPTOR_PROTO_CPP_H_
