// Copyright (c) YugaByte, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
// in compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" basic, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied.  See the License for the specific language governing permissions and limitations
// under the License.
//

#include "basic/jsonb/jsonb.h"

#include "base/strings/utf_string_conversions.h"
#include "base/big_endian.h"
#include "base/notreached.h"
#include "base/strings/string_util.h"
#include "base/json/json_string_value_serializer.h"

using namespace basic::error;

namespace basic {

// We are flipping the sign bit of 64-bit integers appearing as object keys in a document so that
// negative numbers sort earlier.
constexpr uint64_t kInt64SignBitFlipMask = 0x8000000000000000L;
constexpr uint32_t kInt32SignBitFlipMask = 0x80000000;

template <class Buffer>
void AppendDoubleToKey(double val, Buffer* dest, bool descending = false) {
  char buf[sizeof(uint64_t)];
  uint64_t v = *(reinterpret_cast<uint64_t*>(&val));
  if (v >> 63) { // This is the sign bit: better than using val >= 0 (because -0, nulls denormals).
    v = ~v;
  } else {
    v ^= kInt64SignBitFlipMask;
  }

  if (descending) {
    // flip the bits to reverse the order.
    v = ~v;
  }
  base::BigEndianWriter writer(buf, sizeof(buf));
  if(!writer.WriteU64(v)) {
    DCHECK(false);
  }
  dest->append(buf, sizeof(buf));
}

template <class Buffer>
void AppendInt32ToKey(int32_t val, Buffer* dest) {
  char buf[sizeof(int32_t)];
  base::BigEndianWriter writer(buf, sizeof(buf));
  if(!writer.WriteU32(val ^ kInt32SignBitFlipMask)) {
    DCHECK(false);
  }
  dest->append(buf, sizeof(buf));
}

template <class Buffer>
void AppendFloatToKey(float val, Buffer* dest, bool descending = false) {
  char buf[sizeof(uint32_t)];
  uint32_t v = *(reinterpret_cast<uint32_t*>(&val));
  if (v >> 31) { // This is the sign bit: better than using val >= 0 (because -0, nulls denormals).
    v = ~v;
  } else {
    v ^= kInt32SignBitFlipMask;
  }

  if (descending) {
    // flip the bits to reverse the order.
    v = ~v;
  }

  base::BigEndianWriter writer(buf, sizeof(buf));
  if(!writer.WriteU32(v)) {
    DCHECK(false);
  }

  dest->append(buf, sizeof(buf));
}

inline int64_t DecodeInt32FromKey(const base::span<const char>& slice) {
  uint32_t v;

  base::BigEndianReader reader(slice.data(), sizeof(slice.data()));
  if(!reader.ReadU32(&v)) {
    DCHECK(false);
  }

  return v ^ kInt32SignBitFlipMask;
}

inline int64_t DecodeInt64FromKey(const base::span<const char>& slice) {
  uint64_t v;

  base::BigEndianReader reader(slice.data(), sizeof(slice.data()));
  if(!reader.ReadU64(&v)) {
    DCHECK(false);
  }

  return v ^ kInt64SignBitFlipMask;
}

inline double DecodeDoubleFromKey(const base::span<const char>& slice, bool descending = false) {
  uint64_t v;

  base::BigEndianReader reader(slice.data(), sizeof(slice.data()));
  if(!reader.ReadU64(&v)) {
    DCHECK(false);
  }

  if (descending) {
    // Flip the bits.
    v = ~v;
  }

  if (v >> 63) { // This is the sign bit: better than using val >= 0 (because -0, nulls denormals).
    v ^= kInt64SignBitFlipMask;
  } else {
    v = ~v;
  }
  return *(reinterpret_cast<double*>(&v));
}

inline float DecodeFloatFromKey(const base::span<const char>& slice, bool descending = false) {
  uint32_t v;

  base::BigEndianReader reader(slice.data(), sizeof(slice.data()));
  if(!reader.ReadU32(&v)) {
    DCHECK(false);
  }

  if (descending) {
    // Flip the bits.
    v = ~v;
  }

  if (v >> 31) { // This is the sign bit: better than using val >= 0 (because -0, nulls denormals).
    v ^= kInt32SignBitFlipMask;
  } else {
    v = ~v;
  }
  return *(reinterpret_cast<float*>(&v));
}

// Encode and append the given signed 64-bit integer to the destination string holding a RocksDB
// key being constructed. We are flipping the sign bit so that negative numbers sort before positive
// ones.
template <class Buffer>
inline void AppendInt64ToKey(int64_t val, Buffer* dest) {
  char buf[sizeof(uint64_t)];
  // Flip the sign bit so that negative values sort before positive ones when compared as
  // big-endian byte sequences.
  base::BigEndianWriter writer(buf, sizeof(buf));
  if(!writer.WriteU64(val ^ kInt64SignBitFlipMask)) {
    DCHECK(false);
  }

  dest->append(buf, sizeof(buf));
}

inline void AppendBigEndianUInt64(uint64_t u, std::string* dest) {
  char buf[sizeof(uint64_t)];

  base::BigEndianWriter writer(buf, sizeof(buf));
  if(!writer.WriteU64(u)) {
    DCHECK(false);
  }

  dest->append(buf, sizeof(buf));
}

bool Jsonb::IsScalar(const JEntry& jentry) {
  uint32_t jentry_type = GetJEType(jentry);
  return ((jentry_type) != kJEIsArray && (jentry_type) != kJEIsObject);
}

size_t Jsonb::ComputeDataOffset(const size_t num_entries, const uint32_t container_type) {
  const size_t num_jentries = (container_type & kJBArray) ? num_entries : 2 * num_entries;
  return sizeof(JsonbHeader) + num_jentries * sizeof(JEntry);
}

Jsonb::Jsonb() {
}

Jsonb::Jsonb(const std::string& jsonb)
    : serialized_jsonb_(jsonb) {
}

Jsonb::Jsonb(std::string&& jsonb)
    : serialized_jsonb_(std::move(jsonb)) {
}

void Jsonb::Assign(const std::string& jsonb) {
  serialized_jsonb_ = jsonb;
}

void Jsonb::Assign(std::string&& jsonb) {
  serialized_jsonb_ = std::move(jsonb);
}

std::string&& Jsonb::MoveSerializedJsonb() {
  return std::move(serialized_jsonb_);
}

const std::string& Jsonb::SerializedJsonb() const {
  return serialized_jsonb_;
}

bool Jsonb::operator==(const Jsonb& other) const {
  return serialized_jsonb_ == other.serialized_jsonb_;
}

Status Jsonb::FromString(const std::string& json) {
  // Parse the json document.
  ::base::JSONReader::ValueWithError root =
    ::base::JSONReader::ReadAndReturnValueWithError(json);
  RETURN_ERROR_IF(!root.value, INTERNAL)
    << "JSON text is corrupt: "
    << root.error_message;

  return FromJson(*root.value);
}

Status Jsonb::FromJson(const base::Value& document) {
  return ToJsonbInternal(document, &serialized_jsonb_);
}

basic::Status Jsonb::ToJsonbInternal(const base::Value& document, std::string* jsonb) {
  if (document.is_dict()) {
    return ToJsonbProcessObject(document, jsonb);
  } else if (document.is_list()) {
    return ToJsonbProcessArray(document, /* is_scalar */ false, jsonb);
  } else {
    // Scalar values are stored as an array with one element with a special field in the header
    // indicating it is a scalar.
    base::ListValue json_array;
    if(document.is_int()) {
      int int_val;
      if(document.GetAsInteger(&int_val))
        json_array.AppendInteger(int_val);
      else
        CHECK(false);
    }
    else if(document.is_double()) {
      double double_val;
      if(document.GetAsDouble(&double_val))
        json_array.AppendDouble(double_val);
      else
        CHECK(false);
    }
    return ToJsonbProcessArray(std::move(json_array), true, jsonb);
  }
}

basic::Status Jsonb::ToJsonbProcessObject(const base::Value& document,
                                           std::string* jsonb) {
  DCHECK(document.is_dict());

  // Use a map since we need to store the keys in sorted order.
  std::map<std::string, const base::Value&> kv_pairs;
  for (const auto& member : document.DictItems()) {
    const auto& key = member.first;
    const auto& value = member.second;
    kv_pairs.emplace(key, value);
  }

  size_t metadata_offset, jsonb_metadata_size;
  std::tie(metadata_offset, jsonb_metadata_size) = ComputeOffsetsAndJsonbHeader(kv_pairs.size(),
                                                                                kJBObject, jsonb);

  // Now append the keys and store the key offsets in the jentry.
  size_t data_begin_offset = jsonb->size();
  for (const auto& entry : kv_pairs) {
    jsonb->append(entry.first);
    auto key_offset = jsonb->size() - data_begin_offset;
    JEntry jentry = GetOffset(key_offset) | kJEIsString; // keys are always strings.

    base::BigEndianWriter writer(&((*jsonb)[metadata_offset]), sizeof(&((*jsonb)[metadata_offset])));
    if(!writer.WriteU32(jentry)) {
      DCHECK(false);
    }

    metadata_offset += sizeof(JEntry);
  }

  // Append the values to the buffer.
  for (const auto& entry : kv_pairs) {
    const base::Value& value = entry.second;
    RETURN_IF_NOT_OK(ProcessJsonValueAndMetadata(value, data_begin_offset, jsonb, &metadata_offset));
  }

  // The metadata slice should now be empty.
  if (data_begin_offset != metadata_offset) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "Couldn't process entire data for json object");
  }

  RETURN_OK();
}

