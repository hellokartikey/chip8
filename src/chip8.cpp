#include "chip8.h"

#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <utility>

#include "bit.h"
#include "common.h"
#include "parser.h"
#include "screen.h"

namespace chip8 {
chip8::chip8() {
  auto addr = 0x0050_w;
  for (const auto& digit : letters) {
    for (const auto& data : digit) {
      write(addr++, data);
    }
  }
}

chip8::chip8(screen_tag_t /* unused */) : chip8() { m_screen.init_raylib(); }

auto chip8::get(regs reg) -> byte& {
  return m_registers.at(std::to_underlying(reg));
}

auto chip8::get(regs reg) const -> byte {
  return m_registers.at(std::to_underlying(reg));
}

auto chip8::get_random() -> byte { return m_r = randomness(random_device); }

auto chip8::dump_memory() -> memory& { return m_memory; }

auto chip8::print_memory(word begin, word end) const -> void {
  fmt::print(" hex  ");

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
  fmt::print("I : {:04x}\n", m_i);
  fmt::print("SP: {:02x}\n", m_stack.size());
  fmt::print("R : {:02x}\n", m_r);
}

auto chip8::parse_opcode(word opcode) const -> std::string {
  auto parsed = parsed_instruction{opcode};

  auto addr = parsed.get_addr();
  auto lo_byte = parsed.get_lo_byte();
  auto reg_x = reg_to_str(to_reg(parsed.get_nibble(2)));
  auto reg_y = reg_to_str(to_reg(parsed.get_nibble(1)));

  switch (parsed.get_nibble(3)) {
    case 0x0:
      switch (opcode) {
        case opcode::CLS():
          return fmt::format("CLS");
        case opcode::RET():
          return fmt::format("RET");
        default:
          return fmt::format("SYS {:03x}", addr);
      }
      break;
    case 0x1:
      return fmt::format("JP {:03x}", addr);
    case 0x2:
      return fmt::format("CALL {:03x}", addr);
    case 0x3:
      return fmt::format("SE {}, {:02x}", reg_x, lo_byte);
    case 0x4:
      return fmt::format("SNE {}, {:02x}", reg_x, lo_byte);
    case 0x5:
      return fmt::format("SE {}, {}", reg_x, reg_y);
    case 0x6:
      return fmt::format("LD {}, {:02x}", reg_x, lo_byte);
    case 0x7:
      return fmt::format("ADD {}, {:02x}", reg_x, lo_byte);
    case 0x8:
      switch (parsed.get_nibble(0)) {
        case 0x0:
          return fmt::format("LD {}, {}", reg_x, reg_y);
        case 0x1:
          return fmt::format("OR {}, {}", reg_x, reg_y);
        case 0x2:
          return fmt::format("AND {}, {}", reg_x, reg_y);
        case 0x3:
          return fmt::format("XOR {}, {}", reg_x, reg_y);
        case 0x4:
          return fmt::format("ADD {}, {}", reg_x, reg_y);
        case 0x5:
          return fmt::format("SUB {}, {}", reg_x, reg_y);
        case 0x6:
          return fmt::format("SHR {} (, {})", reg_x, reg_y);
        case 0x7:
          return fmt::format("SUBN {}, {}", reg_x, reg_y);
        case 0xe:
          return fmt::format("SHL {} (, {})", reg_x, reg_y);
        default:
          return invalid_opcode(opcode);
      }
      break;
    case 0x9:
      return fmt::format("SNE {}, {}", reg_x, reg_y);
    case 0xa:
      return fmt::format("LD I, {:03x}", addr);
    case 0xb:
      return fmt::format("JP V0, {:03x}", addr);
    case 0xc:
      return fmt::format("RND {}, {:02x}", reg_x, lo_byte);
    case 0xd:
      return fmt::format("DRW {}, {}, {}", reg_x, reg_y, parsed.get_nibble(0));
    case 0xf:
      switch (lo_byte) {
        case 0x07:
          return fmt::format("LD {}, DT", reg_x);
        case 0x55:
          return fmt::format("LD [I], Vx");
        case 0x65:
          return fmt::format("LD Vx, [I]");
        default:
          return invalid_opcode(opcode);
      }
    default:
      return invalid_opcode(opcode);
  }
};

auto chip8::invalid_opcode(word opcode) const -> std::string {
  return fmt::format("INVALID {:04x}", opcode);
}

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

auto chip8::is_invalid() const -> bool { return m_is_invalid_state; }

auto chip8::fetch() -> word {
  auto opcode = read16(m_pc);

  m_pc += 2;
  m_pc &= 0x0fff;

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

  auto opcode = parsed.get_opcode();
  auto addr = parsed.get_addr();
  auto lo_byte = parsed.get_lo_byte();
  auto reg_x = to_reg(parsed.get_nibble(2));
  auto reg_y = to_reg(parsed.get_nibble(1));

  switch (parsed.get_nibble(3)) {
    case 0x0:
      switch (opcode) {
        case 0x00e0:
          cls();
          break;
        case 0x00ee:
          ret();
          break;
        default:
          sys(addr);
          break;
      }
      break;
    case 0x1:
      jp(addr);
      break;
    case 0x2:
      call(addr);
      break;
    case 0x3:
      se(reg_x, lo_byte);
      break;
    case 0x4:
      sne(reg_x, lo_byte);
      break;
    case 0x5:
      se(reg_x, reg_y);
      break;
    case 0x6:
      ld(reg_x, lo_byte);
      break;
    case 0x7:
      add(reg_x, lo_byte);
      break;
    case 0x8:
      switch (parsed.get_nibble(0)) {
        case 0x0:
          ld(reg_x, reg_y);
          break;
        case 0x1:
          or_(reg_x, reg_y);
          break;
        case 0x2:
          and_(reg_x, reg_y);
          break;
        case 0x3:
          xor_(reg_x, reg_y);
          break;
        case 0x4:
          add(reg_x, reg_y);
          break;
        case 0x05:
          sub(reg_x, reg_y);
          break;
        case 0x6:
          shr(reg_x);
          break;
        case 0x7:
          subn(reg_x, reg_y);
          break;
        case 0xe:
          shl(reg_x);
          break;
        default:
          invalid(opcode);
          break;
      }
    case 0x9:
      sne(reg_x, reg_y);
      break;
    case 0xa:
      ld_i(addr);
      break;
    case 0xb:
      jp_v0(addr);
      break;
    case 0xc:
      rnd(reg_x, lo_byte);
      break;
    case 0xd:
      drw(reg_x, reg_y, parsed.get_nibble(0));
      break;
    case 0xf:
      switch (lo_byte) {
        case 0x07:
          ld_dt(reg_x);
          break;
        case 0x55:
          st_regs();
          break;
        case 0x65:
          ld_regs();
          break;
        default:
          invalid(opcode);
          break;
      }
      break;
    default:
      invalid(opcode);
      break;
  }

  m_screen.draw_screen();
}

auto chip8::exec_n(std::uint64_t count) -> void {
  for (; count > 0 and not is_invalid(); count--) {
    exec();
  }
}

auto chip8::exec_all() -> void {
  while (not is_invalid()) {
    exec();
  }

  debug_shell();
}

auto chip8::load_rom(const std::filesystem::path& file) -> void {
  if (not std::filesystem::is_regular_file(file)) {
    fmt::print(stderr, "Invalid rom file path\n");
    return;
  }

  std::ifstream rom{file, std::ios::binary | std::ios::ate};

  auto data = 0x00_b;

  auto end = rom.tellg();
  auto rom_data = std::vector<byte>(end);

  rom.seekg(std::ios::beg);
  rom.read(reinterpret_cast<char*>(rom_data.data()), end);

  std::ranges::copy(rom_data, std::next(m_memory.begin(), 0x200));
}

auto chip8::debug_shell() -> void {
  fmt::print("Interactive debug shell!\n");

  while (true) {
    if (std::cin.eof()) {
      break;
    }

    fmt::print("{:03x}> ", m_pc);

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
    } else if (sub_command == "display") {
      debug_scr();
    } else if (sub_command == "help") {
      debug_help(cmd);
    } else if (sub_command == "si") {
      debug_step(cmd);
    } else if (sub_command == "stk") {
      debug_stk();
    } else if (sub_command == "push") {
      debug_push(cmd);
    } else if (sub_command == "pop") {
      debug_pop();
    } else if (sub_command == "set") {
      debug_set_regs(cmd);
    } else if (sub_command == "rnd") {
      debug_random();
    } else if (sub_command == "screen") {
      debug_screen(cmd);
    } else if (sub_command == "clear") {
      m_screen.clear();
    } else if (sub_command == "full") {
      m_screen.full();
    } else if (sub_command == "pixel") {
      debug_pixel(cmd);
    } else if (sub_command == "rom") {
      debug_rom(cmd);
    } else {
      fmt::print(std::cerr, "Invalid command...\n");
    }

    m_screen.draw_screen();
  }

