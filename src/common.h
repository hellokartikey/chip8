#ifndef HK_CHIP8_COMMON_H
#define HK_CHIP8_COMMON_H

#include <raylib.h>

#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <utility>

#define BG_COLOR SKYBLUE
#define FG_COLOR DARKPURPLE

namespace chip8 {
constexpr auto WIDTH = 64Z;
constexpr auto HEIGHT = 32Z;

constexpr auto PIXEL = 10;

using byte = std::uint8_t;
using word = std::uint16_t;

template <typename To, typename From>
auto as(const From& from) {
  return static_cast<To>(from);
}

constexpr auto operator""_w(unsigned long long int value) -> word {
  return as<word>(value);
}

constexpr auto operator""_b(unsigned long long int value) -> byte {
  return as<byte>(value);
}

constexpr auto address(word addr) -> word { return as<word>(addr & 0x0fff); }

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

enum class keys : byte {
  KEY_0 = 0x00,
  KEY_1 = 0x01,
  KEY_2 = 0x02,
  KEY_3 = 0x03,
  KEY_4 = 0x04,
  KEY_5 = 0x05,
  KEY_6 = 0x06,
  KEY_7 = 0x07,
  KEY_8 = 0x08,
  KEY_9 = 0x09,
  KEY_A = 0x0a,
  KEY_B = 0x0b,
  KEY_C = 0x0c,
  KEY_D = 0x0d,
  KEY_E = 0x0e,
  KEY_F = 0x0f,

  NONE = 0xff,
};

inline const std::map<int, keys> KEYBOARD_MAP{// Row 1
                                              {KEY_ONE, keys::KEY_1},
                                              {KEY_TWO, keys::KEY_2},
                                              {KEY_THREE, keys::KEY_3},
                                              {KEY_FOUR, keys::KEY_C},

                                              // Row 2
                                              {KEY_Q, keys::KEY_4},
                                              {KEY_W, keys::KEY_5},
                                              {KEY_E, keys::KEY_6},
                                              {KEY_R, keys::KEY_D},

                                              // Row 3
                                              {KEY_A, keys::KEY_7},
                                              {KEY_S, keys::KEY_8},
                                              {KEY_D, keys::KEY_9},
                                              {KEY_F, keys::KEY_E},

                                              // Row 4
                                              {KEY_Z, keys::KEY_A},
                                              {KEY_X, keys::KEY_0},
                                              {KEY_C, keys::KEY_B},
                                              {KEY_V, keys::KEY_F}};

constexpr auto from_key(keys key) { return std::to_underlying(key); }

constexpr auto to_key(byte key) { return as<keys>(key); }

constexpr auto from_reg(regs reg) { return std::to_underlying(reg); }

constexpr auto to_reg(byte reg) { return as<regs>(reg & 0x000f); }

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