basic::Status Jsonb::ToJsonbProcessArray(const base::Value& document,
                                          const bool is_scalar,
                                          std::string* jsonb) {
  DCHECK(document.is_list());

  const auto& json_array = document.GetList();
  const size_t num_array_entries = json_array.size();

  uint32_t container_type = kJBArray;
  if (is_scalar) {
    // Scalars are an array with one element and the special kJBScalar field set in the header.
    DCHECK_EQ(num_array_entries, 1);
    container_type |= kJBScalar;
  }

  size_t metadata_offset, jsonb_metadata_size;
  std::tie(metadata_offset, jsonb_metadata_size) = ComputeOffsetsAndJsonbHeader(num_array_entries,
                                                                                container_type,
                                                                                jsonb);
  const size_t data_begin_offset = jsonb->size();
  // Append the array members to the buffer.
  for (const base::Value& value : json_array) {
    RETURN_IF_NOT_OK(ProcessJsonValueAndMetadata(value, data_begin_offset, jsonb, &metadata_offset));
  }

  // The metadata base::span<const char> should now be empty.
  if (data_begin_offset != metadata_offset) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "Couldn't process entire data for json array");
  }
  RETURN_OK();
}

std::pair<size_t, size_t> Jsonb::ComputeOffsetsAndJsonbHeader(size_t num_entries,
                                                              uint32_t container_type,
                                                              std::string* jsonb) {
  // Compute the size we need to allocate for the metadata.
  size_t metadata_offset = jsonb->size();
  const size_t jsonb_metadata_size = ComputeDataOffset(num_entries, container_type);

  // Resize the string to fit the jsonb header and the jentry for keys and values.
  jsonb->resize(metadata_offset + jsonb_metadata_size);

  // Store the jsonb header at the appropriate place.
  JsonbHeader jsonb_header = GetCount(num_entries) | container_type;

  base::BigEndianWriter writer(&((*jsonb)[metadata_offset]), sizeof(&((*jsonb)[metadata_offset])));
  if(!writer.WriteU32(jsonb_header)) {
    DCHECK(false);
  }

  metadata_offset += sizeof(JsonbHeader);

  return std::make_pair(metadata_offset, jsonb_metadata_size);
}