  fmt::print("exiting...\n");
}

auto chip8::debug_set_regs(std::stringstream& cmd) -> void {
  if (cmd.eof()) {
    fmt::print(std::cerr, "Invalid syntax...\n");
    return;
  }

  auto reg_str = std::string{};
  cmd >> reg_str;

  auto reg = str_to_reg(reg_str);

  if (cmd.eof()) {
    fmt::print(std::cerr, "Invalid syntax...\n");
    return;
  }

  auto addr = 0x0000_w;

  switch (reg) {
    case regs::INVALID:
      fmt::print(std::cerr, "Invalid register\n");
      return;
    case regs::PC:
      cmd >> std::hex >> addr;
      m_pc = address(addr);
      return;
    case regs::R:
      cmd >> std::hex >> addr;
      m_r = addr;
      return;
    case regs::I:
      cmd >> std::hex >> addr;
      m_i = address(addr);
      return;
    default:
      cmd >> std::hex >> addr;
      get(reg) = addr;
  }
}

auto chip8::debug_push(std::stringstream& cmd) -> void {
  auto addr = 0x0000_w;

  if (not cmd.eof()) {
    cmd >> std::hex >> addr;
  }

  m_stack.push(address(addr));
}

auto chip8::debug_pop() -> void { fmt::print("{:03x}\n", m_stack.pop()); }

