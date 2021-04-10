// Copyright 2018 Google LLC
// Copyright 2018-present Open Networking Foundation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <basic/macros.h>

#include <atomic>
#include <iosfwd>
#include <string>

#include <base/logging.h>
#include <base/macros.h>
#include <base/location.h>
#include <base/strings/string_util.h>
#include <base/strings/strcat.h>
#include <base/synchronization/lock.h>

namespace basic {
namespace error {

/// \note
/// Choosing between FAILED_PRECONDITION, ABORTED, and UNAVAILABLE
/// is subtle, especially with respect to the retry strategy
/// the caller should use. Some guidelines that may help a service implementer:
/// * Use UNAVAILABLE if the client can retry just the failing call.
/// * Use ABORTED if the client should retry at a higher transaction level
/// (such as when a client-specified test-and-set fails,
/// indicating the client should restart a read-modify-write sequence).
/// * Use FAILED_PRECONDITION if the client should not retry
/// until the system state has been explicitly fixed.
/// For example, if an “rmdir” fails because the directory is non-empty,
/// FAILED_PRECONDITION should be returned since the client should not retry
/// unless the files are deleted from the directory.
//
enum Code {
  /// Not an error; returned on success.
  OK = 0,
  /// The operation was cancelled (typically by the caller).
  CANCELLED = 1,
  /// Unknown error. An example of where this error may be returned is if a
  /// Status value received from another address space belongs to an error-space
  /// that is not known in this address space. Also errors raised by APIs that
  /// do not return enough error information may be converted to this error.
  UNKNOWN = 2,
  /// Client specified an invalid argument. Note that this differs from
  /// FAILED_PRECONDITION. INVALID_ARGUMENT indicates arguments that are
  /// problematic regardless of the state of the system (e.g., a malformed file
  /// name).
  INVALID_ARGUMENT = 3,
  /// Deadline expired before operation could complete. For operations that
  /// change the state of the system, this error may be returned even if the
  /// operation has completed successfully. For example, a successful response
  /// from a server could have been delayed long enough for the deadline to
  /// expire.
  DEADLINE_EXCEEDED = 4,
  /// Some requested entity (e.g., file or directory) was not found.
  NOT_FOUND = 5,
  /// Some entity that we attempted to create (e.g., file or directory) already
  /// exists.
  ALREADY_EXISTS = 6,
  /// The caller does not have permission to execute the specified operation.
  /// PERMISSION_DENIED must not be used for rejections caused by exhausting
  /// some resource (use RESOURCE_EXHAUSTED instead for those errors).
  /// PERMISSION_DENIED must not be used if the caller can not be identified
  /// (use UNAUTHENTICATED instead for those errors).
  PERMISSION_DENIED = 7,
  /// Some resource has been exhausted, perhaps a per-user quota, or perhaps the
  /// entire file system is out of space.
  RESOURCE_EXHAUSTED = 8,
  /// Operation was rejected because the system is not in a state required for
  /// the operation's execution. For example, directory to be deleted may be
  /// non-empty, an rmdir operation is applied to a non-directory, etc.
  ///
  /// A litmus test that may help a service implementor in deciding
  /// between FAILED_PRECONDITION, ABORTED, and UNAVAILABLE:
  ///  (a) Use UNAVAILABLE if the client can retry just the failing call.
  ///  (b) Use ABORTED if the client should retry at a higher-level
  ///      (e.g., restarting a read-modify-write sequence).
  ///  (c) Use FAILED_PRECONDITION if the client should not retry until
  ///      the system state has been explicitly fixed. E.g., if an "rmdir"
  ///      fails because the directory is non-empty, FAILED_PRECONDITION
  ///      should be returned since the client should not retry unless
  ///      they have first fixed up the directory by deleting files from it.
  ///  (d) Use FAILED_PRECONDITION if the client performs conditional
  ///      REST Get/Update/Delete on a resource and the resource on the
  ///      server does not match the condition. E.g., conflicting
  ///      read-modify-write on the same resource.
  FAILED_PRECONDITION = 9,
  /// The operation was aborted, typically due to a concurrency issue like
  /// sequencer check failures, transaction aborts, etc.
  ///
  /// See litmus test above for deciding between FAILED_PRECONDITION, ABORTED,
  /// and UNAVAILABLE.
  ABORTED = 10,
  /// Operation was attempted past the valid range. E.g., seeking or reading
  /// past end of file.
  ///
  /// Unlike INVALID_ARGUMENT, this error indicates a problem that may be fixed
  /// if the system state changes. For example, a 32-bit file system will
  /// generate INVALID_ARGUMENT if asked to read at an offset that is not in the
  /// range [0,2^32-1], but it will generate OUT_OF_RANGE if asked to read from
  /// an offset past the current file size.
  ///
  /// There is a fair bit of overlap between FAILED_PRECONDITION and
  /// OUT_OF_RANGE. We recommend using OUT_OF_RANGE (the more specific error)
  /// when it applies so that callers who are iterating through a space can
  /// easily look for an OUT_OF_RANGE error to detect when they are done.
  OUT_OF_RANGE = 11,
  /// Operation is not implemented or not supported/enabled in this service.
  UNIMPLEMENTED = 12,
  /// Internal errors. Means some invariants expected by underlying System has
  /// been broken. If you see one of these errors, Something is very broken.
  INTERNAL = 13,
  /// The service is currently unavailable. This is a most likely a transient
  /// condition and may be corrected by retrying with a backoff.
  ///
  /// \warning Although data MIGHT not have been transmitted when this
  /// status occurs, there is NOT A GUARANTEE that the server has not seen
  /// anything. So in general it is unsafe to retry on this status code
  /// if the call is non-idempotent.
  ///
  /// See litmus test above for deciding between FAILED_PRECONDITION, ABORTED,
  /// and UNAVAILABLE.
  UNAVAILABLE = 14,
  /// Unrecoverable data loss or corruption.
  DATA_LOSS = 15,
  /// The request does not have valid authentication credentials for the
  /// operation.
  UNAUTHENTICATED = 16,
  TIMEOUT = 17,
  ALLOCATION_FAILED = 18,
  IO_ERROR = 19,
  NOT_IMPLEMENTED = 20,
  END_OF_FILE = 21,
  RUNTIME = 22,
  MEMORY_LIMIT_EXCEEDED = 23,
  TOO_MANY_TASKS = 24,
  SERVICE_UNAVAILABLE = 25,
  UNINITIALIZED = 26,
  UNSUPPORTED_TYPE = 27,
  TOO_LONG = 28,
  TOO_LARGE = 29,
  CONFLICT = 30,
  NOT_ACCEPTABLE = 31,
  PAYMENT_REQUIRED = 32,
  BAD_REQUEST = 33,
  REDIRECT = 34,
  FOUND = 35,
  MULTIPLE_CHOICES = 36,
  PARTIAL_CONTENT = 37,
  NO_CONTENT = 38,
  LENGTH_REQUIRED = 39,
  /// Force users to include a default branch:
  DO_NOT_USE_RESERVED_FOR_FUTURE_EXPANSION_USE_DEFAULT_IN_SWITCH_INSTEAD_ = 40,
  // **DO NOT ADD ANYTHING TO THIS**
};
static const enum Code Code_MIN = Code::OK;
static const enum Code Code_MAX = Code::LENGTH_REQUIRED;
inline bool Code_IsValid(int c) { return (c >= Code_MIN) && (c <= Code_MAX); }
}  // end namespace error
}  // end namespace basic