basic::Status Jsonb::ProcessJsonValueAndMetadata(const base::Value& value,
                                                  const size_t data_begin_offset,
                                                  std::string* jsonb,
                                                  size_t* metadata_offset) {
  JEntry jentry = 0;
  switch (value.type()) {
    case base::Value::Type::NONE:
      jentry |= kJEIsNull;
      break;
    case base::Value::Type::BOOLEAN:
      value.GetBool()
        ? jentry |= kJEIsBoolFalse
        : jentry |= kJEIsBoolTrue;
      break;
    case base::Value::Type::LIST:
      jentry |= kJEIsArray;
      RETURN_IF_NOT_OK(ToJsonbInternal(value, jsonb));
      break;
    case base::Value::Type::DICTIONARY:
      jentry |= kJEIsObject;
      RETURN_IF_NOT_OK(ToJsonbInternal(value, jsonb));
      break;
    case base::Value::Type::DOUBLE:
      jentry |= kJEIsDouble;
      AppendDoubleToKey(value.GetDouble(), jsonb);
      break;
    case base::Value::Type::INTEGER:
      jentry |= kJEIsInt;
      AppendInt32ToKey(value.GetInt(), jsonb);
      break;
    case base::Value::Type::STRING:
      jentry |= kJEIsString;
      jsonb->append(value.GetString());
      break;
    case base::Value::Type::BINARY:
      NOTIMPLEMENTED();
      return ::basic::Status(
        FROM_HERE, ::basic::error::INTERNAL, "Numeric type is not supported");
    // TODO(crbug.com/859477): Remove after root cause is found.
    case base::Value::Type::DEAD:
      NOTIMPLEMENTED();
      return ::basic::Status(
        FROM_HERE, ::basic::error::INTERNAL, "Numeric type is not supported");
  }

  // Store the offset.
  size_t offset = jsonb->size() - data_begin_offset;
  jentry |= GetOffset(offset);

  // Store the JEntry.
  base::BigEndianWriter writer(&((*jsonb)[*metadata_offset]), sizeof(&((*jsonb)[*metadata_offset])));
  if(!writer.WriteU32(jentry)) {
    DCHECK(false);
  }

  (*metadata_offset) += sizeof(JEntry);

  RETURN_OK();
}