auto chip8::debug_step(std::stringstream& cmd) -> void {
  std::uint64_t count = 1;

  if (not cmd.eof()) {
    cmd >> std::dec >> count;
  }

  exec_n(count);
}

auto chip8::debug_stk() -> void {
  if (m_stack.empty()) {
    fmt::print("|     |\n");
  }

  for (auto idx = m_stack.size(); idx > 0; idx--) {
    fmt::print("| {:03x} |\n", m_stack.array().at(idx - 1));
  }

  fmt::print("+-----+\n");
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
      "  regs                 Print all registers\n"
      "  set [reg] [value]    Set value of register\n"
      "  mem [begin] [end]    Print memory\n"
      "  dasm [begin] [end]   Disassemble instructions\n"
      "  si [count]           Execute instructions\n"
      "  stk                  Print the stack\n"
      "  push [addr]          Push an address to the stack\n"
      "  pop                  Pop an address from the stack\n"
      "  rnd                  Generate a random byte\n"
      "  display              Display screen state in terminal\n"
      "  screen [on|off]      Turn on raylib powered screen\n"
      "  clear                Clear all pixels on screen\n"
      "  full                 Fill all pixels on screen\n"
      "  pixel [x] [y]        Toggle pixel at (x, y)\n"
      "  rom [path]           Load rom into memory\n"
      "  exit                 Exit\n"
      "  help                 Print this menu\n");
}

