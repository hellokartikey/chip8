#ifndef HK_CHIP8_CHIP8_H
#define HK_CHIP8_CHIP8_H

#include "common.h"
#include "instructions.h"
#include "stack.h"

namespace chip8 {
class chip8 {
 public:
  // Registers API
  auto get(regs reg) -> byte&;
  [[nodiscard]] auto get(regs reg) const -> byte;

  // Memory API
  auto dump_memory() -> memory&;

  [[nodiscard]] auto read(word addr) const -> byte;
  auto write(word addr, byte data) -> void;

  [[nodiscard]] auto read16(word addr) const -> word;
  auto write16(word addr, word data) -> void;

 private:
  auto fetch() -> word;

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

  auto print_memory(word begin = 0x0000_w, word end = 0x1000_w) const -> void;
  auto print_registers() const -> void;

  [[nodiscard]] auto parse_opcode(word opcode) const -> std::string;
  [[nodiscard]] auto invalid_opcode(word opcode) const -> std::string;
  auto print_opcode(word addr) const -> void;

  registers m_registers{};
  word m_i{};

  word m_start_addr{0x0200_w};
  word m_pc{m_start_addr};

  stack m_stack;
  memory m_memory{};

  screen m_screen{};
};
}  // namespace chip8

#endif