Status Jsonb::FromJsonbInternal(const base::span<const char>& jsonb, base::Value* document) {
  // Read the jsonb header.
  base::BigEndianReader reader(jsonb.data(), sizeof(jsonb.data()));
  JsonbHeader jsonb_header;
  if(!reader.ReadU32(&jsonb_header)) {
    DCHECK(false);
  }

  if ((jsonb_header & kJBObject) == kJBObject) {
    return FromJsonbProcessObject(jsonb, jsonb_header, document);
  } else if ((jsonb_header & kJBArray) == kJBArray) {
    std::unique_ptr<base::ListValue> array_doc = std::make_unique<base::ListValue>();
    RETURN_IF_NOT_OK(FromJsonbProcessArray(jsonb, jsonb_header, (array_doc.get())));

    if ((jsonb_header & kJBScalar) && array_doc->is_list() && array_doc->GetList().size() == 1) {
      // This is actually a scalar, since jsonb stores scalars as arrays with one element.
      // Therefore, just return the single element.
      //*document = base::Value::FromUniquePtrValue(std::make_unique<base::Value>(array_doc->GetList()[0]));
      const base::Value& val = array_doc->GetList()[0];
      if(val.is_int()) {
        int int_val;
        if(val.GetAsInteger(&int_val))
          *document = base::Value::FromUniquePtrValue(std::make_unique<base::Value>(int_val));
        else
          CHECK(false);
      }
      else if(val.is_double()) {
        double double_val;
        if(val.GetAsDouble(&double_val))
          *document = base::Value::FromUniquePtrValue(std::make_unique<base::Value>(double_val));
        else
          CHECK(false);
      }
    } else {
      *document = base::Value::FromUniquePtrValue(std::move(array_doc));
    }
  } else {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "Invalid json type!");
  }
  RETURN_OK();
}

const char kWinLineEnds[] = "\r\n";
const char kLinuxLineEnds[] = "\n";

StatusOr<base::Value> Jsonb::ToJson() const {
  base::Value document;
  RETURN_IF_NOT_OK(FromJsonbInternal(serialized_jsonb_, &document));

  return {std::move(document)};
}

StatusOr<std::string> Jsonb::ToJsonString() const {
  base::Value document;
  RETURN_IF_NOT_OK(FromJsonbInternal(serialized_jsonb_, &document));

  std::string serialized_json;
  JSONStringValueSerializer str_serializer(&serialized_json);
  str_serializer.set_pretty_print(true);
  if(!str_serializer.Serialize(document)) {
    DCHECK(false);
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "Invalid json type!");
  }

  // Unify line endings between platforms.
  base::ReplaceSubstringsAfterOffset(&serialized_json, 0,
                               kWinLineEnds, kLinuxLineEnds);

  return {serialized_json};
}

Status Jsonb::FromJsonbProcessObject(const base::span<const char>& jsonb,
                                     const JsonbHeader& jsonb_header,
                                     base::Value* document) {
  size_t metadata_begin_offset = sizeof(JsonbHeader);

  size_t nelems = GetCount(jsonb_header);
  const size_t data_begin_offset = ComputeDataOffset(nelems, kJBObject);

  // Now read the kv pairs and build the json
  std::unique_ptr<base::DictionaryValue> value = std::make_unique<base::DictionaryValue>();
  *document = base::Value::FromUniquePtrValue(std::move(value));

  for (int i = 0; i < nelems; i++) {
    base::span<const char> key;
    RETURN_IF_NOT_OK(GetObjectKey(i, jsonb, metadata_begin_offset, data_begin_offset, &key));
    base::span<const char> json_value;
    JEntry value_metadata;
    RETURN_IF_NOT_OK(GetObjectValue(i, jsonb, metadata_begin_offset, data_begin_offset, nelems,
                                 &json_value, &value_metadata));
    base::StringPiece json_key(key.data(), key.size());
    switch (GetJEType(value_metadata)) {
      case kJEIsString: {
        document->SetStringKey(json_key, base::StringPiece(json_value.data(), json_value.size()));
        break;
      }
      case kJEIsInt: {
        int32_t value = DecodeInt32FromKey(json_value);
        //AddNumericMember(document, key, value);
        base::StringPiece json_key(key.data(), key.size());
        document->SetIntKey(json_key, value);
        break;
      }
      case kJEIsUInt: {
        uint32_t value;

        base::BigEndianReader reader(json_value.data(), sizeof(json_value.data()));
        if(!reader.ReadU32(&value)) {
          DCHECK(false);
        }

        //AddNumericMember(document, key, value);
        base::StringPiece json_key(key.data(), key.size());
        document->SetIntKey(json_key, value);

        break;
      }
      case kJEIsInt64: {
        int64_t value = DecodeInt64FromKey(json_value);
        //AddNumericMember(document, key, value);
        base::StringPiece json_key(key.data(), key.size());
        document->SetIntKey(json_key, value);
        break;
      }
      case kJEIsUInt64: {
        uint64_t value;

        base::BigEndianReader reader(json_value.data(), sizeof(json_value.data()));
        if(!reader.ReadU64(&value)) {
          DCHECK(false);
        }

        //AddNumericMember(document, key, value);
        base::StringPiece json_key(key.data(), key.size());
        document->SetIntKey(json_key, value);
        break;
      }
      case kJEIsDouble: {
        double value = DecodeDoubleFromKey(json_value);
        //AddNumericMember(document, key, value);
        base::StringPiece json_key(key.data(), key.size());
        document->SetDoubleKey(json_key, value);
        break;
      }
      case kJEIsFloat: {
        float value = DecodeFloatFromKey(json_value);
        //AddNumericMember(document, key, value);
        base::StringPiece json_key(key.data(), key.size());
        document->SetDoubleKey(json_key, value);
        break;
      }
      case kJEIsBoolFalse: {
        document->SetBoolKey(json_key, false);
        break;
      }
      case kJEIsBoolTrue: {
        document->SetBoolKey(json_key, true);
        break;
      }
      case kJEIsNull: {
        document->SetKey(json_key, base::Value(base::Value::Type::NONE));
        break;
      }
      case kJEIsObject: {
        base::Value nested_container(base::Value::Type::DICTIONARY);
        RETURN_IF_NOT_OK(FromJsonbInternal(json_value, &nested_container));
        document->SetKey(json_key,
                            std::move(nested_container));
        break;
      }
      case kJEIsArray: {
        base::Value nested_container(base::Value::Type::LIST);
        RETURN_IF_NOT_OK(FromJsonbInternal(json_value, &nested_container));
        document->SetKey(json_key,
                            std::move(nested_container));
        break;
      }
    }
  }
  RETURN_OK();
}

