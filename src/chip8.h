#ifndef HK_CHIP8_CHIP8_H
#define HK_CHIP8_CHIP8_H

#include <filesystem>
#include <random>

#include "common.h"
#include "instructions.h"
#include "keyboard.h"
#include "screen.h"
#include "stack.h"

namespace chip8 {
class chip8 {
 public:
  explicit chip8();
  explicit chip8(screen_tag_t /* unused */);
  ~chip8();

  explicit chip8(const chip8&) = delete;
  chip8(chip8&&) = delete;

  auto operator=(const chip8&) -> chip8& = delete;
  auto operator=(chip8&&) -> chip8& = delete;

  // Registers API
  auto get(regs reg) -> byte&;
  [[nodiscard]] auto get(regs reg) const -> byte;

  [[nodiscard]] auto get_random() -> byte;

  // Memory API
  auto dump_memory() -> memory&;

  [[nodiscard]] auto read(word addr) const -> byte;
  auto write(word addr, byte data) -> void;

  [[nodiscard]] auto read16(word addr) const -> word;
  auto write16(word addr, word data) -> void;

  [[nodiscard]] auto is_invalid() const -> bool;

 private:
  auto fetch() -> word;

  auto init_raylib() -> void;
  auto close_raylib() -> void;
  [[nodiscard]] auto is_raylib() const -> bool;

 public:
  // Program API
  [[nodiscard]] auto start_addr() const -> word;

  auto load_program(opcode::instructions program) -> void;

  // Execute a single instruction
  auto exec() -> void;

  // Execute count instructions
  auto exec_n(std::uint64_t count = 1) -> void;

  // Execute continously
  auto exec_all() -> void;

  // Rom file API
  auto load_rom(const std::filesystem::path& file) -> void;

 private:
  auto sys(word addr) -> void;
  auto cls() -> void;
  auto ret() -> void;
  auto jp(word addr) -> void;
  auto call(word addr) -> void;
  auto se(regs reg, byte value) -> void;
  auto se(regs reg1, regs reg2) -> void;
  auto sne(regs reg, byte value) -> void;
  auto ld(regs reg, byte value) -> void;
  auto add(regs reg, byte value) -> void;
  auto add(regs dst, regs src) -> void;
  auto ld(regs dst, regs src) -> void;
  auto or_(regs dst, regs src) -> void;
  auto and_(regs dst, regs src) -> void;
  auto xor_(regs dst, regs src) -> void;
  auto sub(regs dst, regs src) -> void;
  auto shr(regs reg) -> void;
  auto subn(regs dst, regs src) -> void;
  auto shl(regs reg) -> void;
  auto sne(regs reg1, regs reg2) -> void;
  auto ld_i(word addr) -> void;
  auto jp_v0(word addr) -> void;
  auto rnd(regs reg, byte value) -> void;
  auto drw(regs reg_x, regs reg_y, byte count) -> void;
  auto ld_dt(regs reg) -> void;
  auto bcd(regs reg) -> void;
  auto st_regs() -> void;
  auto ld_regs() -> void;

  auto invalid(word opcode) -> void;

 public:
  auto debug_shell() -> void;

 private:
  auto debug_help(std::stringstream& cmd) -> void;
  auto debug_dasm(std::stringstream& cmd) -> void;
  auto debug_mem(std::stringstream& cmd) -> void;
  auto debug_scr() -> void;
  auto debug_step(std::stringstream& cmd) -> void;
  auto debug_stk() -> void;
  auto debug_push(std::stringstream& cmd) -> void;
  auto debug_pop() -> void;
  auto debug_set_regs(std::stringstream& cmd) -> void;
  auto debug_random() -> void;
  auto debug_screen(std::stringstream& cmd) -> void;
  auto debug_pixel(std::stringstream& cmd) -> void;
  auto debug_rom(std::stringstream& cmd) -> void;

  auto print_memory(word begin = 0x0000_w, word end = 0x1000_w) const -> void;
  auto print_registers() const -> void;

  [[nodiscard]] auto parse_opcode(word opcode) const -> std::string;
  [[nodiscard]] auto invalid_opcode(word opcode) const -> std::string;
  auto print_opcode(word addr) const -> void;

  registers m_registers{};
  word m_i{};
  byte m_r{};

  keyboard m_keyboard;

  byte m_dt{};
  byte m_st{};

  bool m_is_invalid_state{false};

  word m_start_addr{0x0200_w};
  word m_pc{m_start_addr};

  stack m_stack;
  memory m_memory{};

  screen m_screen;

  bool m_raylib;

  std::random_device random_device;
  std::uniform_int_distribution<byte> randomness;
};
}  // namespace chip8

#endif
