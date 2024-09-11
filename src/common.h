#ifndef HK_CHIP8_COMMON_H
#define HK_CHIP8_COMMON_H

#include <array>
#include <cstdint>
#include <string>
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

  PC = 0xf0,
  R = 0xf1,
  I = 0xf2,
  INVALID = 0xff
};

constexpr auto from_reg(regs reg) { return std::to_underlying(reg); }

constexpr auto to_reg(byte reg) { return static_cast<regs>(reg & 0x000f); }

constexpr auto str_to_reg(const std::string& str) -> regs {
  auto reg = regs::INVALID;

  if (str == "V0") {
    reg = regs::V0;
  } else if (str == "V1") {
    reg = regs::V1;
  } else if (str == "V2") {
    reg = regs::V2;
  } else if (str == "V3") {
    reg = regs::V3;
  } else if (str == "V4") {
    reg = regs::V4;
  } else if (str == "V5") {
    reg = regs::V5;
  } else if (str == "V6") {
    reg = regs::V6;
  } else if (str == "V7") {
    reg = regs::V7;
  } else if (str == "V8") {
    reg = regs::V8;
  } else if (str == "V9") {
    reg = regs::V9;
  } else if (str == "VA") {
    reg = regs::VA;
  } else if (str == "VB") {
    reg = regs::VB;
  } else if (str == "VC") {
    reg = regs::VC;
  } else if (str == "VD") {
    reg = regs::VD;
  } else if (str == "VE") {
    reg = regs::VE;
  } else if (str == "VF") {
    reg = regs::VF;
  } else if (str == "PC") {
    reg = regs::PC;
  } else if (str == "R") {
    reg = regs::R;
  } else if (str == "I") {
    reg = regs::I;
  }

  return reg;
}

constexpr auto reg_to_str(regs reg) -> std::string {
  using namespace std::string_literals;

  switch (reg) {
    case regs::V0:
      return "V0"s;
    case regs::V1:
      return "V1"s;
    case regs::V2:
      return "V2"s;
    case regs::V3:
      return "V3"s;
    case regs::V4:
      return "V4"s;
    case regs::V5:
      return "V5"s;
    case regs::V6:
      return "V6"s;
    case regs::V7:
      return "V7"s;
    case regs::V8:
      return "V8"s;
    case regs::V9:
      return "V9"s;
    case regs::VA:
      return "VA"s;
    case regs::VB:
      return "VB"s;
    case regs::VC:
      return "VC"s;
    case regs::VD:
      return "VD"s;
    case regs::VE:
      return "VE"s;
    case regs::VF:
      return "VF"s;
    case regs::PC:
      return "PC"s;
    case regs::R:
      return "R"s;
    case regs::I:
      return "I"s;
    default:
      return "INVALID"s;
  }
}

constexpr auto MEMORY_SIZE = 0x1000z;
using memory = std::array<byte, MEMORY_SIZE>;

struct screen_tag_t {
  int x;
};
constexpr auto with_screen = screen_tag_t{.x = 0};

using font = std::array<byte, 5>;
using font_table = std::array<font, 16>;
constexpr auto letters = font_table{
    font{0xf0, 0x90, 0x90, 0x90, 0xf0},  // 0
    font{0x20, 0x60, 0x20, 0x20, 0x70},  // 1
    font{0xf0, 0x10, 0xf0, 0x80, 0xf0},  // 2
    font{0xf0, 0x10, 0xf0, 0x10, 0xf0},  // 3
    font{0x90, 0x90, 0xf0, 0x10, 0x10},  // 4
    font{0xf0, 0x80, 0xf0, 0x10, 0xf0},  // 5
    font{0xf0, 0x80, 0xf0, 0x90, 0xf0},  // 6
    font{0xf0, 0x10, 0x20, 0x40, 0x40},  // 7
    font{0xf0, 0x90, 0xf0, 0x90, 0xf0},  // 8
    font{0xf0, 0x90, 0xf0, 0x10, 0xf0},  // 9
    font{0xf0, 0x90, 0xf0, 0x90, 0x90},  // A
    font{0xe0, 0x90, 0xe0, 0x90, 0xe0},  // B
    font{0xf0, 0x80, 0x80, 0x80, 0xf0},  // C
    font{0xe0, 0x90, 0x90, 0x90, 0xe0},  // D
    font{0xf0, 0x80, 0xf0, 0x80, 0xf0},  // E
    font{0xf0, 0x80, 0xf0, 0x80, 0x80}   // F
};
}  // namespace chip8

#endif