Status Jsonb::FromJsonbProcessArray(const base::span<const char>& jsonb,
                                    const JsonbHeader& jsonb_header,
                                    base::Value* document) {

  size_t metadata_begin_offset = sizeof(JsonbHeader);
  size_t nelems = GetCount(jsonb_header);
  size_t data_begin_offset = ComputeDataOffset(nelems, kJBArray);

  // Now read the array members.
  std::unique_ptr<base::ListValue> list = std::make_unique<base::ListValue>();

  for (int i = 0; i < nelems; i++) {
    base::span<const char> result;
    JEntry element_metadata;
    RETURN_IF_NOT_OK(GetArrayElement(i, jsonb, metadata_begin_offset, data_begin_offset, &result,
                                  &element_metadata));
    switch (GetJEType(element_metadata)) {
      case kJEIsString: {
        list->Append(std::make_unique<base::Value>(base::StringPiece(result.data(), result.size())));
        break;
      }
      case kJEIsInt: {
        int32_t value = DecodeInt32FromKey(result);
        //PushBackNumericMember((list.get()), value);
        list->AppendInteger(value);
        break;
      }
      case kJEIsUInt: {
        uint32_t value;

        base::BigEndianReader reader(result.data(), sizeof(result.data()));
        if(!reader.ReadU32(&value)) {
          DCHECK(false);
        }

        //PushBackNumericMember((list.get()), value);
        list->AppendInteger(value);
        break;
      }
      case kJEIsInt64: {
        int64_t value = DecodeInt64FromKey(result);
        //PushBackNumericMember((list.get()), value);
        list->AppendInteger(value);
        break;
      }
      case kJEIsUInt64: {
        uint64_t value;

        base::BigEndianReader reader(result.data(), sizeof(result.data()));
        if(!reader.ReadU64(&value)) {
          DCHECK(false);
        }

        //PushBackNumericMember((list.get()), value);
        list->AppendInteger(value);
        break;
      }
      case kJEIsDouble: {
        double value = DecodeDoubleFromKey(result);
        //PushBackNumericMember((list.get()), value);
        list->Append(std::make_unique<base::Value>(value));
        break;
      }
      case kJEIsFloat: {
        float value = DecodeFloatFromKey(result);
        //PushBackNumericMember((list.get()), value);
        list->Append(std::make_unique<base::Value>(value));
        break;
      }
      case kJEIsBoolFalse: {
        list->Append(std::make_unique<base::Value>(false));
        break;
      }
      case kJEIsBoolTrue: {
        list->Append(std::make_unique<base::Value>(true));
        break;
      }
      case kJEIsNull: {
        list->Append(std::make_unique<base::Value>(base::Value::Type::NONE));
        break;
      }
      case kJEIsObject: {
        auto nested_container = std::make_unique<base::Value>(base::Value::Type::DICTIONARY);
        RETURN_IF_NOT_OK(FromJsonbInternal(result, nested_container.get()));
        list->Append(std::move(nested_container));
        break;
      }
      case kJEIsArray: {
        auto nested_container = std::make_unique<base::Value>(base::Value::Type::LIST);
        RETURN_IF_NOT_OK(FromJsonbInternal(result, nested_container.get()));
        list->Append(std::move(nested_container));
        break;
      }
    }
  }

  *document = base::Value::FromUniquePtrValue(std::move(list));

  RETURN_OK();
}

