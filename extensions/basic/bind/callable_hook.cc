#include "basic/bind/callable_hook.h" // IWYU pragma: associated

namespace basic {

GlobalCallableHooksRegistry::CallableSlot::~CallableSlot()
{}

// static
GlobalCallableHooksRegistry* GlobalCallableHooksRegistry::GetInstance()
{
  /// \note construction assumed to be thread-safe due to `base::NoDestructor`
  /// and constructed on first access
  static ::base::NoDestructor<GlobalCallableHooksRegistry> instance;
  return instance.get();
}

} // namespace basic
