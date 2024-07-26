#ifndef HK_CHIP8_CHIP8_H
#define HK_CHIP8_CHIP8_H

#include "common.h"

namespace chip8 {
class chip8 {
 public:
  // Registers API
  auto get(regs reg) -> byte&;

  // Memory API
  [[nodiscard]] auto read(word addr) const -> byte;
  auto write(word addr, byte data) -> void;

  [[nodiscard]] auto read16(word addr) const -> word;
  auto write16(word addr, word data) -> void;

  auto fetch() -> word;

 private:
  registers m_registers{};
  stack m_stack;
  memory m_memory{};
  word m_pc{};
};
}  // namespace chip8

#endif