//Status Jsonb::FromJson(const base::Optional<base::Value>& value) {
//  ::base::Optional<std::string> str = base::SerializeToJson(value);
//  EXPECT_FALSE(str.has_value());
//
//  rapidjson::Document document;
//  document.CopyFrom(value, document.GetAllocator());
//  return FromRapidJson(document);
//}

Status Jsonb::GetObjectValue(size_t index, const base::span<const char>& jsonb, size_t metadata_begin_offset,
                             size_t data_begin_offset, size_t num_kv_pairs, base::span<const char> *result,
                             JEntry* value_metadata) {
  // Compute the value index.
  size_t key_index = metadata_begin_offset + (index * sizeof(JEntry));
  size_t value_index = key_index + num_kv_pairs * sizeof(JEntry);
  if (value_index >= jsonb.size()) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "value index in jsonb out of bounds");
  }

  // Read the value metadata.
  base::BigEndianReader reader(jsonb.data() + value_index, sizeof(jsonb.data() + value_index));
  if(!reader.ReadU32(value_metadata)) {
    DCHECK(false);
  }

  // Read the value.
  size_t value_end_offset = GetOffset(*value_metadata);

  // Process the value.
  size_t value_offset;
  size_t value_length;
  std::tie(value_offset, value_length) = GetOffsetAndLength(value_index, jsonb, value_end_offset,
                                                            data_begin_offset,
                                                            metadata_begin_offset);
  if (value_offset + value_length > jsonb.size()) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "json value data out of bounds in serialized jsonb");
  }

  *result = base::span<const char>(jsonb.data() + value_offset, value_length);
  RETURN_OK();
}

Status Jsonb::GetObjectKey(size_t index, const base::span<const char>& jsonb, size_t metadata_begin_offset,
                           size_t data_begin_offset, base::span<const char> *result) {
  // Compute the key index.
  size_t key_index = metadata_begin_offset + (index * sizeof(JEntry));
  if (key_index >= data_begin_offset) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "key index in jsonb out of bounds");
  }

  // Read the key metadata.
  JEntry key_metadata;
  base::BigEndianReader reader(jsonb.data() + key_index, sizeof(jsonb.data() + key_index));
  if(!reader.ReadU32(&key_metadata)) {
    DCHECK(false);
  }

  // Read the key.
  size_t key_end_offset = GetOffset(key_metadata);

  // Process the key.
  size_t key_offset;
  size_t key_length;
  std::tie(key_offset, key_length) = GetOffsetAndLength(key_index, jsonb, key_end_offset,
                                                        data_begin_offset, metadata_begin_offset);
  if (key_offset + key_length > jsonb.size()) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "json key data out of bounds in serialized jsonb");
  }

  *result = base::span<const char>(jsonb.data() + key_offset, key_length);
  RETURN_OK();
}

Status Jsonb::GetArrayElement(size_t index, const base::span<const char>& jsonb,
                              size_t metadata_begin_offset, size_t data_begin_offset,
                              base::span<const char>* result, JEntry* element_metadata) {
  size_t value_index = metadata_begin_offset + (index * sizeof(JEntry));
  if (value_index >= jsonb.size()) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "value index out of bounds");
  }

  // Read the metadata.
  base::BigEndianReader reader(jsonb.data() + value_index, sizeof(jsonb.data() + value_index));
  if(!reader.ReadU32(element_metadata)) {
    DCHECK(false);
  }

  size_t value_end_offset = GetOffset(*element_metadata);

  // Process the value.
  size_t value_offset;
  size_t value_length;
  std::tie(value_offset, value_length) = GetOffsetAndLength(value_index, jsonb, value_end_offset,
                                                            data_begin_offset,
                                                            metadata_begin_offset);

  if (value_offset + value_length > jsonb.size()) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "json value out of bounds of serialized jsonb");
  }
  *result = base::span<const char>(jsonb.data() + value_offset, value_length);
  RETURN_OK();
}

std::pair<size_t, size_t> Jsonb::GetOffsetAndLength(size_t element_metadata_offset,
                                               const base::span<const char>& jsonb,
                                               size_t element_end_offset,
                                               size_t data_begin_offset,
                                               size_t metadata_begin_offset) {
  if (element_metadata_offset == metadata_begin_offset) {
    // This is the first element.
    return std::make_pair(data_begin_offset, element_end_offset);
  }

  DCHECK_GE(element_metadata_offset, sizeof(JsonbHeader));
  JEntry prev_element;

  base::BigEndianReader reader(jsonb.data() + element_metadata_offset - sizeof(JEntry)
    , sizeof(jsonb.data() + element_metadata_offset - sizeof(JEntry)));
  if(!reader.ReadU32(&prev_element)) {
    DCHECK(false);
  }

  size_t prev_element_offset = GetOffset(prev_element);
  return std::make_pair(prev_element_offset + data_begin_offset,
                        element_end_offset - prev_element_offset);

}

