// mojo/public/mojom/base/time.mojom-blink.h is auto generated by mojom_bindings_generator.py, do not edit

// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_MOJOM_BASE_TIME_MOJOM_BLINK_H_
#define MOJO_PUBLIC_MOJOM_BASE_TIME_MOJOM_BLINK_H_

#include <stdint.h>

#include <limits>
#include <type_traits>
#include <utility>

#include "base/callback.h"
#include "base/macros.h"
#include "base/optional.h"

#include "mojo/public/cpp/bindings/clone_traits.h"
#include "mojo/public/cpp/bindings/equals_traits.h"
#include "mojo/public/cpp/bindings/lib/serialization.h"
#include "mojo/public/cpp/bindings/struct_ptr.h"
#include "mojo/public/cpp/bindings/struct_traits.h"
#include "mojo/public/cpp/bindings/union_traits.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value_forward.h"
#include "mojo/public/mojom/base/time.mojom-shared.h"
#include "mojo/public/mojom/base/time.mojom-blink-forward.h"

#include "mojo/public/cpp/bindings/lib/wtf_clone_equals_util.h"
#include "mojo/public/cpp/bindings/lib/wtf_hash_util.h"
#include "third_party/blink/renderer/platform/wtf/hash_functions.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"




#include "mojo/public/cpp/base/time_mojom_traits.h"
#include "base/component_export.h"

#ifdef KYTHE_IS_RUNNING
#pragma kythe_inline_metadata "Metadata comment"
#endif


namespace mojo_base {
namespace mojom {
namespace blink {





// @generated_from: mojo_base.mojom.Time
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) Time {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<Time, T>::value>;
  using DataView = TimeDataView;
  using Data_ = internal::Time_Data;

  template <typename... Args>
  static TimePtr New(Args&&... args) {
    return TimePtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TimePtr From(const U& u) {
    return mojo::TypeConverter<TimePtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, Time>::Convert(*this);
  }


  Time();

  explicit Time(
      int64_t internal_value);

  ~Time();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TimePtr>
  TimePtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, Time::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, Time::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  template <typename UserType>
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        Time::DataView, WTF::Vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        Time::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::Time_UnserializedMessageContext<
            UserType, Time::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<Time::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return Time::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::Time_UnserializedMessageContext<
            UserType, Time::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<Time::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.Time.internal_value
  int64_t internal_value;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, Time::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, Time::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, Time::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, Time::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}





// @generated_from: mojo_base.mojom.TimeDelta
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) TimeDelta {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<TimeDelta, T>::value>;
  using DataView = TimeDeltaDataView;
  using Data_ = internal::TimeDelta_Data;

  template <typename... Args>
  static TimeDeltaPtr New(Args&&... args) {
    return TimeDeltaPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TimeDeltaPtr From(const U& u) {
    return mojo::TypeConverter<TimeDeltaPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TimeDelta>::Convert(*this);
  }


  TimeDelta();

  explicit TimeDelta(
      int64_t microseconds);

  ~TimeDelta();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TimeDeltaPtr>
  TimeDeltaPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, TimeDelta::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, TimeDelta::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  template <typename UserType>
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TimeDelta::DataView, WTF::Vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TimeDelta::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::TimeDelta_UnserializedMessageContext<
            UserType, TimeDelta::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<TimeDelta::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return TimeDelta::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::TimeDelta_UnserializedMessageContext<
            UserType, TimeDelta::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<TimeDelta::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.TimeDelta.microseconds
  int64_t microseconds;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, TimeDelta::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, TimeDelta::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, TimeDelta::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, TimeDelta::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}





// @generated_from: mojo_base.mojom.TimeTicks
class COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) TimeTicks {
 public:
  template <typename T>
  using EnableIfSame = std::enable_if_t<std::is_same<TimeTicks, T>::value>;
  using DataView = TimeTicksDataView;
  using Data_ = internal::TimeTicks_Data;

  template <typename... Args>
  static TimeTicksPtr New(Args&&... args) {
    return TimeTicksPtr(
        base::in_place, std::forward<Args>(args)...);
  }

  template <typename U>
  static TimeTicksPtr From(const U& u) {
    return mojo::TypeConverter<TimeTicksPtr, U>::Convert(u);
  }

  template <typename U>
  U To() const {
    return mojo::TypeConverter<U, TimeTicks>::Convert(*this);
  }


  TimeTicks();

  explicit TimeTicks(
      int64_t internal_value);

  ~TimeTicks();

  // Clone() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Clone() or copy
  // constructor/assignment are available for members.
  template <typename StructPtrType = TimeTicksPtr>
  TimeTicksPtr Clone() const;

  // Equals() is a template so it is only instantiated if it is used. Thus, the
  // bindings generator does not need to know whether Equals() or == operator
  // are available for members.
  template <typename T, TimeTicks::EnableIfSame<T>* = nullptr>
  bool Equals(const T& other) const;

  template <typename T, TimeTicks::EnableIfSame<T>* = nullptr>
  bool operator==(const T& rhs) const { return Equals(rhs); }
  template <typename UserType>
  static WTF::Vector<uint8_t> Serialize(UserType* input) {
    return mojo::internal::SerializeImpl<
        TimeTicks::DataView, WTF::Vector<uint8_t>>(input);
  }

