#include "keyboard.h"

#include <raylib.h>

#include <optional>

#include "common.h"

namespace chip8 {
auto keyboard::is_pressed(keys key) const -> bool {
  if (m_key) {
    return *m_key == key;
  }

  return false;
}

auto keyboard::is_pressed() const -> bool { return m_key.has_value(); }

auto keyboard::press(keys key) -> void { m_key = key; }

auto keyboard::clear() -> void { m_key = std::nullopt; }

auto keyboard::check() -> void {
  for (const auto& [key, value] : KEYBOARD_MAP) {
    if (IsKeyDown(key)) {
      press(value);
      return;
    }
  }

  clear();
}

auto keyboard::key() const -> std::optional<keys> { return m_key; }
}  // namespace chip8