#if 0
Status Jsonb::ToJsonString(std::string* json) const {
  return ToJsonStringInternal(serialized_jsonb_, json);
}

Status Jsonb::ToJsonStringInternal(const base::span<const char>& jsonb, std::string* json) {
  rapidjson::Document document;
  RETURN_IF_NOT_OK(FromJsonbInternal(jsonb, &document));
  *DCHECK_NOTNULL(json) = WriteRapidJsonToString(document);
  RETURN_OK();
}

Status Jsonb::ScalarToString(const JEntry& element_metadata, const base::span<const char>& json_value,
                             string* result) {
  switch (GetJEType(element_metadata)) {
    case kJEIsString: {
      *result = json_value.ToBuffer();
      break;
    }
    case kJEIsInt: {
      int32_t value = DecodeInt32FromKey(json_value);
      *result = std::to_string(value);
      break;
    }
    case kJEIsUInt: {
      uint32_t value = BigEndian::Load32(json_value.data());
      *result = std::to_string(value);
      break;
    }
    case kJEIsInt64: {
      int64_t value = DecodeInt64FromKey(json_value);
      *result = std::to_string(value);
      break;
    }
    case kJEIsUInt64: {
      uint64_t value = BigEndian::Load64(json_value.data());
      *result = std::to_string(value);
      break;
    }
    case kJEIsDouble: {
      double value = DecodeDoubleFromKey(json_value);
      *result = std::to_string(value);
      break;
    }
    case kJEIsFloat: {
      float value = DecodeFloatFromKey(json_value);
      *result = std::to_string(value);
      break;
    }
    case kJEIsBoolFalse: {
      *result = "false";
      break;
    }
    case kJEIsBoolTrue: {
      *result = "true";
      break;
    }
    case kJEIsNull: {
      *result = "null";
      break;
    }
    case kJEIsObject: FALLTHROUGH_INTENDED;
    case kJEIsArray:
      return ::basic::Status(
        FROM_HERE, ::basic::error::INTERNAL, "Arrays and Objects not supported for this method");
  }
  RETURN_OK();
}

Status Jsonb::ApplyJsonbOperatorToArray(const base::span<const char>& jsonb, const QLJsonOperationPB& json_op,
                                        const JsonbHeader& jsonb_header,
                                        base::span<const char>* result, JEntry* element_metadata) {
  if(!json_op.operand().value().has_varint_value()) {
    return STATUS_SUBSTITUTE(NotFound, "Couldn't apply json operator");
  }

  // For arrays, the argument needs to be an integer.
  size_t num_array_entries = GetCount(jsonb_header);

  // Retrieve the array index and verify.
  VarInt varint;
  RETURN_IF_NOT_OK(varint.DecodeFromComparable(json_op.operand().value().varint_value()));
  auto statusor = varint.ToInt64();
  DCHECK_OK(statusor);
  int64_t array_index = RVALUE_CAST(statusor.ConsumeValueOrDie());

  if (array_index < 0 || array_index >= num_array_entries) {
    return STATUS_SUBSTITUTE(NotFound, "Array index: $1 out of bounds [0, $1)",
                             array_index, num_array_entries);
  }

  RETURN_IF_NOT_OK(GetArrayElement(array_index, jsonb, sizeof(jsonb_header),
                                ComputeDataOffset(num_array_entries, kJBArray), result,
                                element_metadata));
  RETURN_OK();
}

