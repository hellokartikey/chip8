#ifndef HK_CHIP8_STACK_H
#define HK_CHIP8_STACK_H

#include <array>

#include "common.h"

namespace chip8 {
class stack {
  static constexpr auto STACK_SIZE = 0x10z;
  using arr = std::array<word, STACK_SIZE>;

 public:
  [[nodiscard]] auto top() const -> word {
    return m_index != 0 ? m_stack.at(m_index - 1) : 0x0000_w;
  }

  [[nodiscard]] auto empty() const -> bool { return m_index == 0; }

  [[nodiscard]] auto full() const -> bool { return m_index == STACK_SIZE; }

  [[nodiscard]] constexpr auto capacity() const -> std::size_t {
    return STACK_SIZE;
  }

  [[nodiscard]] auto size() const -> std::size_t { return m_index; }

  auto push(word value) -> void {
    if (m_index < STACK_SIZE) {
      m_stack.at(m_index++) = value;
    }
  }

  auto pop() -> word { return m_index != 0 ? m_stack.at(--m_index) : 0x0000_w; }

  [[nodiscard]] auto array() const -> arr { return m_stack; }

 private:
  arr m_stack{};
  std::size_t m_index{};
};
}  // namespace chip8

#endif
