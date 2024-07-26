#ifndef HK_CHIP8_COMMON_H
#define HK_CHIP8_COMMON_H

#include <array>
#include <cstdint>
#include <stack>

namespace chip8 {
using byte = std::uint8_t;
using word = std::uint16_t;

constexpr auto NUM_REGISTERS = 0x10z;
using registers = std::array<byte, NUM_REGISTERS>;
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
  VF = 0x0f
};

constexpr auto MEMORY_SIZE = 0x1000z;
using memory = std::array<byte, MEMORY_SIZE>;

constexpr auto STACK_SIZE = 0x10z;
class stack {
 public:
  [[nodiscard]] auto top() const -> word { return m_stack.at(m_index - 1); }

  [[nodiscard]] auto empty() const -> bool { return m_index == 0; }
  [[nodiscard]] auto size() const -> std::size_t { return m_index; }

  auto push(word value) -> void { m_stack.at(m_index++) = value; }
  auto pop() -> word { return m_stack.at(--m_index); }

 private:
  std::array<word, STACK_SIZE> m_stack{};
  std::size_t m_index{};
};
}  // namespace chip8

#endif