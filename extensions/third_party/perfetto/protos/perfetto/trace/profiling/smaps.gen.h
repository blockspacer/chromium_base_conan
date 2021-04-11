// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PROFILING_SMAPS_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PROFILING_SMAPS_PROTO_CPP_H_

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
class SmapsPacket;
class SmapsEntry;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT SmapsPacket : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kPidFieldNumber = 1,
    kEntriesFieldNumber = 2,
  };

  SmapsPacket();
  ~SmapsPacket() override;
  SmapsPacket(SmapsPacket&&) noexcept;
  SmapsPacket& operator=(SmapsPacket&&);
  SmapsPacket(const SmapsPacket&);
  SmapsPacket& operator=(const SmapsPacket&);
  bool operator==(const SmapsPacket&) const;
  bool operator!=(const SmapsPacket& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_pid() const { return _has_field_[1]; }
  uint32_t pid() const { return pid_; }
  void set_pid(uint32_t value) { pid_ = value; _has_field_.set(1); }

  const std::vector<SmapsEntry>& entries() const { return entries_; }
  std::vector<SmapsEntry>* mutable_entries() { return &entries_; }
  int entries_size() const;
  void clear_entries();
  SmapsEntry* add_entries();

 private:
  uint32_t pid_{};
  std::vector<SmapsEntry> entries_;

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};


class PERFETTO_EXPORT SmapsEntry : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kPathFieldNumber = 1,
    kSizeKbFieldNumber = 2,
    kPrivateDirtyKbFieldNumber = 3,
    kSwapKbFieldNumber = 4,
    kFileNameFieldNumber = 5,
    kStartAddressFieldNumber = 6,
    kModuleTimestampFieldNumber = 7,
    kModuleDebugidFieldNumber = 8,
    kModuleDebugPathFieldNumber = 9,
    kProtectionFlagsFieldNumber = 10,
    kPrivateCleanResidentKbFieldNumber = 11,
    kSharedDirtyResidentKbFieldNumber = 12,
    kSharedCleanResidentKbFieldNumber = 13,
    kLockedKbFieldNumber = 14,
    kProportionalResidentKbFieldNumber = 15,
  };

  SmapsEntry();
  ~SmapsEntry() override;
  SmapsEntry(SmapsEntry&&) noexcept;
  SmapsEntry& operator=(SmapsEntry&&);
  SmapsEntry(const SmapsEntry&);
  SmapsEntry& operator=(const SmapsEntry&);
  bool operator==(const SmapsEntry&) const;
  bool operator!=(const SmapsEntry& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_path() const { return _has_field_[1]; }
  const std::string& path() const { return path_; }
  void set_path(const std::string& value) { path_ = value; _has_field_.set(1); }

  bool has_size_kb() const { return _has_field_[2]; }
  uint64_t size_kb() const { return size_kb_; }
  void set_size_kb(uint64_t value) { size_kb_ = value; _has_field_.set(2); }

  bool has_private_dirty_kb() const { return _has_field_[3]; }
  uint64_t private_dirty_kb() const { return private_dirty_kb_; }
  void set_private_dirty_kb(uint64_t value) { private_dirty_kb_ = value; _has_field_.set(3); }

  bool has_swap_kb() const { return _has_field_[4]; }
  uint64_t swap_kb() const { return swap_kb_; }
  void set_swap_kb(uint64_t value) { swap_kb_ = value; _has_field_.set(4); }

  bool has_file_name() const { return _has_field_[5]; }
  const std::string& file_name() const { return file_name_; }
  void set_file_name(const std::string& value) { file_name_ = value; _has_field_.set(5); }

  bool has_start_address() const { return _has_field_[6]; }
  uint64_t start_address() const { return start_address_; }
  void set_start_address(uint64_t value) { start_address_ = value; _has_field_.set(6); }

  bool has_module_timestamp() const { return _has_field_[7]; }
  uint64_t module_timestamp() const { return module_timestamp_; }
  void set_module_timestamp(uint64_t value) { module_timestamp_ = value; _has_field_.set(7); }

  bool has_module_debugid() const { return _has_field_[8]; }
  const std::string& module_debugid() const { return module_debugid_; }
  void set_module_debugid(const std::string& value) { module_debugid_ = value; _has_field_.set(8); }

  bool has_module_debug_path() const { return _has_field_[9]; }
  const std::string& module_debug_path() const { return module_debug_path_; }
  void set_module_debug_path(const std::string& value) { module_debug_path_ = value; _has_field_.set(9); }

  bool has_protection_flags() const { return _has_field_[10]; }
  uint32_t protection_flags() const { return protection_flags_; }
  void set_protection_flags(uint32_t value) { protection_flags_ = value; _has_field_.set(10); }

  bool has_private_clean_resident_kb() const { return _has_field_[11]; }
  uint64_t private_clean_resident_kb() const { return private_clean_resident_kb_; }
  void set_private_clean_resident_kb(uint64_t value) { private_clean_resident_kb_ = value; _has_field_.set(11); }

  bool has_shared_dirty_resident_kb() const { return _has_field_[12]; }
  uint64_t shared_dirty_resident_kb() const { return shared_dirty_resident_kb_; }
  void set_shared_dirty_resident_kb(uint64_t value) { shared_dirty_resident_kb_ = value; _has_field_.set(12); }

  bool has_shared_clean_resident_kb() const { return _has_field_[13]; }
  uint64_t shared_clean_resident_kb() const { return shared_clean_resident_kb_; }
  void set_shared_clean_resident_kb(uint64_t value) { shared_clean_resident_kb_ = value; _has_field_.set(13); }

  bool has_locked_kb() const { return _has_field_[14]; }
  uint64_t locked_kb() const { return locked_kb_; }
  void set_locked_kb(uint64_t value) { locked_kb_ = value; _has_field_.set(14); }

  bool has_proportional_resident_kb() const { return _has_field_[15]; }
  uint64_t proportional_resident_kb() const { return proportional_resident_kb_; }
  void set_proportional_resident_kb(uint64_t value) { proportional_resident_kb_ = value; _has_field_.set(15); }

 private:
  std::string path_{};
  uint64_t size_kb_{};
  uint64_t private_dirty_kb_{};
  uint64_t swap_kb_{};
  std::string file_name_{};
  uint64_t start_address_{};
  uint64_t module_timestamp_{};
  std::string module_debugid_{};
  std::string module_debug_path_{};
  uint32_t protection_flags_{};
  uint64_t private_clean_resident_kb_{};
  uint64_t shared_dirty_resident_kb_{};
  uint64_t shared_clean_resident_kb_{};
  uint64_t locked_kb_{};
  uint64_t proportional_resident_kb_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<16> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PROFILING_SMAPS_PROTO_CPP_H_