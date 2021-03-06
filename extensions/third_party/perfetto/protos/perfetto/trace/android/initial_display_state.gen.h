// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_ANDROID_INITIAL_DISPLAY_STATE_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_ANDROID_INITIAL_DISPLAY_STATE_PROTO_CPP_H_

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
class InitialDisplayState;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {

class PERFETTO_EXPORT InitialDisplayState : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kDisplayStateFieldNumber = 1,
    kBrightnessFieldNumber = 2,
  };

  InitialDisplayState();
  ~InitialDisplayState() override;
  InitialDisplayState(InitialDisplayState&&) noexcept;
  InitialDisplayState& operator=(InitialDisplayState&&);
  InitialDisplayState(const InitialDisplayState&);
  InitialDisplayState& operator=(const InitialDisplayState&);
  bool operator==(const InitialDisplayState&) const;
  bool operator!=(const InitialDisplayState& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_display_state() const { return _has_field_[1]; }
  int32_t display_state() const { return display_state_; }
  void set_display_state(int32_t value) { display_state_ = value; _has_field_.set(1); }

  bool has_brightness() const { return _has_field_[2]; }
  double brightness() const { return brightness_; }
  void set_brightness(double value) { brightness_ = value; _has_field_.set(2); }

 private:
  int32_t display_state_{};
  double brightness_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_ANDROID_INITIAL_DISPLAY_STATE_PROTO_CPP_H_
