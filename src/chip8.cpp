#include "chip8.h"

#include <fmt/core.h>

#include <utility>

namespace chip8 {
auto chip8::get(regs reg) -> byte& {
  return m_registers.at(std::to_underlying(reg));
}

auto chip8::dump_memory() -> memory& { return m_memory; }

auto chip8::print_memory(word begin, word end) const -> void {
  fmt::print("      ");

  for (auto i = byte{}; i < 0x10; i++) {
    fmt::print("{:2x} ", i);
  }

  auto start = begin & 0xfff0;
  for (auto addr = start; addr < end; addr++) {
    if ((addr & 0x000f) == 0x0000) {
      fmt::print("\n {:02x}0  ", static_cast<word>(addr >> 4));
    }

    if (addr < begin) {
      fmt::print("   ");
    } else {
      fmt::print("{:02x} ", read(addr));
    }
  }

  fmt::print("\n");
}

auto chip8::read(word addr) const -> byte {
  if (addr >= MEMORY_SIZE) {
    return 0x00;
  }

  return m_memory.at(addr);
}

auto chip8::write(word addr, byte data) -> void {
  if (addr >= MEMORY_SIZE) {
    return;
  }

  m_memory.at(addr) = data;
}

auto chip8::read16(word addr) const -> word {
  if (addr > MEMORY_SIZE) {
    return 0x00;
  }

  auto upper = static_cast<word>(read(addr) << 8);
  auto lower = static_cast<word>(read(addr + 1));

  return upper | lower;
}

auto chip8::write16(word addr, word data) -> void {
  if (addr >= MEMORY_SIZE) {
    return;
  }

  auto upper = static_cast<byte>(data >> 8);
  auto lower = static_cast<byte>(data & 0x00ff);

  write(addr, upper);
  write(addr + 1, lower);
}

auto chip8::fetch() -> word {
  auto opcode = read16(m_pc);
  m_pc += 2;
  return opcode;
}

auto chip8::start_addr() const -> word { return m_start_addr; }

auto chip8::load_program(instructions program) -> void {}
}  // namespace chip8
