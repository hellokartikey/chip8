#ifndef HK_CHIP8_KEYBOARD_H
#define HK_CHIP8_KEYBOARD_H

#include <bitset>
#include <optional>

#include "common.h"

namespace chip8 {
class keyboard {
 public:
  [[nodiscard]] auto is_pressed(keys key) const -> bool;
  [[nodiscard]] auto is_pressed() const -> bool;

  auto press(keys key) -> void;
  auto clear(keys key) -> void;
  auto clear() -> void;

  [[nodiscard]] auto key() const -> std::optional<keys>;

  auto check() -> void;

 private:
  std::bitset<16> m_keys;
};
}  // namespace chip8

#endif
