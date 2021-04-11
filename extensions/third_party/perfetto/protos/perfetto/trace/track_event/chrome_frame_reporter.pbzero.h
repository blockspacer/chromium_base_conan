// Autogenerated by the ProtoZero compiler plugin. DO NOT EDIT.

#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_FRAME_REPORTER_PROTO_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_CHROME_FRAME_REPORTER_PROTO_H_

#include <stddef.h>
#include <stdint.h>

#include "perfetto/protozero/message.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/proto_decoder.h"
#include "perfetto/protozero/proto_utils.h"

namespace perfetto {
namespace protos {
namespace pbzero {

enum ChromeFrameReporter_FrameDropReason : int32_t;
enum ChromeFrameReporter_ScrollState : int32_t;
enum ChromeFrameReporter_State : int32_t;

enum ChromeFrameReporter_State : int32_t {
  ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED = 0,
  ChromeFrameReporter_State_STATE_PRESENTED_ALL = 1,
  ChromeFrameReporter_State_STATE_PRESENTED_PARTIAL = 2,
  ChromeFrameReporter_State_STATE_DROPPED = 3,
};

const ChromeFrameReporter_State ChromeFrameReporter_State_MIN = ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED;
const ChromeFrameReporter_State ChromeFrameReporter_State_MAX = ChromeFrameReporter_State_STATE_DROPPED;

enum ChromeFrameReporter_FrameDropReason : int32_t {
  ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED = 0,
  ChromeFrameReporter_FrameDropReason_REASON_DISPLAY_COMPOSITOR = 1,
  ChromeFrameReporter_FrameDropReason_REASON_MAIN_THREAD = 2,
  ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR = 3,
};

const ChromeFrameReporter_FrameDropReason ChromeFrameReporter_FrameDropReason_MIN = ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED;
const ChromeFrameReporter_FrameDropReason ChromeFrameReporter_FrameDropReason_MAX = ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR;

enum ChromeFrameReporter_ScrollState : int32_t {
  ChromeFrameReporter_ScrollState_SCROLL_NONE = 0,
  ChromeFrameReporter_ScrollState_SCROLL_MAIN_THREAD = 1,
  ChromeFrameReporter_ScrollState_SCROLL_COMPOSITOR_THREAD = 2,
};

const ChromeFrameReporter_ScrollState ChromeFrameReporter_ScrollState_MIN = ChromeFrameReporter_ScrollState_SCROLL_NONE;
const ChromeFrameReporter_ScrollState ChromeFrameReporter_ScrollState_MAX = ChromeFrameReporter_ScrollState_SCROLL_COMPOSITOR_THREAD;

class ChromeFrameReporter_Decoder : public ::protozero::TypedProtoDecoder</*MAX_FIELD_ID=*/9, /*HAS_NONPACKED_REPEATED_FIELDS=*/false> {
 public:
  ChromeFrameReporter_Decoder(const uint8_t* data, size_t len) : TypedProtoDecoder(data, len) {}
  explicit ChromeFrameReporter_Decoder(const std::string& raw) : TypedProtoDecoder(reinterpret_cast<const uint8_t*>(raw.data()), raw.size()) {}
  explicit ChromeFrameReporter_Decoder(const ::protozero::ConstBytes& raw) : TypedProtoDecoder(raw.data, raw.size) {}
  bool has_state() const { return at<1>().valid(); }
  int32_t state() const { return at<1>().as_int32(); }
  bool has_reason() const { return at<2>().valid(); }
  int32_t reason() const { return at<2>().as_int32(); }
  bool has_frame_source() const { return at<3>().valid(); }
  uint64_t frame_source() const { return at<3>().as_uint64(); }
  bool has_frame_sequence() const { return at<4>().valid(); }
  uint64_t frame_sequence() const { return at<4>().as_uint64(); }
  bool has_affects_smoothness() const { return at<5>().valid(); }
  bool affects_smoothness() const { return at<5>().as_bool(); }
  bool has_scroll_state() const { return at<6>().valid(); }
  int32_t scroll_state() const { return at<6>().as_int32(); }
  bool has_has_main_animation() const { return at<7>().valid(); }
  bool has_main_animation() const { return at<7>().as_bool(); }
  bool has_has_compositor_animation() const { return at<8>().valid(); }
  bool has_compositor_animation() const { return at<8>().as_bool(); }
  bool has_has_smooth_input_main() const { return at<9>().valid(); }
  bool has_smooth_input_main() const { return at<9>().as_bool(); }
};

class ChromeFrameReporter : public ::protozero::Message {
 public:
  using Decoder = ChromeFrameReporter_Decoder;
  enum : int32_t {
    kStateFieldNumber = 1,
    kReasonFieldNumber = 2,
    kFrameSourceFieldNumber = 3,
    kFrameSequenceFieldNumber = 4,
    kAffectsSmoothnessFieldNumber = 5,
    kScrollStateFieldNumber = 6,
    kHasMainAnimationFieldNumber = 7,
    kHasCompositorAnimationFieldNumber = 8,
    kHasSmoothInputMainFieldNumber = 9,
  };
  using State = ::perfetto::protos::pbzero::ChromeFrameReporter_State;
  using FrameDropReason = ::perfetto::protos::pbzero::ChromeFrameReporter_FrameDropReason;
  using ScrollState = ::perfetto::protos::pbzero::ChromeFrameReporter_ScrollState;
  static const State STATE_NO_UPDATE_DESIRED = ChromeFrameReporter_State_STATE_NO_UPDATE_DESIRED;
  static const State STATE_PRESENTED_ALL = ChromeFrameReporter_State_STATE_PRESENTED_ALL;
  static const State STATE_PRESENTED_PARTIAL = ChromeFrameReporter_State_STATE_PRESENTED_PARTIAL;
  static const State STATE_DROPPED = ChromeFrameReporter_State_STATE_DROPPED;
  static const FrameDropReason REASON_UNSPECIFIED = ChromeFrameReporter_FrameDropReason_REASON_UNSPECIFIED;
  static const FrameDropReason REASON_DISPLAY_COMPOSITOR = ChromeFrameReporter_FrameDropReason_REASON_DISPLAY_COMPOSITOR;
  static const FrameDropReason REASON_MAIN_THREAD = ChromeFrameReporter_FrameDropReason_REASON_MAIN_THREAD;
  static const FrameDropReason REASON_CLIENT_COMPOSITOR = ChromeFrameReporter_FrameDropReason_REASON_CLIENT_COMPOSITOR;
  static const ScrollState SCROLL_NONE = ChromeFrameReporter_ScrollState_SCROLL_NONE;
  static const ScrollState SCROLL_MAIN_THREAD = ChromeFrameReporter_ScrollState_SCROLL_MAIN_THREAD;
  static const ScrollState SCROLL_COMPOSITOR_THREAD = ChromeFrameReporter_ScrollState_SCROLL_COMPOSITOR_THREAD;
  void set_state(::perfetto::protos::pbzero::ChromeFrameReporter_State value) {
    AppendTinyVarInt(1, value);
  }
  void set_reason(::perfetto::protos::pbzero::ChromeFrameReporter_FrameDropReason value) {
    AppendTinyVarInt(2, value);
  }
  void set_frame_source(uint64_t value) {
    AppendVarInt(3, value);
  }
  void set_frame_sequence(uint64_t value) {
    AppendVarInt(4, value);
  }
  void set_affects_smoothness(bool value) {
    AppendTinyVarInt(5, value);
  }
  void set_scroll_state(::perfetto::protos::pbzero::ChromeFrameReporter_ScrollState value) {
    AppendTinyVarInt(6, value);
  }
  void set_has_main_animation(bool value) {
    AppendTinyVarInt(7, value);
  }
  void set_has_compositor_animation(bool value) {
    AppendTinyVarInt(8, value);
  }
  void set_has_smooth_input_main(bool value) {
    AppendTinyVarInt(9, value);
  }
};

} // Namespace.
} // Namespace.
} // Namespace.
#endif  // Include guard.