auto chip8::debug_dasm(std::stringstream& cmd) -> void {
  auto begin = m_pc;

  if (begin >= 0x0004) {
    begin -= 0x0004;
  }

  auto end = 0x0000_w;

  if (not cmd.eof()) {
    cmd >> std::hex >> begin;
  }

  if (not cmd.eof()) {
    cmd >> std::hex >> end;
  }

  if (begin >= end) {
    end = (begin + 0x0010_w);
  }

  begin &= 0x0ffe;
  end &= 0x0ffe;

  for (auto addr = begin; addr < end; addr += 2) {
    print_opcode(addr);
  }
}

auto chip8::debug_scr() -> void {
  fmt::print(
      "+----------------------------------------------------------------+\n");

  for (const auto& row : m_screen) {
    fmt::print("|");

    for (auto col = 0; col < row.size(); col++) {
      if (row[col]) {
        fmt::print("#");
      } else {
        fmt::print(" ");
      }
    }

    fmt::print("|\n");
  }

  fmt::print(
      "+----------------------------------------------------------------+\n");
}

auto chip8::debug_random() -> void { fmt::print("{:02x}\n", get_random()); }

auto chip8::debug_screen(std::stringstream& cmd) -> void {
  if (cmd.eof()) {
    m_screen.init_raylib();
  }

  auto arg = std::string{};
  cmd >> arg;

  if (arg == "on") {
    m_screen.init_raylib();
  } else if (arg == "off") {
    m_screen.close_raylib();
  }
}

auto chip8::debug_pixel(std::stringstream& cmd) -> void {
  if (cmd.eof()) {
    fmt::print(stderr, "Invalid syntax");
  }

  auto idx_x = 0Z;
  auto idx_y = 0Z;

  cmd >> idx_x;
  cmd >> idx_y;

  if (idx_x < screen::WIDTH and idx_y < screen::HEIGHT) {
    m_screen[idx_x, idx_y] = ~m_screen[idx_x, idx_y];
  }
}

auto chip8::debug_rom(std::stringstream& cmd) -> void {
  if (cmd.eof()) {
    fmt::print(stderr, "Invalid syntax.\n");
    return;
  }

  std::filesystem::path file{};
  cmd >> file;
  load_rom(file);
}

auto chip8::sys(word addr) -> void {
  fmt::print(std::cerr, "SYS addr not implemented by this emulator\n");
}

auto chip8::invalid(word opcode) -> void {
  fmt::print(stderr, "Unsupported opcode {:04x}\n", opcode);
  m_is_invalid_state = true;
}

auto chip8::cls() -> void { m_screen.clear(); }

auto chip8::ret() -> void { m_pc = m_stack.pop(); }

auto chip8::jp(word addr) -> void { m_pc = address(addr); };

auto chip8::call(word addr) -> void {
  m_stack.push(m_pc);
  m_pc = addr;
}

auto chip8::se(regs reg, byte value) -> void {
  if (get(reg) == value) {
    m_pc += 2;
  }
}

auto chip8::se(regs reg1, regs reg2) -> void {
  if (get(reg1) == get(reg2)) {
    m_pc += 2;
  }
}

auto chip8::sne(regs reg, byte value) -> void {
  if (get(reg) != value) {
    m_pc += 2;
  }
}

auto chip8::ld(regs reg, byte value) -> void { get(reg) = value; }

auto chip8::add(regs reg, byte value) -> void { get(reg) += value; }

auto chip8::add(regs dst, regs src) -> void {
  auto res = get(dst) + get(src);
  get(regs::VF) = res > 255 ? 0x01 : 0x00;
  get(dst) = static_cast<byte>(res);
}

auto chip8::ld(regs dst, regs src) -> void { get(dst) = get(src); }

