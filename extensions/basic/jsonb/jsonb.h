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

#pragma once

#include "basic/status/status_macros.h"
#include "basic/status/status.h"
#include "basic/status/statusor.h"

#include "base/base_export.h"
#include "base/logging.h"
#include "base/optional.h"
#include "base/macros.h"
#include "base/memory/ptr_util.h"
#include "base/strings/string16.h"
#include "base/strings/string_piece.h"
#include "base/values.h"
#include "base/json/json_parser.h"
#include "base/json/json_reader.h"
#include "base/containers/span.h"

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace basic {

using JsonbMetadata = uint32_t;
using JsonbHeader = JsonbMetadata;
using JEntry = JsonbMetadata;

/// \todo improve support for int64, uint64. See todo-s in tests.
//
// Jsonb is a serialization format for json that used in postgresql. This implementation of jsonb
// is similar to the jsonb format, although not exactly the same (details regarding differences
// follow). The jsonb format, first includes a 32 bit header, whose first 28 bits store the total
// number of key-value pairs in the json object. The next four bits are used to indicate whether
// this is a json object, json array or just a scalar value.
//
// Next, we store the metadata for all the keys and values in the json object. The key-value
// pairs are sorted based on keys before serialization and hence the original order is lost.
// However, the sorting of key-value pairs would make it easier to search for a particular key in
// jsonb. After the 32 bit jsonb header, we store 32 bit metadata for each key, followed by a
// 32 bit metadata for each value. Next, we store all the keys followed by all the values.
//
// In case of arrays, we store the metadata for all the array elements first and then store the
// data for the corresponding array elements after that. The original order of the array elements
// is maintained.
//
// The 32 bit metadata is called a JEntry and the first 28 bits store the ending offset of the
// data. The last 4 bits indicate the type of the data (ex: string, numeric, bool, array, object
// or null).
//
// The following are some of the differences from postgresql's jsonb implementation:
// 1. In the JEntry, postgresql sometimes stores offsets and sometimes stores the length. This is
// done for better compressibility in their case. Although, for us this doesn't make much of a
// difference and hence its simpler to just use offsets.
// 2. In our serialization format, we just use the BigEndian format used in docdb
// docs.yugabyte.com/latest/architecture/docdb/ to store serialized integers.
// 3. We store the data type for ints, uints, floats and doubles in the JEntry.
// 4. We store information about whether a container is an array or an object in the JEntry.
class Jsonb {
 public:
  Jsonb();

  // Creates an object from a serialized jsonb payload.
  explicit Jsonb(const std::string& jsonb);

  explicit Jsonb(std::string&& jsonb);

  void Assign(const std::string& jsonb);
  void Assign(std::string&& jsonb);

  // Creates a serialized jsonb string from plaintext json.
  basic::Status FromString(const std::string& json);

  // Creates a serialized jsonb string from json document or value.
  basic::Status FromJson(const base::Value& document);

  // Builds a json document from serialized jsonb.
  basic::StatusOr<base::Value> ToJson() const;

  // Returns a json string for serialized jsonb
  basic::StatusOr<std::string> ToJsonString() const;

#if 0
  basic::Status ToJsonString(std::string* json) const;

  basic::Status ApplyJsonbOperators(const QLJsonColumnOperationsPB& json_ops,
                                     QLValue* result) const;
#endif

  const std::string& SerializedJsonb() const;

  // Use with extreme care since this destroys the internal state of the object. The only purpose
  // for this method is to allow for efficiently moving the serialized jsonb.
  std::string&& MoveSerializedJsonb();

  bool operator==(const Jsonb& other) const;

 private:
  std::string serialized_jsonb_;

#if 0
  // Given a jsonb slice, it applies the given operator to the slice and returns the result as a
  // Slice and the element's metadata.
  static basic::Status ApplyJsonbOperator(const base::span<const char>& jsonb, const QLJsonOperationPB& json_op,
                                           base::span<const char>* result, JEntry* element_metadata);
#endif

  static bool IsScalar(const JEntry& jentry);

  static size_t ComputeDataOffset(const size_t num_entries, const uint32_t container_type);

  static std::pair<size_t, size_t> ComputeOffsetsAndJsonbHeader(size_t num_entries,
                                                           uint32_t container_type,
                                                           std::string* jsonb);

  static basic::Status ToJsonbInternal(const base::Value& document, std::string* jsonb);
  static basic::Status ToJsonbProcessObject(const base::Value& document,
                                             std::string* jsonb);
  static basic::Status ToJsonbProcessArray(const base::Value& document,
                                            bool is_scalar,
                                            std::string* jsonb);

  static basic::Status ProcessJsonValueAndMetadata(const base::Value& document,
                                                   const size_t data_begin_offset,
                                                   std::string* jsonb,
                                                   size_t* metadata_offset);

  // Method to recursively build the json object from serialized jsonb. The offset denotes the
  // starting position in the jsonb from which we need to start processing.
  static basic::Status FromJsonbInternal(const base::span<const char>& jsonb, base::Value* document);

  static basic::Status FromJsonbProcessObject(const base::span<const char>& jsonb,
                                               const JsonbHeader& jsonb_header,
                                               base::Value* document);
  static basic::Status FromJsonbProcessArray(const base::span<const char>& jsonb,
                                              const JsonbHeader& jsonb_header,
                                              base::Value* document);

#if 0
  static basic::Status ToJsonStringInternal(const base::span<const char>& jsonb, std::string* json);

  // Given a scalar value retrieved from a serialized jsonb, this method creates a jsonb scalar
  // (which is a single element within an array). This is required for comparison purposes.
  static basic::Status CreateScalar(const base::span<const char>& scalar, const JEntry& original_jentry,
                                     std::string* scalar_jsonb);

  // Given a serialized json scalar and its metadata, return a string representation of it.
  static basic::Status ScalarToString(const JEntry& element_metadata, const base::span<const char>& json_value,
                                       std::string* result);
#endif

  // Retrieves an element in serialized jsonb array with the provided index. The result is a
  // slice pointing to a section of the serialized jsonb string provided. The parameters
  // metdata_begin_offset and data_begin_offset indicate the starting positions of metadata and
  // data in the serialized jsonb. The method also returns a JEntry for the specified element, if
  // metadata information for that element is required.
  static basic::Status GetArrayElement(size_t index, const base::span<const char>& jsonb,
                                        size_t metadata_begin_offset, size_t data_begin_offset,
                                        base::span<const char>* result, JEntry* element_metadata);

  // Retrieves the key from a serialized jsonb object at the given index. The result is a
  // slice pointing to a section of the serialized jsonb string provided. The parameters
  // metdata_begin_offset and data_begin_offset indicate the starting positions of metadata and
  // data in the serialized jsonb.
  static basic::Status GetObjectKey(size_t index, const base::span<const char>& jsonb, size_t metadata_begin_offset,
                                     size_t data_begin_offset, base::span<const char> *result);

  // Retrieves the value from a serialized jsonb object at the given index. The result is a
  // slice pointing to a section of the serialized jsonb string provided. The parameters
  // metdata_begin_offset and data_begin_offset indicate the starting positions of metadata and
  // data in the serialized jsonb. The parameter num_kv_pairs indicates the total number of kv
  // pairs in the json object. The method also returns a JEntry for the specified element, if
  // metadata information for that element is required.
  static basic::Status GetObjectValue(size_t index, const base::span<const char>& jsonb,
                                       size_t metadata_begin_offset, size_t data_begin_offset,
                                       size_t num_kv_pairs, base::span<const char> *result, JEntry* value_metadata);

  // Helper method to retrieve the (offset, length) of a key/value serialized in jsonb format.
  // element_metadata_offset denotes the offset for the JEntry of the key/value,
  // element_end_offset denotes the end of data portion of the key/value, data_begin_offset
  // denotes the offset from which the data portion of jsonb starts, metadata_begin_offset is the
  // offset from which all the JEntry fields begin.
  static std::pair<size_t, size_t> GetOffsetAndLength(size_t element_metadata_offset,
                                                 const base::span<const char>& jsonb,
                                                 size_t element_end_offset,
                                                 size_t data_begin_offset,
                                                 size_t metadata_begin_offset);

#if 0
  static basic::Status ApplyJsonbOperatorToArray(const base::span<const char>& jsonb,
                                                  const QLJsonOperationPB& json_op,
                                                  const JsonbHeader& jsonb_header,
                                                  base::span<const char>* result,
                                                  JEntry* element_metadata);

  static basic::Status ApplyJsonbOperatorToObject(const base::span<const char>& jsonb,
                                                   const QLJsonOperationPB& json_op,
                                                   const JsonbHeader& jsonb_header,
                                                   base::span<const char>* result,
                                                   JEntry* element_metadata);
#endif

  static inline size_t GetOffset(JEntry metadata) { return metadata & kJEOffsetMask; }

  static inline uint32_t GetJEType(JEntry metadata) { return metadata & kJETypeMask; }

  static inline uint32_t GetCount(JsonbHeader jsonb_header) { return jsonb_header & kJBCountMask; }

  // Bit masks for jsonb header fields.
  static constexpr uint32_t kJBCountMask = 0x0FFFFFFF; // mask for number of kv pairs.
  static constexpr uint32_t kJBScalar = 0x10000000; // indicates whether we have a scalar value.
  static constexpr uint32_t kJBObject = 0x20000000; // indicates whether we have a json object.
  static constexpr uint32_t kJBArray = 0x40000000; // indicates whether we have a json array.

  // Bit masks for json header fields.
  static constexpr uint32_t kJEOffsetMask = 0x0FFFFFFF;
  static constexpr uint32_t kJETypeMask = 0xF0000000;

  // Values stored in the type bits.
  static constexpr uint32_t kJEIsString = 0x00000000;
  static constexpr uint32_t kJEIsObject = 0x10000000;
  static constexpr uint32_t kJEIsBoolFalse = 0x20000000;
  static constexpr uint32_t kJEIsBoolTrue = 0x30000000;
  static constexpr uint32_t kJEIsNull = 0x40000000;
  static constexpr uint32_t kJEIsArray = 0x50000000;
  static constexpr uint32_t kJEIsInt = 0x60000000;
  static constexpr uint32_t kJEIsUInt = 0x70000000;
  static constexpr uint32_t kJEIsInt64 = 0x80000000;
  static constexpr uint32_t kJEIsUInt64 = 0x90000000;
  static constexpr uint32_t kJEIsFloat = 0xA0000000;
  static constexpr uint32_t kJEIsDouble = 0xB0000000;
};

}  // namespace basic
