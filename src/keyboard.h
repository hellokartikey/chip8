#ifndef HK_CHIP8_KEYBOARD_H
#define HK_CHIP8_KEYBOARD_H

#include "common.h"

namespace chip8 {
class keyboard {
 public:
  [[nodiscard]] auto is_pressed(keys key) const -> bool;
  auto press(keys key) -> void;

 private:
  keys m_key{keys::NONE};
};
}  // namespace chip8

#endif
