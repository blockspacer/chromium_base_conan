#pragma once

#include <base/location.h>

/// \note `WithDetails` allows even "successful" status to have "reason string",
/// unlike `::basic::Status` or `::basic::StatusOr`.
//
// In functions with priority-ordered return statements, this helps with
// identifying the statement that took effect.
//
// Instead of writing comments near `return`:
// int f() {
//   ...
//   return value1;   // explanation1
//   ...
//   return value2;   // explanation2
// }
//
// Write:
// WithDetails<int> f() {
//   ...
//   return {value1; FROM_HERE, "explanation1..."};
//   ...
//   return {value2; FROM_HERE, "explanation2..."};
// }
//
// The caller should unpack the struct, and can print the reason string
// (and source location) when desired.
//
// MOTIVATION
//
// Suppose you create API function `doLogicOrCrash()` that returns `bool`
// You need to log both success reasons (different success reasons)
// and fail (crash) reasons somehow.
// But it is bad to log something in API function,
// so you need to return reason string using `WithDetails`.
//
namespace basic {

// You can change type tag to create custom strong alias like so:
//
// // #include <basic/core/typed_enum.h>
// TYPED_ENUM(PrettyEnum, int, (kZero)(kLow)(kNormal))
//
// // same as `::basic::WithDetails<PrettyEnum, class MyPrettyFunctionTag>`
// using MyPrettyFuncResult
//   = ::basic::WithData<
//         PrettyEnum
//         , ::basic::DetailChars
//         , class MyPrettyFunctionTag
//       >;
//
// MyPrettyFuncResult myPrettyFunction(int val) {
//   if(val == 0)
//     return {PrettyEnum::kZero, FROM_HERE, "explanation1..."};
//   else if(val < 0)
//     return {PrettyEnum::kLow, FROM_HERE, "explanation1..."};
//
//   return {PrettyEnum::kNormal, FROM_HERE, "explanation2..."};
// }
//
// MyPrettyFuncResult my_res = myPrettyFunction(3);
//
// // #include <basic/strings/substitute.h>
// DVLOG(99)
//   << basic::Substitute(
//        "myFunction resulted in $1"
//        " because of reason $2"
//        " from code location $3."
//        , my_res.value
//        , my_res.reason
//        , my_res.location);
//
class DefaultWithDataTag;

// Usually `CustomData` is utf8, utf16 string etc.
//
// USAGE
//
// struct MyData { DetailChars data; }
//
// WithData<int, MyData> f() {
//   ...
//   return {value1; FROM_HERE, MyData{"explanation1..."}};
//   ...
//   return {value2; FROM_HERE, MyData{"explanation2..."}};
// }
//
template <typename T, typename CustomData, typename Tag = DefaultWithDataTag>
struct WithData
{
  T value;
  // Location in source code, useful for debug purposes.
  const base::Location location;
  // A simple string literal shall suffice.
  CustomData reason;
};

// used by `WithDetails` below
using DetailChars = const char*;

// USAGE
//
// WithDetails<int> f() {
//   ...
//   return {value1; FROM_HERE, "explanation1..."};
//   ...
//   return {value2; FROM_HERE, "explanation2..."};
// }
//
template <typename T, typename Tag = DefaultWithDataTag>
using WithDetails = WithData<T, DetailChars, Tag>;

}  // namespace basic
