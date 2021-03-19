#pragma once

#include "basic/status/status_macros.h"

#include <base/macros.h>
#include <base/callback_forward.h>

namespace basic {

using RepeatingStatusClosure = base::RepeatingCallback<basic::Status(void)>;

template<typename... Args>
using RepeatingStatus = base::RepeatingCallback<basic::Status(Args...)>;

template<typename T>
using RepeatingStatusOrClosure = base::RepeatingCallback<basic::StatusOr<T>(void)>;

template<typename T, typename... Args>
using RepeatingStatusOr = base::RepeatingCallback<basic::StatusOr<T>(Args...)>;

using OnceStatusClosure = base::OnceCallback<basic::Status(void)>;

template<typename... Args>
using OnceStatus = base::OnceCallback<basic::Status(Args...)>;

template<typename T>
using OnceStatusOrClosure = base::OnceCallback<basic::StatusOr<T>(void)>;

template<typename T, typename... Args>
using OnceStatusOr = base::OnceCallback<basic::StatusOr<T>(Args...)>;

}  // namespace basic
