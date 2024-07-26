#ifndef HK_CHIP8_CHIP8_H
#define HK_CHIP8_CHIP8_H

#include "common.h"
#include "instructions.h"

namespace chip8 {
class chip8 {
 public:
  // Registers API
  auto get(regs reg) -> byte&;

  // Memory API
  auto dump_memory() -> memory&;
  auto print_memory(word begin = 0x0000_w, word end = 0x1000_w) const -> void;

  [[nodiscard]] auto read(word addr) const -> byte;
  auto write(word addr, byte data) -> void;

  [[nodiscard]] auto read16(word addr) const -> word;
  auto write16(word addr, word data) -> void;

  auto fetch() -> word;

  // Program API
  [[nodiscard]] auto start_addr() const -> word;

  auto load_program(instructions program) -> void;

 private:
  registers m_registers{};

  word m_start_addr{0x0200_w};
  word m_pc{m_start_addr};

  stack m_stack;
  memory m_memory{};
};
}  // namespace chip8

#endif
