#ifndef HK_CHIP8_INSTRUCTIONS_H
#define HK_CHIP8_INSTRUCTIONS_H

#include <initializer_list>

#include "common.h"

namespace chip8 {
using instructions = std::initializer_list<word>;

constexpr auto CLS() -> word { return 0x00e0; }

constexpr auto RET() -> word { return 0x00ee; }

constexpr auto JP(word addr) -> word { return 0x1000 | address(addr); }

constexpr auto CALL(word addr) -> word { return 0x2000 | address(addr); }

constexpr auto SE(regs reg, byte value) -> word {
  return 0x3000 | (from_reg(reg) << 8) | static_cast<word>(value);
}
}  // namespace chip8

#endif
