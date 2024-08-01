#include "chip8.h"

#include <fmt/core.h>

#include <iostream>
#include <sstream>
#include <utility>

#include "parser.h"

namespace chip8 {
auto chip8::get(regs reg) -> byte& {
  return m_registers.at(std::to_underlying(reg));
}

auto chip8::get(regs reg) const -> byte {
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

auto chip8::print_registers() const -> void {
  fmt::print("V0: {:02x}\tV1: {:02x}\t", get(regs::V0), get(regs::V1));
  fmt::print("V2: {:02x}\tV3: {:02x}\n", get(regs::V2), get(regs::V3));
  fmt::print("V4: {:02x}\tV5: {:02x}\t", get(regs::V4), get(regs::V5));
  fmt::print("V6: {:02x}\tV7: {:02x}\n", get(regs::V6), get(regs::V7));
  fmt::print("V8: {:02x}\tV9: {:02x}\t", get(regs::V8), get(regs::V9));
  fmt::print("VA: {:02x}\tVB: {:02x}\n", get(regs::VA), get(regs::VB));
  fmt::print("VC: {:02x}\tVD: {:02x}\t", get(regs::VC), get(regs::VD));
  fmt::print("VE: {:02x}\tVF: {:02x}\n", get(regs::VE), get(regs::VF));

  fmt::print("PC: {:04x}\n", m_pc);
  fmt::print("SP: {:02x}\n", m_stack.size());
}

auto chip8::parse_opcode(word opcode) const -> std::string {
  auto parsed = parsed_instruction{opcode};

  switch (parsed.get_nibble(3)) {
    case 0x0:
      switch (parsed.get_opcode()) {
        case opcode::CLS():
          return fmt::format("CLS");
        case opcode::RET():
          return fmt::format("RET");
        default:
          return fmt::format("SYS {:03x}", parsed.get_addr());
      }
      break;
    case 0x1:
      return fmt::format("JP {:03x}", parsed.get_addr());
    case 0x2:
      return fmt::format("CALL {:03x}", parsed.get_addr());
    default:
      return fmt::format("INVALID {:04x}", parsed.get_opcode());
  }
};

auto chip8::print_opcode(word addr) const -> void {
  if (addr == m_pc) {
    fmt::print(
        "{:03x} [=]\t"
        "{:04x}\t"
        "{}\n",
        addr, read16(addr), parse_opcode(read16(addr)));
  } else {
    fmt::print(
        "{:03x}\t"
        "{:04x}\t"
        "{}\n",
        addr, read16(addr), parse_opcode(read16(addr)));
  }
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

auto chip8::load_program(opcode::instructions program) -> void {
  auto addr = start_addr();
  m_pc = addr;

  for (const auto& opcode : program) {
    write16(addr, opcode);
    addr += 2;
  }
}

auto chip8::exec() -> void {
  auto parsed = parsed_instruction(fetch());

  switch (parsed.get_nibble(3)) {
    case 0x0:
      switch (parsed.get_opcode()) {
        case 0x00e0:
          cls();
          return;
        case 0x00ee:
          ret();
          return;
        default:
          sys(parsed.get_addr());
          return;
      }
      break;
    case 0x1:
      jp(parsed.get_addr());
      return;
    case 0x2:
      call(parsed.get_addr());
      return;
    default:
      invalid(parsed.get_opcode());
      return;
  }

  invalid(parsed.get_opcode());
}  // namespace chip8

auto chip8::exec_n(std::uint64_t count) -> void {
  for (; count > 0; count--) {
    exec();
  }
}

auto chip8::exec_all() -> void {
  while (true) {
    exec();
  }
}

auto chip8::debug_shell() -> void {
  fmt::print("Interactive debug shell!\n");

  while (true) {
    if (std::cin.eof()) {
      break;
    }

    fmt::print("$ ");

    auto line = std::string{};
    std::getline(std::cin, line);
    auto cmd = std::stringstream{line};

    auto sub_command = std::string{};
    cmd >> sub_command;

    if (sub_command == "regs") {
      print_registers();
    } else if (sub_command == "mem") {
      debug_mem(cmd);
    } else if (sub_command == "exit") {
      break;
    } else if (sub_command == "dasm") {
      debug_dasm(cmd);
    } else if (sub_command == "help") {
      debug_help(cmd);
    }
  }

  fmt::print("exiting...\n");
}

auto chip8::debug_mem(std::stringstream& cmd) -> void {
  auto begin = 0x0200_w;
  auto end = 0x0000_w;

  if (not cmd.eof()) {
    cmd >> std::hex >> begin;
  }

  if (not cmd.eof()) {
    cmd >> std::hex >> end;
  }

  if (begin > end) {
    end = (begin + 0x0040_w);
  }

  begin &= 0xfff0;
  end &= 0xfff0;

  print_memory(address(begin), address(end));
}

auto chip8::debug_help(std::stringstream& cmd) -> void {
  fmt::print(
      "Available commands\n"
      "\tregs\t\t\tPrint all registers\n"
      "\tmem [begin] [end]\tPrint memory\n"
      "\tdasm [begin] [end]\tDisassemble instructions\n"
      "\texit\t\t\tExit\n"
      "\thelp\t\t\tPrint this menu\n");
}

auto chip8::debug_dasm(std::stringstream& cmd) -> void {
  auto begin = m_pc;
  auto end = 0x0000_w;

  if (not cmd.eof()) {
    cmd >> std::hex >> begin;
  }

  if (not cmd.eof()) {
    cmd >> std::hex >> end;
  }

  if (begin > end) {
    end = (begin + 0x0010_w);
  }

  begin &= 0xfffe;
  end &= 0xfffe;

  for (auto addr = begin; addr < end; addr += 2) {
    print_opcode(addr);
  }
}

auto chip8::sys(word addr) -> void {
  fmt::print(stderr, "SYS addr not implemented by this emulator\n");
}

auto chip8::invalid(word opcode) -> void {
  fmt::print(stderr, "Unsupported opcode {:04x}\n", opcode);
}

auto chip8::cls() -> void {
  for (auto& column : m_screen) {
    column.reset();
  }
}

auto chip8::ret() -> void { m_pc = m_stack.pop(); }

auto chip8::jp(word addr) -> void { m_pc = addr; };

auto chip8::call(word addr) -> void {
  m_stack.push(m_pc);
  m_pc = addr;
}
}  // namespace chip8
