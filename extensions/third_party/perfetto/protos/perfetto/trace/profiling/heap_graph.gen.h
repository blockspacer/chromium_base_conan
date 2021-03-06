// DO NOT EDIT. Autogenerated by Perfetto cppgen_plugin
#ifndef PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PROFILING_HEAP_GRAPH_PROTO_CPP_H_
#define PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PROFILING_HEAP_GRAPH_PROTO_CPP_H_

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
class HeapGraph;
class InternedString;
class HeapGraphType;
class HeapGraphRoot;
class HeapGraphObject;
enum HeapGraphType_Kind : int;
enum HeapGraphRoot_Type : int;
}  // namespace perfetto
}  // namespace protos
}  // namespace gen

namespace protozero {
class Message;
}  // namespace protozero

namespace perfetto {
namespace protos {
namespace gen {
enum HeapGraphType_Kind : int {
  HeapGraphType_Kind_KIND_UNKNOWN = 0,
  HeapGraphType_Kind_KIND_NORMAL = 1,
  HeapGraphType_Kind_KIND_NOREFERENCES = 2,
  HeapGraphType_Kind_KIND_STRING = 3,
  HeapGraphType_Kind_KIND_ARRAY = 4,
  HeapGraphType_Kind_KIND_CLASS = 5,
  HeapGraphType_Kind_KIND_CLASSLOADER = 6,
  HeapGraphType_Kind_KIND_DEXCACHE = 7,
  HeapGraphType_Kind_KIND_SOFT_REFERENCE = 8,
  HeapGraphType_Kind_KIND_WEAK_REFERENCE = 9,
  HeapGraphType_Kind_KIND_FINALIZER_REFERENCE = 10,
  HeapGraphType_Kind_KIND_PHANTOM_REFERENCE = 11,
};
enum HeapGraphRoot_Type : int {
  HeapGraphRoot_Type_ROOT_UNKNOWN = 0,
  HeapGraphRoot_Type_ROOT_JNI_GLOBAL = 1,
  HeapGraphRoot_Type_ROOT_JNI_LOCAL = 2,
  HeapGraphRoot_Type_ROOT_JAVA_FRAME = 3,
  HeapGraphRoot_Type_ROOT_NATIVE_STACK = 4,
  HeapGraphRoot_Type_ROOT_STICKY_CLASS = 5,
  HeapGraphRoot_Type_ROOT_THREAD_BLOCK = 6,
  HeapGraphRoot_Type_ROOT_MONITOR_USED = 7,
  HeapGraphRoot_Type_ROOT_THREAD_OBJECT = 8,
  HeapGraphRoot_Type_ROOT_INTERNED_STRING = 9,
  HeapGraphRoot_Type_ROOT_FINALIZING = 10,
  HeapGraphRoot_Type_ROOT_DEBUGGER = 11,
  HeapGraphRoot_Type_ROOT_REFERENCE_CLEANUP = 12,
  HeapGraphRoot_Type_ROOT_VM_INTERNAL = 13,
  HeapGraphRoot_Type_ROOT_JNI_MONITOR = 14,
};

class PERFETTO_EXPORT HeapGraph : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kPidFieldNumber = 1,
    kObjectsFieldNumber = 2,
    kRootsFieldNumber = 7,
    kTypesFieldNumber = 9,
    kFieldNamesFieldNumber = 4,
    kLocationNamesFieldNumber = 8,
    kContinuedFieldNumber = 5,
    kIndexFieldNumber = 6,
  };

