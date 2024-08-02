#ifndef HK_CHIP8_COMMON_H
#define HK_CHIP8_COMMON_H

#include <array>
#include <bitset>
#include <cstdint>
#include <utility>

namespace chip8 {
using byte = std::uint8_t;
using word = std::uint16_t;

constexpr auto operator""_w(unsigned long long int value) -> word {
  return static_cast<word>(value);
}

constexpr auto operator""_b(unsigned long long int value) -> byte {
  return static_cast<byte>(value);
}

constexpr auto address(word addr) -> word {
  return static_cast<word>(addr & 0x0fff);
}

using registers = std::array<byte, 0x10>;

enum class regs : byte {
  V0 = 0x00,
  V1 = 0x01,
  V2 = 0x02,
  V3 = 0x03,
  V4 = 0x04,
  V5 = 0x05,
  V6 = 0x06,
  V7 = 0x07,
  V8 = 0x08,
  V9 = 0x09,
  VA = 0x0a,
  VB = 0x0b,
  VC = 0x0c,
  VD = 0x0d,
  VE = 0x0e,
  VF = 0x0f,

  PC = 0xab,
  INVALID = 0xff
};

constexpr auto from_reg(regs reg) { return std::to_underlying(reg); }

constexpr auto to_reg(byte reg) { return static_cast<regs>(reg & 0x000f); }

constexpr auto MEMORY_SIZE = 0x1000z;
using memory = std::array<byte, MEMORY_SIZE>;

// Index using (x, y)
constexpr auto SCREEN_WIDTH = 64Z;
constexpr auto SCREEN_HEIGHT = 32Z;
using screen = std::array<std::bitset<SCREEN_WIDTH>, SCREEN_HEIGHT>;
}  // namespace chip8

#endif