  template <typename UserType>
  static mojo::Message SerializeAsMessage(UserType* input) {
    return mojo::internal::SerializeAsMessageImpl<
        TimeTicks::DataView>(input);
  }

  // The returned Message is serialized only if the message is moved
  // cross-process or cross-language. Otherwise if the message is Deserialized
  // as the same UserType |input| will just be moved to |output| in
  // DeserializeFromMessage.
  template <typename UserType>
  static mojo::Message WrapAsMessage(UserType input) {
    return mojo::Message(std::make_unique<
        internal::TimeTicks_UnserializedMessageContext<
            UserType, TimeTicks::DataView>>(0, 0, std::move(input)),
        MOJO_CREATE_MESSAGE_FLAG_NONE);
  }

  template <typename UserType>
  static bool Deserialize(const void* data,
                          size_t data_num_bytes,
                          UserType* output) {
    mojo::Message message;
    return mojo::internal::DeserializeImpl<TimeTicks::DataView>(
        message, data, data_num_bytes, output, Validate);
  }

  template <typename UserType>
  static bool Deserialize(const WTF::Vector<uint8_t>& input,
                          UserType* output) {
    return TimeTicks::Deserialize(
        input.size() == 0 ? nullptr : &input.front(), input.size(), output);
  }

  template <typename UserType>
  static bool DeserializeFromMessage(mojo::Message input,
                                     UserType* output) {
    auto context = input.TakeUnserializedContext<
        internal::TimeTicks_UnserializedMessageContext<
            UserType, TimeTicks::DataView>>();
    if (context) {
      *output = std::move(context->TakeData());
      return true;
    }
    input.SerializeIfNecessary();
    return mojo::internal::DeserializeImpl<TimeTicks::DataView>(
        input, input.payload(), input.payload_num_bytes(), output, Validate);
  }

  
// @generated_from: mojo_base.mojom.TimeTicks.internal_value
  int64_t internal_value;

  // Serialise this struct into a trace.
  void WriteIntoTracedValue(perfetto::TracedValue context) const;

 private:
  static bool Validate(const void* data,
                       mojo::internal::ValidationContext* validation_context);
};

// The comparison operators are templates, so they are only instantiated if they
// are used. Thus, the bindings generator does not need to know whether
// comparison operators are available for members.
template <typename T, TimeTicks::EnableIfSame<T>* = nullptr>
bool operator<(const T& lhs, const T& rhs);

template <typename T, TimeTicks::EnableIfSame<T>* = nullptr>
bool operator<=(const T& lhs, const T& rhs) {
  return !(rhs < lhs);
}

template <typename T, TimeTicks::EnableIfSame<T>* = nullptr>
bool operator>(const T& lhs, const T& rhs) {
  return rhs < lhs;
}

template <typename T, TimeTicks::EnableIfSame<T>* = nullptr>
bool operator>=(const T& lhs, const T& rhs) {
  return !(lhs < rhs);
}






template <typename StructPtrType>
TimePtr Time::Clone() const {
  return New(
      mojo::Clone(internal_value)
  );
}

template <typename T, Time::EnableIfSame<T>*>
bool Time::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->internal_value, other_struct.internal_value))
    return false;
  return true;
}

template <typename T, Time::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.internal_value < rhs.internal_value)
    return true;
  if (rhs.internal_value < lhs.internal_value)
    return false;
  return false;
}
template <typename StructPtrType>
TimeDeltaPtr TimeDelta::Clone() const {
  return New(
      mojo::Clone(microseconds)
  );
}

template <typename T, TimeDelta::EnableIfSame<T>*>
bool TimeDelta::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->microseconds, other_struct.microseconds))
    return false;
  return true;
}

template <typename T, TimeDelta::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.microseconds < rhs.microseconds)
    return true;
  if (rhs.microseconds < lhs.microseconds)
    return false;
  return false;
}
template <typename StructPtrType>
TimeTicksPtr TimeTicks::Clone() const {
  return New(
      mojo::Clone(internal_value)
  );
}

template <typename T, TimeTicks::EnableIfSame<T>*>
bool TimeTicks::Equals(const T& other_struct) const {
  if (!mojo::Equals(this->internal_value, other_struct.internal_value))
    return false;
  return true;
}

template <typename T, TimeTicks::EnableIfSame<T>*>
bool operator<(const T& lhs, const T& rhs) {
  if (lhs.internal_value < rhs.internal_value)
    return true;
  if (rhs.internal_value < lhs.internal_value)
    return false;
  return false;
}


}  // namespace blink
}  // namespace mojom
}  // namespace mojo_base