  HeapGraph();
  ~HeapGraph() override;
  HeapGraph(HeapGraph&&) noexcept;
  HeapGraph& operator=(HeapGraph&&);
  HeapGraph(const HeapGraph&);
  HeapGraph& operator=(const HeapGraph&);
  bool operator==(const HeapGraph&) const;
  bool operator!=(const HeapGraph& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_pid() const { return _has_field_[1]; }
  int32_t pid() const { return pid_; }
  void set_pid(int32_t value) { pid_ = value; _has_field_.set(1); }

  const std::vector<HeapGraphObject>& objects() const { return objects_; }
  std::vector<HeapGraphObject>* mutable_objects() { return &objects_; }
  int objects_size() const;
  void clear_objects();
  HeapGraphObject* add_objects();

  const std::vector<HeapGraphRoot>& roots() const { return roots_; }
  std::vector<HeapGraphRoot>* mutable_roots() { return &roots_; }
  int roots_size() const;
  void clear_roots();
  HeapGraphRoot* add_roots();

  const std::vector<HeapGraphType>& types() const { return types_; }
  std::vector<HeapGraphType>* mutable_types() { return &types_; }
  int types_size() const;
  void clear_types();
  HeapGraphType* add_types();

  const std::vector<InternedString>& field_names() const { return field_names_; }
  std::vector<InternedString>* mutable_field_names() { return &field_names_; }
  int field_names_size() const;
  void clear_field_names();
  InternedString* add_field_names();

  const std::vector<InternedString>& location_names() const { return location_names_; }
  std::vector<InternedString>* mutable_location_names() { return &location_names_; }
  int location_names_size() const;
  void clear_location_names();
  InternedString* add_location_names();

  bool has_continued() const { return _has_field_[5]; }
  bool continued() const { return continued_; }
  void set_continued(bool value) { continued_ = value; _has_field_.set(5); }

  bool has_index() const { return _has_field_[6]; }
  uint64_t index() const { return index_; }
  void set_index(uint64_t value) { index_ = value; _has_field_.set(6); }

 private:
  int32_t pid_{};
  std::vector<HeapGraphObject> objects_;
  std::vector<HeapGraphRoot> roots_;
  std::vector<HeapGraphType> types_;
  std::vector<InternedString> field_names_;
  std::vector<InternedString> location_names_;
  bool continued_{};
  uint64_t index_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<10> _has_field_{};
};


class PERFETTO_EXPORT HeapGraphType : public ::protozero::CppMessageObj {
 public:
  using Kind = HeapGraphType_Kind;
  static constexpr auto KIND_UNKNOWN = HeapGraphType_Kind_KIND_UNKNOWN;
  static constexpr auto KIND_NORMAL = HeapGraphType_Kind_KIND_NORMAL;
  static constexpr auto KIND_NOREFERENCES = HeapGraphType_Kind_KIND_NOREFERENCES;
  static constexpr auto KIND_STRING = HeapGraphType_Kind_KIND_STRING;
  static constexpr auto KIND_ARRAY = HeapGraphType_Kind_KIND_ARRAY;
  static constexpr auto KIND_CLASS = HeapGraphType_Kind_KIND_CLASS;
  static constexpr auto KIND_CLASSLOADER = HeapGraphType_Kind_KIND_CLASSLOADER;
  static constexpr auto KIND_DEXCACHE = HeapGraphType_Kind_KIND_DEXCACHE;
  static constexpr auto KIND_SOFT_REFERENCE = HeapGraphType_Kind_KIND_SOFT_REFERENCE;
  static constexpr auto KIND_WEAK_REFERENCE = HeapGraphType_Kind_KIND_WEAK_REFERENCE;
  static constexpr auto KIND_FINALIZER_REFERENCE = HeapGraphType_Kind_KIND_FINALIZER_REFERENCE;
  static constexpr auto KIND_PHANTOM_REFERENCE = HeapGraphType_Kind_KIND_PHANTOM_REFERENCE;
  static constexpr auto Kind_MIN = HeapGraphType_Kind_KIND_UNKNOWN;
  static constexpr auto Kind_MAX = HeapGraphType_Kind_KIND_PHANTOM_REFERENCE;
  enum FieldNumbers {
    kIdFieldNumber = 1,
    kLocationIdFieldNumber = 2,
    kClassNameFieldNumber = 3,
    kObjectSizeFieldNumber = 4,
    kSuperclassIdFieldNumber = 5,
    kReferenceFieldIdFieldNumber = 6,
    kKindFieldNumber = 7,
    kClassloaderIdFieldNumber = 8,
  };

