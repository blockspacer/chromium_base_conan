#pragma once

#include <cstdint>
#include <string>
#include <optional>
#include <functional>
#include <unordered_map>

#include <base/logging.h>
#include <base/trace_event/trace_event.h>

// Fixed-size circular buffer that stores tick numbers (seq. num.) mapped to some data
// (usually stores snapshots of server state at specific loop iteration numbers).
// Only latest snapshots saved i.e. `tickNumToBufferIndex`
// maps tick number (from 0 to inf) to buffer index (from 0 to buffer size)
//
namespace backend {

/// \note uint64_t range 0 .. 18,446,744,073,709,551,615
typedef std::uint64_t TickNumType;

typedef size_t TickBufferSizeType;

/// \note keep that data type small,
/// otherwise reserved buffer will take a lot of memory
struct UserCommand
{
  TickNumType tickSeqId = 0;

  /// \note detect missing packets at the end of the tick
  /// and fill 'holes', for example - by predicting movement
  /// based on client's input from prev. tick
  bool isDropped = false;
};

/// \note expected to work with ordeded sequence num. (tick num.)
/// without holes or duplication.
/// i.e. server snapshot generation using LatestTickBuffer
/// will store N last snapshots made by server
/// \note conatainer expects that mapping tick num. to value
/// is not frequent operation
// stores two buffers:
// 1) buffer of values i.e.
//    [Snapshot4, Snapshot2, Snapshot3]
// 2) buffer that maps tick num. to value i.e.
//    [tick4, tick2, tick3]
template<typename Type, TickBufferSizeType Size>
class LatestTickBuffer {
public:
  typedef std::function<
    void(const Type&, const TickNumType&)
  > EachCb;

public:
  LatestTickBuffer() {
    clear();
  }

  void each(const EachCb& cb) {
    DCHECK(cb);
    for(size_t i = 0; i < buffer_.size(); i++)
    {
      const bool has_value
        = sequences_[i].has_value();
      if(has_value) {
        cb(buffer_[i], sequences_[i].value());
      }
    }
  }

  size_t size() const {
    return buffer_.size();
  }

  void clear()
  {
    for (int i = 0; i < sequences_.size(); ++i) {
      sequences_[i] = std::nullopt;
    }
  }

  TickNumType latestTick() const noexcept
  {
    return latestTick_;
  }

  void setByTickNum(const Type& value, const TickNumType tickNum)
  {
    const size_t tickIndex = tickNumToBufferIndex(tickNum);

    DCHECK(tickIndex >= 0);
    DCHECK(tickIndex < buffer_.size());
    buffer_[tickIndex] = value;
    sequences_[tickIndex] = tickNum;
    if(tickNum > latestTick_) {
      latestTick_ = tickNum;
    }
  }

  MUST_USE_RETURN_VALUE
  bool hasValue(TickNumType tickNum) const
  {
    const size_t tickIndex = tickNumToBufferIndex(tickNum);

    const bool has_value
      = sequences_[tickIndex].has_value();

    // if we have value, than we expect valid seq. num.
    DCHECK(has_value
      ? (sequences_[tickIndex].value() == tickNum)
      : true)
      << " something went wrong for tickIndex = "
      << tickIndex;

    return has_value;
  }

  MUST_USE_RETURN_VALUE
  bool tryGetValue(TickNumType tickNum, Type* result)
  {
    const size_t tickIndex = tickNumToBufferIndex(tickNum);
    DCHECK(tickIndex >= 0);
    DCHECK(tickIndex < buffer_.size());
    *result = buffer_[tickIndex];

    if(!sequences_[tickIndex].has_value()
       // if we have value, than we expect valid seq. num.
       || sequences_[tickIndex].value() != tickNum)
    {
      DCHECK(false)
        << " something went wrong for tickIndex = "
        << tickIndex;
      return false;
    }

    return true;
  }

  MUST_USE_RETURN_VALUE
  size_t tickNumToBufferIndex(const TickNumType tickNum) const
  {
    /// \note tickNum must start from 1
    DCHECK(tickNum > 0);
    DCHECK(tickNum < std::numeric_limits<TickNumType>::max());

    /// \n example:
    ///  when buffer size = 6:
    ///    tickNum = 1 => buffer[1 % 6] => buffer[1]
    ///    tickNum = 6 => buffer[6 % 6] => buffer[0]
    ///    tickNum = 7 => buffer[7 % 6] => buffer[1]
    ///    tickNum = 63 => buffer[63 % 6] => buffer[3]
    const TickNumType tickIndex = tickNum % buffer_.size();
    return tickIndex;
  }

private:
  TickBufferSizeType maxBufferSize_ = Size;

  TickNumType latestTick_ = 0;

  // maps buffer index (from 0 to buffer size) to tick num. (from 0 to inf)
  // i.e. sequences_[maxBufferSize_] == latestTick_
  // i.e. sequences_[maxBufferSize_ - 1] == latestTick_ - 1
  // i.e. sequences_[maxBufferSize_ - 2] == latestTick_ - 2
  std::array<std::optional<TickNumType>, Size> sequences_{};

  // maps buffer index (from 0 to buffer size) to snapshot with custom data
  // i.e. buffer_[latestTick_] == Type{...}
  std::array<Type, Size> buffer_{};
};

} // namespace backend