auto chip8::or_(regs dst, regs src) -> void { get(dst) |= get(src); }

auto chip8::and_(regs dst, regs src) -> void { get(dst) &= get(src); }

auto chip8::xor_(regs dst, regs src) -> void { get(dst) ^= get(src); }

auto chip8::sub(regs dst, regs src) -> void {
  if (not(get(dst) < get(src))) {
    get(regs::VF) = 0x01;
  } else {
    get(regs::VF) = 0x00;
  }

  get(dst) -= get(src);
}

auto chip8::shr(regs reg) -> void {
  get(regs::VF) = get(reg) & 0x01;
  get(reg) >>= 1;
}

auto chip8::subn(regs dst, regs src) -> void {
  if (not(get(src) < get(dst))) {
    get(regs::VF) = 0x01;
  } else {
    get(regs::VF) = 0x00;
  }

  get(dst) = get(src) - get(dst);
}

auto chip8::shl(regs reg) -> void {
  if ((get(reg) & 0x80) != 0x00) {
    // MSB is 1
    get(regs::VF) = 0x01;
  } else {
    // MSB is 0
    get(regs::VF) = 0x00;
  }

  get(reg) <<= 1;
}

auto chip8::sne(regs reg1, regs reg2) -> void {
  if (get(reg1) != get(reg2)) {
    m_pc += 2;
  }
}

auto chip8::ld_i(word addr) -> void { m_i = address(addr); }

auto chip8::jp_v0(word addr) -> void { m_pc = address(addr + get(regs::V0)); }

auto chip8::rnd(regs reg, byte value) -> void {
  get(reg) = get_random() & value;
}

auto chip8::drw(regs reg_x, regs reg_y, byte count) -> void {
  auto idx_x = get(reg_x);
  auto idx_y = get(reg_y);

  auto iter = m_screen.pixel_iter(idx_x, idx_y);
  auto addr = m_i;

  get(regs::VF) = 0x00;

  while (count-- != 0) {
    auto data = read(addr++);
    for (auto i = begin(data); i != end(data); i++) {
      auto old_value = bool{*iter};
      auto new_value = static_cast<bool>(*i ^ *iter);

      if (old_value and not new_value) {
        get(regs::VF) = 0x01;
      }

      *iter = new_value;
      iter++;
    }
  }
}

auto chip8::ld_dt(regs reg) -> void { get(reg) = m_dt; }

auto chip8::st_regs() -> void {
  auto addr = m_i;
  write(addr++, get(regs::V0));
  write(addr++, get(regs::V1));
  write(addr++, get(regs::V2));
  write(addr++, get(regs::V3));
  write(addr++, get(regs::V4));
  write(addr++, get(regs::V5));
  write(addr++, get(regs::V6));
  write(addr++, get(regs::V7));
  write(addr++, get(regs::V8));
  write(addr++, get(regs::V9));
  write(addr++, get(regs::VA));
  write(addr++, get(regs::VB));
  write(addr++, get(regs::VC));
  write(addr++, get(regs::VD));
  write(addr++, get(regs::VE));
  write(addr++, get(regs::VF));
}

auto chip8::ld_regs() -> void {
  auto addr = m_i;
  get(regs::V0) = read(addr++);
  get(regs::V1) = read(addr++);
  get(regs::V2) = read(addr++);
  get(regs::V3) = read(addr++);
  get(regs::V4) = read(addr++);
  get(regs::V5) = read(addr++);
  get(regs::V6) = read(addr++);
  get(regs::V7) = read(addr++);
  get(regs::V8) = read(addr++);
  get(regs::V9) = read(addr++);
  get(regs::VA) = read(addr++);
  get(regs::VB) = read(addr++);
  get(regs::VC) = read(addr++);
  get(regs::VD) = read(addr++);
  get(regs::VE) = read(addr++);
  get(regs::VF) = read(addr++);
}
}  // namespace chip8
