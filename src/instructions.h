#ifndef HK_CHIP8_INSTRUCTIONS_H
#define HK_CHIP8_INSTRUCTIONS_H

#include <functional>
#include <initializer_list>

#include "common.h"

namespace chip8::opcode {
using instructions = std::initializer_list<word>;

// Null helper
constexpr auto NOP() -> word { return 0x000; }

// Clear the display
constexpr auto CLS() -> word { return 0x00e0; }

// Return from a subroutine
constexpr auto RET() -> word { return 0x00ee; }

// Jump to location addr
constexpr auto JP(word addr) -> word { return 0x1000 | address(addr); }

// Call subroutine at addr
constexpr auto CALL(word addr) -> word { return 0x2000 | address(addr); }

// Skip next instruction if reg == value
constexpr auto SE(regs reg, byte value) -> word {
  return 0x3000 | (from_reg(reg) << 8) | static_cast<word>(value);
}

// Skip next instruction if reg != value
constexpr auto SNE(regs reg, byte value) -> word {
  return 0x4000 | (from_reg(reg) << 8) | static_cast<word>(value);
}

// Skip next instruction if reg1 == reg2
constexpr auto SE(regs reg1, regs reg2) -> word {
  return 0x5000 | (from_reg(reg1) << 8) | (from_reg(reg2) << 4);
}

// Set reg = value
constexpr auto LD(regs reg, byte value) -> word {
  return 0x6000 | (from_reg(reg) << 8) | static_cast<word>(value);
}

// Set reg = reg + value
constexpr auto ADD(regs reg, byte value) -> word {
  return 0x7000 | (from_reg(reg) << 8) | static_cast<word>(value);
}

// Set reg1 = reg2
constexpr auto LD(regs reg1, regs reg2) -> word {
  return 0x8000 | (from_reg(reg1) << 8) | (from_reg(reg2) << 4);
}
}  // namespace chip8::opcode

#endif