namespace mojo {


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) StructTraits<::mojo_base::mojom::blink::Time::DataView,
                                         ::mojo_base::mojom::blink::TimePtr> {
  static bool IsNull(const ::mojo_base::mojom::blink::TimePtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::blink::TimePtr* output) { output->reset(); }

  static decltype(::mojo_base::mojom::blink::Time::internal_value) internal_value(
      const ::mojo_base::mojom::blink::TimePtr& input) {
    return input->internal_value;
  }

  static bool Read(::mojo_base::mojom::blink::Time::DataView input, ::mojo_base::mojom::blink::TimePtr* output);
};


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) StructTraits<::mojo_base::mojom::blink::TimeDelta::DataView,
                                         ::mojo_base::mojom::blink::TimeDeltaPtr> {
  static bool IsNull(const ::mojo_base::mojom::blink::TimeDeltaPtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::blink::TimeDeltaPtr* output) { output->reset(); }

  static decltype(::mojo_base::mojom::blink::TimeDelta::microseconds) microseconds(
      const ::mojo_base::mojom::blink::TimeDeltaPtr& input) {
    return input->microseconds;
  }

  static bool Read(::mojo_base::mojom::blink::TimeDelta::DataView input, ::mojo_base::mojom::blink::TimeDeltaPtr* output);
};


template <>
struct COMPONENT_EXPORT(MOJO_BASE_MOJOM_BLINK) StructTraits<::mojo_base::mojom::blink::TimeTicks::DataView,
                                         ::mojo_base::mojom::blink::TimeTicksPtr> {
  static bool IsNull(const ::mojo_base::mojom::blink::TimeTicksPtr& input) { return !input; }
  static void SetToNull(::mojo_base::mojom::blink::TimeTicksPtr* output) { output->reset(); }

  static decltype(::mojo_base::mojom::blink::TimeTicks::internal_value) internal_value(
      const ::mojo_base::mojom::blink::TimeTicksPtr& input) {
    return input->internal_value;
  }

  static bool Read(::mojo_base::mojom::blink::TimeTicks::DataView input, ::mojo_base::mojom::blink::TimeTicksPtr* output);
};

}  // namespace mojo

#endif  // MOJO_PUBLIC_MOJOM_BASE_TIME_MOJOM_BLINK_H_

/* Metadata comment
eyJtZXRhIjogW3siZW5kIjogMTYzMSwgImJlZ2luIjogMTYyNywgImVkZ2UiOiAiJS9reXRoZS9l
ZGdlL2dlbmVyYXRlcyIsICJ0eXBlIjogImFuY2hvcl9kZWZpbmVzIiwgInZuYW1lIjogeyJjb3Jw
dXMiOiAiY2hyb21pdW0uZ29vZ2xlc291cmNlLmNvbS9jaHJvbWl1bS9zcmMiLCAibGFuZ3VhZ2Ui
OiAibW9qb20iLCAic2lnbmF0dXJlIjogIm1vam9fYmFzZS5tb2pvbS5UaW1lIn19LCB7ImVuZCI6
IDUwNTIsICJiZWdpbiI6IDUwMzgsICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAi
dHlwZSI6ICJhbmNob3JfZGVmaW5lcyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdv
b2dsZXNvdXJjZS5jb20vY2hyb21pdW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25h
dHVyZSI6ICJtb2pvX2Jhc2UubW9qb20uVGltZS5pbnRlcm5hbF92YWx1ZSJ9fSwgeyJlbmQiOiA2
MDg3LCAiYmVnaW4iOiA2MDc4LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5
cGUiOiAiYW5jaG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29n
bGVzb3VyY2UuY29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1
cmUiOiAibW9qb19iYXNlLm1vam9tLlRpbWVEZWx0YSJ9fSwgeyJlbmQiOiA5NjI3LCAiYmVnaW4i
OiA5NjE1LCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5jaG9y
X2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2UuY29t
L2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9qb19i
YXNlLm1vam9tLlRpbWVEZWx0YS5taWNyb3NlY29uZHMifX0sIHsiZW5kIjogMTA2ODIsICJiZWdp
biI6IDEwNjczLCAiZWRnZSI6ICIlL2t5dGhlL2VkZ2UvZ2VuZXJhdGVzIiwgInR5cGUiOiAiYW5j
aG9yX2RlZmluZXMiLCAidm5hbWUiOiB7ImNvcnB1cyI6ICJjaHJvbWl1bS5nb29nbGVzb3VyY2Uu
Y29tL2Nocm9taXVtL3NyYyIsICJsYW5ndWFnZSI6ICJtb2pvbSIsICJzaWduYXR1cmUiOiAibW9q
b19iYXNlLm1vam9tLlRpbWVUaWNrcyJ9fSwgeyJlbmQiOiAxNDIyOCwgImJlZ2luIjogMTQyMTQs
ICJlZGdlIjogIiUva3l0aGUvZWRnZS9nZW5lcmF0ZXMiLCAidHlwZSI6ICJhbmNob3JfZGVmaW5l
cyIsICJ2bmFtZSI6IHsiY29ycHVzIjogImNocm9taXVtLmdvb2dsZXNvdXJjZS5jb20vY2hyb21p
dW0vc3JjIiwgImxhbmd1YWdlIjogIm1vam9tIiwgInNpZ25hdHVyZSI6ICJtb2pvX2Jhc2UubW9q
b20uVGltZVRpY2tzLmludGVybmFsX3ZhbHVlIn19XSwgInR5cGUiOiAia3l0aGUwIn0=
*/