  HeapGraphType();
  ~HeapGraphType() override;
  HeapGraphType(HeapGraphType&&) noexcept;
  HeapGraphType& operator=(HeapGraphType&&);
  HeapGraphType(const HeapGraphType&);
  HeapGraphType& operator=(const HeapGraphType&);
  bool operator==(const HeapGraphType&) const;
  bool operator!=(const HeapGraphType& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_id() const { return _has_field_[1]; }
  uint64_t id() const { return id_; }
  void set_id(uint64_t value) { id_ = value; _has_field_.set(1); }

  bool has_location_id() const { return _has_field_[2]; }
  uint64_t location_id() const { return location_id_; }
  void set_location_id(uint64_t value) { location_id_ = value; _has_field_.set(2); }

  bool has_class_name() const { return _has_field_[3]; }
  const std::string& class_name() const { return class_name_; }
  void set_class_name(const std::string& value) { class_name_ = value; _has_field_.set(3); }

  bool has_object_size() const { return _has_field_[4]; }
  uint64_t object_size() const { return object_size_; }
  void set_object_size(uint64_t value) { object_size_ = value; _has_field_.set(4); }

  bool has_superclass_id() const { return _has_field_[5]; }
  uint64_t superclass_id() const { return superclass_id_; }
  void set_superclass_id(uint64_t value) { superclass_id_ = value; _has_field_.set(5); }

  const std::vector<uint64_t>& reference_field_id() const { return reference_field_id_; }
  std::vector<uint64_t>* mutable_reference_field_id() { return &reference_field_id_; }
  int reference_field_id_size() const { return static_cast<int>(reference_field_id_.size()); }
  void clear_reference_field_id() { reference_field_id_.clear(); }
  void add_reference_field_id(uint64_t value) { reference_field_id_.emplace_back(value); }
  uint64_t* add_reference_field_id() { reference_field_id_.emplace_back(); return &reference_field_id_.back(); }

  bool has_kind() const { return _has_field_[7]; }
  HeapGraphType_Kind kind() const { return kind_; }
  void set_kind(HeapGraphType_Kind value) { kind_ = value; _has_field_.set(7); }

  bool has_classloader_id() const { return _has_field_[8]; }
  uint64_t classloader_id() const { return classloader_id_; }
  void set_classloader_id(uint64_t value) { classloader_id_ = value; _has_field_.set(8); }

 private:
  uint64_t id_{};
  uint64_t location_id_{};
  std::string class_name_{};
  uint64_t object_size_{};
  uint64_t superclass_id_{};
  std::vector<uint64_t> reference_field_id_;
  HeapGraphType_Kind kind_{};
  uint64_t classloader_id_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<9> _has_field_{};
};


class PERFETTO_EXPORT HeapGraphRoot : public ::protozero::CppMessageObj {
 public:
  using Type = HeapGraphRoot_Type;
  static constexpr auto ROOT_UNKNOWN = HeapGraphRoot_Type_ROOT_UNKNOWN;
  static constexpr auto ROOT_JNI_GLOBAL = HeapGraphRoot_Type_ROOT_JNI_GLOBAL;
  static constexpr auto ROOT_JNI_LOCAL = HeapGraphRoot_Type_ROOT_JNI_LOCAL;
  static constexpr auto ROOT_JAVA_FRAME = HeapGraphRoot_Type_ROOT_JAVA_FRAME;
  static constexpr auto ROOT_NATIVE_STACK = HeapGraphRoot_Type_ROOT_NATIVE_STACK;
  static constexpr auto ROOT_STICKY_CLASS = HeapGraphRoot_Type_ROOT_STICKY_CLASS;
  static constexpr auto ROOT_THREAD_BLOCK = HeapGraphRoot_Type_ROOT_THREAD_BLOCK;
  static constexpr auto ROOT_MONITOR_USED = HeapGraphRoot_Type_ROOT_MONITOR_USED;
  static constexpr auto ROOT_THREAD_OBJECT = HeapGraphRoot_Type_ROOT_THREAD_OBJECT;
  static constexpr auto ROOT_INTERNED_STRING = HeapGraphRoot_Type_ROOT_INTERNED_STRING;
  static constexpr auto ROOT_FINALIZING = HeapGraphRoot_Type_ROOT_FINALIZING;
  static constexpr auto ROOT_DEBUGGER = HeapGraphRoot_Type_ROOT_DEBUGGER;
  static constexpr auto ROOT_REFERENCE_CLEANUP = HeapGraphRoot_Type_ROOT_REFERENCE_CLEANUP;
  static constexpr auto ROOT_VM_INTERNAL = HeapGraphRoot_Type_ROOT_VM_INTERNAL;
  static constexpr auto ROOT_JNI_MONITOR = HeapGraphRoot_Type_ROOT_JNI_MONITOR;
  static constexpr auto Type_MIN = HeapGraphRoot_Type_ROOT_UNKNOWN;
  static constexpr auto Type_MAX = HeapGraphRoot_Type_ROOT_JNI_MONITOR;
  enum FieldNumbers {
    kObjectIdsFieldNumber = 1,
    kRootTypeFieldNumber = 2,
  };

