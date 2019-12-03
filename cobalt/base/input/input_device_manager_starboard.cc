// Copyright 2015 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>

#include "cobalt/input/input_device_manager_desktop.h"

namespace cobalt {
namespace input {

// static
std::unique_ptr<InputDeviceManager> InputDeviceManager::CreateFromWindow(
    const KeyboardEventCallback& keyboard_event_callback,
    const PointerEventCallback& pointer_event_callback,
    const WheelEventCallback& wheel_event_callback,
#if SB_HAS(ON_SCREEN_KEYBOARD)
    const InputEventCallback& input_event_callback,
#endif  // SB_HAS(ON_SCREEN_KEYBOARD)
    system_window::SystemWindow* system_window) {
  return std::unique_ptr<InputDeviceManager>(new InputDeviceManagerDesktop(
      keyboard_event_callback, pointer_event_callback, wheel_event_callback,
#if SB_HAS(ON_SCREEN_KEYBOARD)
      input_event_callback,
#endif  // SB_HAS(ON_SCREEN_KEYBOARD)
      system_window));
}

}  // namespace input
}  // namespace cobalt
