#include "keyboard.h"

#include <raylib.h>

#include <optional>

#include "common.h"
#include "helpers.h"

namespace chip8 {
auto keyboard::is_pressed(keys key) const -> bool {
  return m_keys.test(as<int>(key));
}

auto keyboard::is_pressed() const -> bool { return m_keys.any(); }

auto keyboard::press(keys key) -> void { m_keys.set(as<int>(key)); }

auto keyboard::clear() -> void { m_keys.reset(); }

auto keyboard::check() -> void {
  for (const auto& [key, value] : KEYBOARD_MAP) {
    if (IsKeyDown(key)) {
      press(value);
      return;
    }
  }

  clear();
}

auto keyboard::key() const -> std::optional<keys> {
  for (auto idx = 0; idx < 16; idx++) {
    if (m_keys.test(idx)) {
      return as<keys>(idx);
    }
  }

  return std::nullopt;
}
}  // namespace chip8