namespace basic {

using logging::LogSeverity;

// An ErrorSpace is a collection of related numeric error codes.  For
// example, all Posix errno values may be placed in the same
// ErrorSpace, all bigtable errors may be placed in the same
// ErrorSpace, etc.
//
// We recommend that new APIs use the canonical error space (and the
// corresponding two-argument constructor below) instead of creating a
// new error space per API
class ErrorSpace;

// Status represents an error state or the absence thereof.
// Inspired by https://abseil.io/docs/cpp/guides/status
//
// A Status is designed to either return OK
// or one of a number of different error codes,
// corresponding to typical error conditions.
// In almost all cases, when using Status
// you should use the canonical error codes.
// These canonical codes are understood across the codebase
// and will be accepted across all API and RPC boundaries.
// A function which has a return value of Status must be handled
// (and is marked MUST_USE_RESULT).
//
/// \note The error message is not intended for end users;
/// it may get logged somewhere for a developer or SRE
/// to examine and find out what went wrong.
//
/// \note low-level routines such as a file Open() operation
/// should typically not log status values themselves,
/// but should pass them up to the caller
/// who will have better context on how to handle any error.
//
class MUST_USE_RESULT Status final {
 public:
  // Creates a "successful" status.
  Status();

  // Create a status in the canonical error space with the specified
  // code, and error message.  If "code == 0", error_message is
  // ignored and a Status object identical to Status::OK is
  // constructed.
  Status(const ::base::Location& from_here
    , ::basic::error::Code code
    , const std::string& error_message);

