// Copyright 2020 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <base/logging.h>
#include <base/macros.h>
#include <base/compiler_specific.h>
#include <base/check.h>

#include <atomic>

// Bit fields are used to pack more variables into a smaller data space.
//
/// \note `BitField` can store only primitive types
//
// You must pass size of each field using `DefineFirstValue` and `DefineNextValue`.
//
// For example if you want to store 2 byte unsigned integer field
// with type `uint16_t`:
// `BitField::DefineFirstValue<uint16_t, 16>;`.
//
/// \note If you search for bit masks - see `typed_enum.h`.
/// Unlike `BitField` bit masks can not store arbitrary data.
//
namespace basic {

namespace internal {

/// \todo replace these casts with std::atomic_ref (C++20) once it
/// becomes available
template <typename T>
ALWAYS_INLINE std::atomic<T>* AsAtomicPtr(T* t) {
  return reinterpret_cast<std::atomic<T>*>(t);
}
template <typename T>
ALWAYS_INLINE const std::atomic<T>* AsAtomicPtr(const T* t) {
  return reinterpret_cast<const std::atomic<T>*>(t);
}

} // namespace internal

enum class BitFieldValueConstness {
  kNonConst,
  kConst,
};

namespace internal {

template <class BitFieldType>
class BitFieldBase;

// Helper class for defining values in a bit field. This helper provides
// utilities to read, write and update the value in the bit field.
//
/// \note size in bits
//
template <class ValueType,
          size_t offset,
          size_t size,
          class BitFieldType,
          BitFieldValueConstness is_const = BitFieldValueConstness::kNonConst>
class BitFieldValue final {
  static_assert(std::is_fundamental<ValueType>::value,
                "Fields in a bit field must be of a primitive type.");
  static_assert(std::is_fundamental<BitFieldType>::value,
                "Bit fields must be of a primitive type.");
  static_assert(std::is_unsigned<BitFieldType>::value,
                "Bit field must be of an unsigned type");
  static_assert(sizeof(ValueType) <= sizeof(BitFieldType),
                "Value in bit field cannot be bigger than the bit field");
  // sizeof in bytes, but `offset` and `size` in bits, so multiply bits by 8
  static_assert(
      offset < 8 * sizeof(BitFieldType),
      "Field offset in bit field must be smaller than the bit field size");
  static_assert(
      size < 8 * sizeof(BitFieldType),
      "Field size in bit field must be smaller than the bit field size");
  static_assert(offset + size <= 8 * sizeof(BitFieldType),
                "Field in bit field cannot overflow the bit field");
  static_assert(size > 0, "Bit field fields cannot have 0 size.");

 public:
  using Type = ValueType;
  using BitType = BitFieldType;

  template <class OtherValueType,
            int other_size,
            BitFieldValueConstness other_is_const =
                BitFieldValueConstness::kNonConst>
  using DefineNextValue = BitFieldValue<OtherValueType,
                                        offset + size,
                                        other_size,
                                        BitFieldType,
                                        other_is_const>;

  // Create a bit field with the given value.
  static constexpr BitFieldType encode(ValueType value) {
    DCHECK(is_valid(value));
    return static_cast<BitFieldType>(value) << offset;
  }

  // Update a bit field with the given value.
  static constexpr BitFieldType update(BitFieldType previous, ValueType value) {
    return (previous & ~kMask) | encode(value);
  }

  // Read the value from the bit field.
  static constexpr ValueType decode(BitFieldType value) {
    return static_cast<ValueType>((value & kMask) >> offset);
  }

 private:
  static constexpr BitFieldValueConstness kIsConst = is_const;

  static constexpr BitFieldType kValidationMask =
      (BitFieldType{1} << size) - BitFieldType{1};
  static constexpr BitFieldType kMask = (kValidationMask) << offset;
  static_assert(kMask != 0, "Mask in which all bits are 0 is not allowed.");
  static_assert(~kMask != 0, "Mask in which all bits are 1 is not allowed.");

  // Confirm that the provided value fits into the bit field.
  static constexpr bool is_valid(ValueType value) {
    return (static_cast<BitFieldType>(value) & ~kValidationMask) == 0;
  }

  friend class BitFieldBase<BitFieldType>;
};

}  // namespace internal

// BitField intended to be used by a single thread.
template <class BitFieldType>
class BASE_EXPORT SingleThreadedBitField {
  static_assert(std::is_fundamental<BitFieldType>::value,
                "Bit fields must be of a primitive type.");
  static_assert(std::is_unsigned<BitFieldType>::value,
                "Bit field must be of an unsigned type");

 public:
  /// \note size in bits
  //
  template <class Type,
            int size,
            BitFieldValueConstness is_const = BitFieldValueConstness::kNonConst>
  using DefineFirstValue =
      internal::BitFieldValue<Type, /* offset */ 0, size, BitFieldType, is_const>;

  explicit SingleThreadedBitField() : SingleThreadedBitField(0) {}
  explicit SingleThreadedBitField(BitFieldType bits) : bits_(bits) {}

  template <typename Value>
  typename Value::Type get() const {
    return Value::decode(bits_);
  }

  template <typename Value>
  void set(typename Value::Type value) {
    bits_ = Value::update(bits_, value);
  }

 protected:
  BitFieldType bits_;
};

// BitField that can be written by a single thread but read by multiple threads.
template <class BitFieldType>
class BASE_EXPORT ConcurrentlyReadBitField
    : public SingleThreadedBitField<BitFieldType> {
  using Base = SingleThreadedBitField<BitFieldType>;
  using Base::bits_;

 public:
  explicit ConcurrentlyReadBitField() : Base(0) {}
  explicit ConcurrentlyReadBitField(BitFieldType bits) : Base(bits) {}

  template <typename Value>
  typename Value::Type get_concurrently() const {
    return Value::decode(internal::AsAtomicPtr(&bits_)->load(std::memory_order_relaxed));
  }

  template <typename Value>
  void set(typename Value::Type value) {
    internal::AsAtomicPtr(&bits_)->store(Value::update(bits_, value),
                               std::memory_order_relaxed);
  }
};

}  // namespace basic
