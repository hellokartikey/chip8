#include "parser.h"

#include <cstddef>

#include "common.h"
#include "helpers.h"

namespace chip8 {
parsed_instruction::parsed_instruction(word opcode) : m_opcode(opcode) {}

auto parsed_instruction::get_byte(std::size_t index) const -> byte {
  switch (index) {
    case 0:
      return get_lo_byte();
    case 1:
      return get_hi_byte();
    default:
      return 0x00;
  }
}

auto parsed_instruction::get_lo_byte() const -> byte {
  return as<byte>(m_opcode & 0x00ff);
}

auto parsed_instruction::get_hi_byte() const -> byte {
  return as<byte>((m_opcode & 0xff00) >> 8);
}

auto parsed_instruction::get_nibble(std::size_t index) const -> byte {
  switch (index) {
    case 0:
      return as<byte>(m_opcode & 0x000f);
    case 1:
      return as<byte>((m_opcode & 0x00f0) >> 4);
    case 2:
      return as<byte>((m_opcode & 0x0f00) >> 8);
    case 3:
      return as<byte>((m_opcode & 0xf000) >> 12);
    default:
      return 0x00;
  }
}

auto parsed_instruction::get_addr() const -> word { return address(m_opcode); }

auto parsed_instruction::get_opcode() const -> word { return m_opcode; }
}  // namespace chip8