Status Jsonb::ApplyJsonbOperatorToObject(const base::span<const char>& jsonb, const QLJsonOperationPB& json_op,
                                         const JsonbHeader& jsonb_header,
                                         base::span<const char>* result, JEntry* element_metadata) {
  if (!json_op.operand().value().has_string_value()) {
    return STATUS_SUBSTITUTE(NotFound, "Couldn't apply json operator");
  }

  size_t num_kv_pairs = GetCount(jsonb_header);
  const string& search_key = json_op.operand().value().string_value();

  size_t metadata_begin_offset = sizeof(jsonb_header);
  size_t data_begin_offset = ComputeDataOffset(num_kv_pairs, kJBObject);

  // Binary search to find the key.
  int64_t low = 0, high = num_kv_pairs - 1;
  auto search_key_slice = base::span<const char>(search_key);
  while (low <= high) {
    size_t mid = low + (high - low)/2;
    base::span<const char> mid_key;
    RETURN_IF_NOT_OK(GetObjectKey(mid, jsonb, metadata_begin_offset, data_begin_offset, &mid_key));

    if (mid_key == search_key_slice) {
      RETURN_IF_NOT_OK(GetObjectValue(mid, jsonb, sizeof(jsonb_header),
                                   ComputeDataOffset(num_kv_pairs, kJBObject), num_kv_pairs,
                                   result, element_metadata));
      RETURN_OK();
    } else if (mid_key.ToBuffer() > search_key) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return STATUS_SUBSTITUTE(NotFound, "Couldn't find key $1 in json document", search_key);
}

Status Jsonb::ApplyJsonbOperators(const QLJsonColumnOperationsPB& json_ops, QLValue* result) const {
  const int num_ops = json_ops.json_operations().size();

  base::span<const char> jsonop_result;
  base::span<const char> operand(serialized_jsonb_);
  JEntry element_metadata;
  for (int i = 0; i < num_ops; i++) {
    const QLJsonOperationPB &op = json_ops.json_operations().Get(i);
    const Status s = ApplyJsonbOperator(operand, op, &jsonop_result,
                                        &element_metadata);
    if (s.IsNotFound()) {
      // We couldn't apply the operator to the operand and hence return null as the result.
      result->SetNull();
      RETURN_OK();
    }
    RETURN_IF_NOT_OK(s);

    if (IsScalar(element_metadata) && i != num_ops - 1) {
      // We have to apply another operation after this, but we received a scalar intermediate
      // result.
      result->SetNull();
      RETURN_OK();
    }
    operand = jsonop_result;
  }

  // In case of '->>', we need to return a string result.
  if (num_ops > 0 &&
      json_ops.json_operations().Get(num_ops - 1).json_operator() == JsonOperatorPB::JSON_TEXT) {
    if (IsScalar(element_metadata)) {
      RETURN_IF_NOT_OK(ScalarToString(element_metadata, jsonop_result,
                                   result->mutable_string_value()));
    } else {
      string str_result;
      RETURN_IF_NOT_OK(ToJsonStringInternal(jsonop_result, &str_result));
      result->set_string_value(std::move(str_result));
    }
    RETURN_OK();
  }

  string jsonb_result = jsonop_result.ToBuffer();
  if (IsScalar(element_metadata)) {
    // In case of a scalar that is received from an operation, convert it to a jsonb scalar.
    RETURN_IF_NOT_OK(CreateScalar(jsonop_result,
                               element_metadata,
                               &jsonb_result));
  }
  result->set_jsonb_value(std::move(jsonb_result));
  RETURN_OK();
}

Status Jsonb::ApplyJsonbOperator(const base::span<const char>& jsonb, const QLJsonOperationPB& json_op,
                                 base::span<const char>* result, JEntry* element_metadata) {
  // Currently, both these operators are considered the same since we only handle strings.
  DCHECK(json_op.json_operator() == JsonOperatorPB::JSON_OBJECT ||
         json_op.json_operator() == JsonOperatorPB::JSON_TEXT);

  // We only support strings and integers as the argument to the json operation currently.
  DCHECK(json_op.operand().has_value());

  if (jsonb.size() < sizeof(JsonbHeader)) {
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "Not enough data to process");
  }

  JsonbHeader jsonb_header = BigEndian::Load32(jsonb.data());
  if ((jsonb_header & kJBScalar) && (jsonb_header & kJBArray)) {
    // This is a scalar value and no operators can be applied to it.
    return ::basic::Status(
      FROM_HERE, ::basic::error::INTERNAL, "Cannot apply operators to scalar values");
  } else if (jsonb_header & kJBArray) {
    return ApplyJsonbOperatorToArray(jsonb, json_op, jsonb_header, result, element_metadata);
  } else if (jsonb_header & kJBObject) {
    return ApplyJsonbOperatorToObject(jsonb, json_op, jsonb_header, result, element_metadata);
  }

  return ::basic::Status(
    FROM_HERE, ::basic::error::INTERNAL, "Invalid json operation");
}

Status Jsonb::CreateScalar(const base::span<const char>& scalar, const JEntry& original_jentry,
                           std::string* scalar_jsonb) {
  // Build the header.
  size_t metadata_begin_offset = sizeof(JsonbHeader);
  size_t metadata_size = metadata_begin_offset + sizeof(JEntry);
  size_t data_begin_offset = metadata_size;

  // Resize the result.
  scalar_jsonb->resize(metadata_size);
  scalar_jsonb->append(scalar.data(), scalar.size());

  JsonbHeader jsonb_header = (1 & kJBCountMask) | kJBArray | kJBScalar;
  JEntry jentry = (GetOffset(scalar_jsonb->size() - data_begin_offset)) |
      GetJEType(original_jentry);

  // Store the header.
  BigEndian::Store32(&((*scalar_jsonb)[0]), jsonb_header);
  // Store the JEntry.
  BigEndian::Store32(&((*scalar_jsonb)[metadata_begin_offset]), jentry);
  RETURN_OK();
}
#endif

} // namespace basic

