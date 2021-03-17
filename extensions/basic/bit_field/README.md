# About

Bit fields are used to pack more variables into a smaller data space.

You must pass size of `BitField` like so:

```cpp
/// \note `uint16_t` is bit field type
using BitField = basic::ConcurrentlyReadBitField<uint16_t>;
```

You must pass size of each field using `DefineFirstValue` and `DefineNextValue`.

`BitField` implementation checks that `offset_sum + field_size <= 8 * sizeof(BitFieldType)`
where offset usually equals to size-es of previous fields.

For example if you want to store integer field
with type `uint16_t` you can use `BitField::DefineFirstValue<uint16_t, 16>;`
or you can use `BitField::DefineFirstValue<uint16_t, 4>;`.
If you used `16` bits, than you will be able to store bigger value
than with `4` bits.
Our `BitField` implementation checks that provided value fits into the bit field.


`ConcurrentlyReadBitField` - BitField that can be written by a single thread
but read by multiple threads.

`SingleThreadedBitField` - BitField intended to be used by a single thread.

## bit masks vs bit fields

If you search for bit masks - see `typed_enum.hpp`.

Unlike `BitField` bit masks can not store arbitrary data.

## Example

```cpp
enum class DynamicRestyleFlags {
  kChildrenOrSiblingsAffectedByFocus = 1 << 0,
  kChildrenOrSiblingsAffectedByHover = 1 << 1,
  kChildrenOrSiblingsAffectedByActive = 1 << 2,
  kChildrenOrSiblingsAffectedByDrag = 1 << 3,
  kChildrenAffectedByFirstChildRules = 1 << 4,
  kChildrenAffectedByLastChildRules = 1 << 5,
  kChildrenAffectedByDirectAdjacentRules = 1 << 6,
  kChildrenAffectedByIndirectAdjacentRules = 1 << 7,
  kChildrenAffectedByForwardPositionalRules = 1 << 8,
  kChildrenAffectedByBackwardPositionalRules = 1 << 9,
  kAffectedByFirstChildRules = 1 << 10,
  kAffectedByLastChildRules = 1 << 11,
  kChildrenOrSiblingsAffectedByFocusWithin = 1 << 12,
  kChildrenOrSiblingsAffectedByFocusVisible = 1 << 13,

  kNumberOfDynamicRestyleFlags = 14,

  kChildrenAffectedByStructuralRules =
      kChildrenAffectedByFirstChildRules | kChildrenAffectedByLastChildRules |
      kChildrenAffectedByDirectAdjacentRules |
      kChildrenAffectedByIndirectAdjacentRules |
      kChildrenAffectedByForwardPositionalRules |
      kChildrenAffectedByBackwardPositionalRules
};

enum {
  // matches DynamicRestyleFlags::kNumberOfDynamicRestyleFlags
  kNumberOfDynamicRestyleFlags = 14
};

/// \note `uint32_t` is bit field type, type requires 32 bits
using BitField = basic::ConcurrentlyReadBitField<uint32_t>;
/// \note `uint16_t` is associated value type, type requires 16 bits
using RestyleFlags =
    BitField::DefineFirstValue<uint16_t, kNumberOfDynamicRestyleFlags>;
/// \note `bool` is associated value type, type requires 1 bit
using IsElementRareData = RestyleFlags::
    DefineNextValue<bool, 1, basic::BitFieldValueConstness::kConst>;
/// \note `bool` is associated value type, type requires 1 bit
using IsRareData = IsElementRareData::
    DefineNextValue<bool, 1, basic::BitFieldValueConstness::kConst>;

// `IsRareData` and `IsElementRareData` are const
// and can be set in class constructor.
// `RestyleFlags` can change.
BitField bit_field_(RestyleFlags::encode(0) |
                    IsElementRareData::encode(is_element_rare_data) |
                    IsRareData::encode(is_rare_data))


bool HasRestyleFlag(DynamicRestyleFlags mask) const {
  return bit_field_.get<RestyleFlags>() & static_cast<uint16_t>(mask);
}
void SetRestyleFlag(DynamicRestyleFlags mask) {
  bit_field_.set<RestyleFlags>(bit_field_.get<RestyleFlags>() |
                               static_cast<uint16_t>(mask));
  CHECK(bit_field_.get<RestyleFlags>());
}
bool HasRestyleFlags() const { return bit_field_.get<RestyleFlags>(); }
void ClearRestyleFlags() { bit_field_.set<RestyleFlags>(0); }
```

Lets compare `BitField` example above with

```cpp
struct FieldStruct {
  uint16_t RestyleFlags;
  bool IsElementRareData;
  bool IsRareData;
}
```

Unlike `BitField` code above includes alignment padding,
see https://riptutorial.com/c/example/19968/bit-field-alignment

What about C++ syntax for `bit-field-struct`?

```cpp
struct FieldStruct {
  uint16_t RestyleFlags : 16;
  bool IsElementRareData : 1;
  bool IsRareData : 1;
}
```

`bit-field-struct` actual memory layout is implementation defined:
if the memory layout must follow a precise specification,
bitfields should not be used and hand-coded bit manipulations may be required.

The handing of signed values in signed typed `bit-field-structs`
is implementation defined.
If signed values are packed into a range of bits,
it may be more reliable to hand-code the access functions.

Any portable code that uses `bit-field-struct` seems to distinguish
between little- and big-endian platforms.
https://stackoverflow.com/a/6044223

For example, the 'wire' protocol for communications or file format layout
have strict requirements and must be portable.
Using `bit-field-struct` to model them means
that you have to rely on implementation-defined
and - even worse - the unspecified behavior
of how the compiler will layout the bit-field.

The only portable solution is to use the
bit-wise operators instead of bit fields.
Our `BitField` implementation uses bit-wise operators.

Also remember that if you are writing cross platform code,
then never just write out a struct as a binary object.
Besides the endian byte issues described,
there can be all kinds of packing and formatting issues between compilers.
