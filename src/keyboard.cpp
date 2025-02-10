#include "keyboard.h"

#include <raylib.h>

#include "common.h"

namespace chip8 {
auto keyboard::is_pressed(keys key) const -> bool {
  if (key == keys::NONE) {
    return m_key != key;
  }
  return m_key == key;
}

auto keyboard::press(keys key) -> void { m_key = key; }

auto keyboard::check() -> void {
  for (const auto& [key, value] : KEYBOARD_MAP) {
    if (IsKeyPressed(key)) {
      press(value);
      return;
    }
  }

  press(keys::NONE);
}

auto keyboard::key() const -> keys { return m_key; }
}  // namespace chip8
