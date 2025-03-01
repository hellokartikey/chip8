#ifndef HK_CHIP8_INSTRUCTIONS_H
#define HK_CHIP8_INSTRUCTIONS_H

#include <initializer_list>

#include "common.h"
#include "helpers.h"

namespace chip8::opcode {
using instructions = std::initializer_list<word>;

// Null helper
constexpr auto NOP() -> word { return 0x000; }

// Clear the display
constexpr auto CLS() -> word { return 0x00e0; }

// Return from a subroutine
constexpr auto RET() -> word { return 0x00ee; }

// System opcode
constexpr auto SYS(word addr) -> word { return address(addr); }

// Jump to location addr
constexpr auto JP(word addr) -> word { return 0x1000 | address(addr); }

// Call subroutine at addr
constexpr auto CALL(word addr) -> word { return 0x2000 | address(addr); }

// Skip next instruction if reg == value
constexpr auto SE(regs reg, byte value) -> word {
  return 0x3000 | (as<word>(reg) << 8) | as<word>(value);
}

// Skip next instruction if reg != value
constexpr auto SNE(regs reg, byte value) -> word {
  return 0x4000 | (as<word>(reg) << 8) | as<word>(value);
}

// Skip next instruction if reg1 == reg2
constexpr auto SE(regs reg1, regs reg2) -> word {
  return 0x5000 | (as<word>(reg1) << 8) | (as<word>(reg2) << 4);
}

// Set reg = value
constexpr auto LD(regs reg, byte value) -> word {
  return 0x6000 | (as<word>(reg) << 8) | as<word>(value);
}

// Set reg = reg + value
constexpr auto ADD(regs reg, byte value) -> word {
  return 0x7000 | (as<word>(reg) << 8) | as<word>(value);
}

// Set dst = src
constexpr auto LD(regs dst, regs src) -> word {
  return 0x8000 | (as<word>(dst) << 8) | (as<word>(src) << 4);
}

// Set dst = dst | src
constexpr auto OR(regs dst, regs src) -> word {
  return 0x8001 | (as<word>(dst) << 8) | (as<word>(src) << 4);
}

// Set dst = dst & src
constexpr auto AND(regs dst, regs src) -> word {
  return 0x8002 | (as<word>(dst) << 8) | (as<word>(src) << 4);
}

constexpr auto XOR(regs dst, regs src) -> word {
  return 0x8003 | (as<word>(dst) << 8) | (as<word>(src) << 4);
}

constexpr auto ADD(regs dst, regs src) -> word {
  return 0x8004 | (as<word>(dst) << 8) | (as<word>(src) << 4);
}

constexpr auto SUB(regs dst, regs src) -> word {
  return 0x8005 | (as<word>(dst) << 8) | (as<word>(src) << 4);
}

constexpr auto SHR(regs reg, regs none = regs::V0) -> word {
  return 0x8006 | (as<word>(reg) << 8) | (as<word>(none) << 4);
}

constexpr auto SUBN(regs dst, regs src) -> word {
  return 0x8007 | (as<word>(dst) << 8) | (as<word>(src) << 4);
}

constexpr auto SHL(regs reg, regs none = regs::V0) -> word {
  return 0x800e | (as<word>(reg) << 8) | (as<word>(none) << 4);
}

constexpr auto SNE(regs reg1, regs reg2) -> word {
  return 0x9000 | (as<word>(reg1) << 8) | (as<word>(reg2) << 4);
}

constexpr auto LD_I(word addr) -> word { return 0xa000 | address(addr); }

constexpr auto JP_V0(word addr) -> word { return 0xb000 | address(addr); }

constexpr auto RND(regs reg, byte value) -> word {
  return 0xc000 | (as<word>(reg) << 8) | value;
}

constexpr auto DRW(regs reg_x, regs reg_y, byte count) -> word {
  return 0xd000 | (as<word>(reg_x) << 8) | (as<word>(reg_y) << 4) |
         (count & 0x0f);
}

constexpr auto SKP(regs reg) -> word { return 0xe09e | (as<word>(reg) << 8); }

constexpr auto SKNP(regs reg) -> word { return 0xe0a1 | (as<word>(reg) << 8); }

constexpr auto LD_VX_DT(regs reg) -> word {
  return 0xf007 | (as<word>(reg) << 8);
}

constexpr auto LD_KEY(regs reg) -> word {
  return 0xf00a | (as<word>(reg) << 8);
}

constexpr auto LD_DT(regs reg) -> word { return 0xf015 | (as<word>(reg) << 8); }

constexpr auto LD_ST(regs reg) -> word { return 0xf018 | (as<word>(reg) << 8); }

constexpr auto ADD_I(regs reg) -> word { return 0xf01e | (as<word>(reg) << 8); }

constexpr auto LD_F(regs reg) -> word { return 0xf029 | (as<word>(reg) << 8); }

constexpr auto LD_B(regs reg) -> word { return 0xf033 | (as<word>(reg) << 8); }

constexpr auto LD_I(regs reg) -> word { return 0xf055 | (as<word>(reg) << 8); }

constexpr auto LD_VX_I(regs reg) -> word {
  return 0xf065 | (as<word>(reg) << 8);
}
}  // namespace chip8::opcode

#endif