  // Creates a status in the specified "space", "code" and the
  // associated error message.  If "code == 0", (space,msg) are ignored
  // and a Status object identical to Status::OK is constructed.
  //
  // New APIs should use the canonical error space and the preceding
  // two-argument constructor.
  //
  // REQUIRES: space != NULL
  Status(const ::base::Location& from_here
    , const ErrorSpace* space
    , int code
    , const std::string& msg);

  Status(const Status&);
  Status& operator=(const Status& x);
  ~Status();

  // For backwards compatibility, provide aliases of some the
  // canonical error codes defined in codes.proto.
  enum Code {
    OK_CODE = 0,         // No error
    CANCELLED_CODE = 1,  // For cancelled operations
    UNKNOWN_CODE = 2,    // For unknown spaces/codes
  };

  // Some pre-defined Status objects
  static const Status& OK;  // Identical to 0-arg constructor

  // Return the canonical error space.
  static const ErrorSpace* canonical_space();

  // Store the specified error in this Status object. If "code == 0",
  // (space,msg) are ignored and a Status object identical to Status::OK
  // is constructed.
  // REQUIRES: code == 0 OR space != NULL
  void SetError(const ::base::Location& location
    , const ErrorSpace* space
    , int code
    , const std::string& msg);

  // Keeps track of the first non-ok status encountered in a sequence.
  // Will overwrite an existing OK status,
  // but will not overwrite an existing error code of another value.
  //
  // If "ok()", stores "new_status" into *this.  If "!ok()", preserves
  // the current "error_code()/error_message()/error_space()",
  // but may augment with additional information about "new_status".
  //
  // Convenient way of keeping track of the first error encountered.
  // Instead of:
  //   if (overall_status.ok()) overall_status = new_status
  // Use:
  //   overall_status.UpdateIfOk(new_status);
  //
  // Suppose you want to execute two operations
  // (regardless of whether or not the first operation failed),
  // but want to return an error if either of the operations failed.
  // Instead of:
  // Status s = Operation1();
  // Status s2 = Operation2();
  // if (s.ok()) s = s2;
  // Use:
  // Status s = Operation1();
  // s.UpdateIfOk(Operation2());
  void UpdateIfOk(const Status& new_status);

  // Clear this status object to contain the OK code and no error message.
  void Clear();

  // Accessor
  MUST_USE_RETURN_VALUE
  bool ok() const;

  MUST_USE_RETURN_VALUE
  int error_code() const;

  MUST_USE_RETURN_VALUE
  const ::base::Location& location() const;

  MUST_USE_RETURN_VALUE
  const std::string& error_message() const;

  MUST_USE_RETURN_VALUE
  const ErrorSpace* error_space() const;

  // Returns the canonical code for this Status value.  Automatically
  // converts to the canonical space if necessary.
  ::basic::error::Code CanonicalCode() const;

  // Sets the equivalent canonical code for a Status with a
  // non-canonical error space.
  void SetCanonicalCode(int canonical_code);

  bool operator==(const Status& x) const;
#if __cplusplus <= 201703L
  bool operator!=(const Status& x) const;
#endif

  // Returns true iff this->CanonicalCode() == expected.
  MUST_USE_RETURN_VALUE
  bool Matches(::basic::error::Code expected) const;

  // Returns true iff this has the same error_space, error_code,
  // and canonical_code as "x".  I.e., the two Status objects are
  // identical except possibly for the error message.
  MUST_USE_RETURN_VALUE
  bool Matches(const Status& x) const;