  HeapGraphRoot();
  ~HeapGraphRoot() override;
  HeapGraphRoot(HeapGraphRoot&&) noexcept;
  HeapGraphRoot& operator=(HeapGraphRoot&&);
  HeapGraphRoot(const HeapGraphRoot&);
  HeapGraphRoot& operator=(const HeapGraphRoot&);
  bool operator==(const HeapGraphRoot&) const;
  bool operator!=(const HeapGraphRoot& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  const std::vector<uint64_t>& object_ids() const { return object_ids_; }
  std::vector<uint64_t>* mutable_object_ids() { return &object_ids_; }
  int object_ids_size() const { return static_cast<int>(object_ids_.size()); }
  void clear_object_ids() { object_ids_.clear(); }
  void add_object_ids(uint64_t value) { object_ids_.emplace_back(value); }
  uint64_t* add_object_ids() { object_ids_.emplace_back(); return &object_ids_.back(); }

  bool has_root_type() const { return _has_field_[2]; }
  HeapGraphRoot_Type root_type() const { return root_type_; }
  void set_root_type(HeapGraphRoot_Type value) { root_type_ = value; _has_field_.set(2); }

 private:
  std::vector<uint64_t> object_ids_;
  HeapGraphRoot_Type root_type_{};

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<3> _has_field_{};
};


class PERFETTO_EXPORT HeapGraphObject : public ::protozero::CppMessageObj {
 public:
  enum FieldNumbers {
    kIdFieldNumber = 1,
    kTypeIdFieldNumber = 2,
    kSelfSizeFieldNumber = 3,
    kReferenceFieldIdBaseFieldNumber = 6,
    kReferenceFieldIdFieldNumber = 4,
    kReferenceObjectIdFieldNumber = 5,
  };

  HeapGraphObject();
  ~HeapGraphObject() override;
  HeapGraphObject(HeapGraphObject&&) noexcept;
  HeapGraphObject& operator=(HeapGraphObject&&);
  HeapGraphObject(const HeapGraphObject&);
  HeapGraphObject& operator=(const HeapGraphObject&);
  bool operator==(const HeapGraphObject&) const;
  bool operator!=(const HeapGraphObject& other) const { return !(*this == other); }

  bool ParseFromArray(const void*, size_t) override;
  std::string SerializeAsString() const override;
  std::vector<uint8_t> SerializeAsArray() const override;
  void Serialize(::protozero::Message*) const;

  bool has_id() const { return _has_field_[1]; }
  uint64_t id() const { return id_; }
  void set_id(uint64_t value) { id_ = value; _has_field_.set(1); }

  bool has_type_id() const { return _has_field_[2]; }
  uint64_t type_id() const { return type_id_; }
  void set_type_id(uint64_t value) { type_id_ = value; _has_field_.set(2); }

  bool has_self_size() const { return _has_field_[3]; }
  uint64_t self_size() const { return self_size_; }
  void set_self_size(uint64_t value) { self_size_ = value; _has_field_.set(3); }

  bool has_reference_field_id_base() const { return _has_field_[6]; }
  uint64_t reference_field_id_base() const { return reference_field_id_base_; }
  void set_reference_field_id_base(uint64_t value) { reference_field_id_base_ = value; _has_field_.set(6); }

  const std::vector<uint64_t>& reference_field_id() const { return reference_field_id_; }
  std::vector<uint64_t>* mutable_reference_field_id() { return &reference_field_id_; }
  int reference_field_id_size() const { return static_cast<int>(reference_field_id_.size()); }
  void clear_reference_field_id() { reference_field_id_.clear(); }
  void add_reference_field_id(uint64_t value) { reference_field_id_.emplace_back(value); }
  uint64_t* add_reference_field_id() { reference_field_id_.emplace_back(); return &reference_field_id_.back(); }

  const std::vector<uint64_t>& reference_object_id() const { return reference_object_id_; }
  std::vector<uint64_t>* mutable_reference_object_id() { return &reference_object_id_; }
  int reference_object_id_size() const { return static_cast<int>(reference_object_id_.size()); }
  void clear_reference_object_id() { reference_object_id_.clear(); }
  void add_reference_object_id(uint64_t value) { reference_object_id_.emplace_back(value); }
  uint64_t* add_reference_object_id() { reference_object_id_.emplace_back(); return &reference_object_id_.back(); }

 private:
  uint64_t id_{};
  uint64_t type_id_{};
  uint64_t self_size_{};
  uint64_t reference_field_id_base_{};
  std::vector<uint64_t> reference_field_id_;
  std::vector<uint64_t> reference_object_id_;

  // Allows to preserve unknown protobuf fields for compatibility
  // with future versions of .proto files.
  std::string unknown_fields_;

  std::bitset<7> _has_field_{};
};

}  // namespace perfetto
}  // namespace protos
}  // namespace gen

#endif  // PERFETTO_PROTOS_PROTOS_PERFETTO_TRACE_PROFILING_HEAP_GRAPH_PROTO_CPP_H_
