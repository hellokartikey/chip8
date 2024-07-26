#include "chip8.h"

#include <utility>

namespace chip8 {
auto chip8::get(regs reg) -> byte& {
  return m_registers.at(std::to_underlying(reg));
}

auto chip8::read(word addr) const -> byte { return m_memory.at(addr); }

auto chip8::write(word addr, byte data) -> void { m_memory.at(addr) = data; }

auto chip8::read16(word addr) const -> word {
  constexpr auto SHIFT_RIGHT = word{8};

  auto upper = static_cast<word>(read(addr) << SHIFT_RIGHT);
  auto lower = static_cast<word>(read(addr + 1));

  return upper | lower;
}

auto chip8::write16(word addr, word data) -> void {
  constexpr auto SHIFT_LEFT = word{8};
  constexpr auto FLAG = word{0x00ff};

  auto upper = static_cast<byte>(data >> SHIFT_LEFT);
  auto lower = static_cast<byte>(data & FLAG);

  write(addr, upper);
  write(addr + 1, lower);
}

auto chip8::fetch() -> word {
  auto opcode = read16(m_pc);
  m_pc += 2;
  return opcode;
}
}  // namespace chip8