  // Return a combination of the error code name and message.
  MUST_USE_RETURN_VALUE
  std::string ToString() const;

  // Returns a copy of the status object in the canonical error space.  This
  // will use the canonical code from the status protocol buffer (if present) or
  // the result of passing this status to the ErrorSpace CanonicalCode method.
  MUST_USE_RETURN_VALUE
  Status ToCanonical() const;

  // If this->Matches(x), return without doing anything.
  // Else die with an appropriate error message.
  void CheckMatches(const Status& x) const;

  // Ignores any errors. This method does nothing except potentially suppress
  // complaints from any tools that are checking that errors are not dropped on
  // the floor.
  void IgnoreError() const;

  // Swap the contents of *this with *that
  void Swap(basic::Status* that) {
    Rep* t = this->rep_;
    this->rep_ = that->rep_;
    that->rep_ = t;
  }

  // Returns a copy of the status object with error message stripped off.
  // Useful for comparing against expected status when error message
  // might vary, e.g.
  //     EXPECT_EQ(expected_status, real_status.StripMessage());
  MUST_USE_RETURN_VALUE
  Status StripMessage() const;

 private:
  // Reference-counted representation
  static const unsigned int kGlobalRef = 0;

  struct Rep {
    std::atomic<unsigned int> ref;  // reference count.
    int code;                       // code >= 0
    int canonical_code;             // 0 means use space to calculate
    const ErrorSpace* space_ptr;    // NULL means canonical_space()
    std::string* message_ptr;       // NULL means empty
    // Each ERROR status must provide `Location`.
    // OK status does not need `Location`.
    // You can manually "chain" locations (converted to strings)
    // from multiple error statuses to build their stacktrace.
    ::base::Location location;
  };
  Rep* rep_;  // Never NULL.

  static void UnrefSlow(Rep*);
  inline static void Ref(Rep* r) {
    // Do not adjust refs for globals
    if (r->ref != kGlobalRef) {
      ++r->ref;
    }
  }
  inline static void Unref(Rep* r) {
    // Do not adjust refs for globals
    if (r->ref != kGlobalRef) {
      UnrefSlow(r);
    }
  }

  void InternalSet(const ::base::Location& location, const ErrorSpace* space, int code, const std::string& msg,
                   int canonical_code);

  // Returns the canonical code from the status protocol buffer (if present) or
  // the result of passing this status to the ErrorSpace CanonicalCode method.
  int RawCanonicalCode() const;

  // REQUIRES: !ok()
  // Ensures rep_ is not shared with any other Status.
  void PrepareToModify();

  MUST_USE_RETURN_VALUE
  static Rep* NewRep(const ErrorSpace*
    , int code
    , const std::string&
    , const ::base::Location&
    , int canonical_code);
  static void ResetRep(Rep* rep
    , const ErrorSpace*
    , int code
    , const std::string&
    , const ::base::Location&
    , int canonical_code);
  static bool EqualsSlow(const ::basic::Status& a, const ::basic::Status& b);

  // Machinery for linker initialization of the global Status objects.
  struct Pod;
  static Rep global_reps[];
  static const Pod globals[];
  static const std::string* EmptyString();
};

// Base class for all error spaces.  An error space is a collection
// of related error codes.  All error codes are non-zero.
// Zero always means success.
//
// NOTE:
// All ErrorSpace objects must be created before the end of the module
// initializer phase (see "base/googleinit.h"). In particular, ErrorSpace
// objects should not be lazily created unless some mechanism forces this to
// occur in the module initializer phase. In most cases, ErrorSpace objects
// should just be created by a module initializer e.g.:
//
//     REGISTER_MODULE_INITIALIZER(ThisModule, {
//         ThisModule::InitErrorSpace();
//         ... other module initialization
//     });
//
// This rule ensures that ErrorSpace::Find(), which cannot be called until
// after the module initializer phase, will see a complete ErrorSpace
// registry.
//
class ErrorSpace {
 public:
  // Return the name of this error space
  const std::string& SpaceName() const { return name_; }

  // Return a string corresponding to the specified error code.
  virtual std::string String(int code) const = 0;

  // Return the equivalent canonical code for the given status. ErrorSpace
  // implementations should override this method to provide a custom
  // mapping. The default is to always return UNKNOWN. It is an error to pass a
  // Status that does not belong to this space; ErrorSpace implementations
  // should return UNKNOWN in that case.
  virtual ::basic::error::Code CanonicalCode(
      const ::basic::Status& status) const {
    return error::UNKNOWN;
  }

  // Find the error-space with the specified name.  Return the
  // space object, or NULL if not found.
  //
  // NOTE: Do not call Find() until after InitGoogle() returns.
  // Otherwise, some module intializers that register error spaces may not
  // have executed and Find() might not locate the error space of
  // interest.
  static ErrorSpace* Find(const std::string& name);

  // ErrorSpace is neither copyable nor movable.
  ErrorSpace(const ErrorSpace&) = delete;
  ErrorSpace& operator=(const ErrorSpace&) = delete;

 protected:
  explicit ErrorSpace(const char* name);

  // Prevent deletions of ErrorSpace objects by random clients
  virtual ~ErrorSpace();

 private:
  const std::string name_;
};

// ::basic::Status success comparison.
// This is better than CHECK((val).ok()) because the embedded
// error string gets printed by the CHECK_EQ.
#define CHECK_OK(val) CHECK((val).ok()) << (val)
#define QCHECK_OK(val) QCHECK((val).ok()) << (val)
#define DCHECK_OK(val) DCHECK((val).ok()) << (val)

// -----------------------------------------------------------------
// Implementation details follow

inline Status::Status()
  : rep_(&global_reps[0])
{}

inline Status::Status(const Status& x)
  : rep_(x.rep_)
{
  Ref(rep_);
}

inline Status& Status::operator=(const Status& x) {
  Rep* old_rep = rep_;
  if (x.rep_ != old_rep) {
    Ref(x.rep_);
    rep_ = x.rep_;
    Unref(old_rep);
  }
  return *this;
}

inline void Status::UpdateIfOk(const Status& new_status) {
  if (ok()) {
    *this = new_status;
  }
}

inline Status::~Status() { Unref(rep_); }

inline bool Status::ok() const { return rep_->code == 0; }

inline int Status::error_code() const { return rep_->code; }

inline const ::base::Location& Status::location() const {
  return rep_->location;
}

inline const std::string& Status::error_message() const {
  return rep_->message_ptr ? *rep_->message_ptr : *EmptyString();
}

inline const ErrorSpace* Status::error_space() const {
  return rep_->space_ptr ? rep_->space_ptr : canonical_space();
}

inline bool Status::Matches(const Status& x) const {
  return (this->error_code() == x.error_code() &&
          this->error_space() == x.error_space() &&
          this->RawCanonicalCode() == x.RawCanonicalCode());
}

inline bool Status::operator==(const Status& x) const {
  return (this->rep_ == x.rep_) || EqualsSlow(*this, x);
}

#if __cplusplus <= 201703L
inline bool Status::operator!=(const Status& x) const { return !(*this == x); }
#endif

inline bool Status::Matches(::basic::error::Code expected) const {
  return CanonicalCode() == expected;
}

extern std::ostream& operator<<(std::ostream& os, const Status& x);

// Returns an OK status, equivalent to a default constructed instance.
Status OkStatus();

inline Status OkStatus() { return Status(); }

// Returns an CANCELLED status, equivalent to a default constructed instance.
Status CancelledStatus(const ::base::Location& location, const std::string& error_message = "");

inline Status CancelledStatus(const ::base::Location& location, const std::string& error_message) {
  return Status(location, ::basic::Status::canonical_space(),
                ::basic::Status::CANCELLED_CODE, error_message);
}

// Returns an UNKNOWN status, equivalent to a default constructed instance.
Status UnknownStatus(const ::base::Location& location, const std::string& error_message = "");

inline Status UnknownStatus(const ::base::Location& location, const std::string& error_message) {
  return Status(location, ::basic::Status::canonical_space(),
                ::basic::Status::UNKNOWN_CODE, error_message);
}

}  // namespace basic
