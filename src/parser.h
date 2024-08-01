#ifndef HK_CHIP8_PARSER_H
#define HK_CHIP8_PARSER_H

#include "common.h"

namespace chip8 {
class parsed_instruction {
 public:
  explicit parsed_instruction(word opcode);

  [[nodiscard]] auto get_byte(std::size_t index) const -> byte;

  [[nodiscard]] auto get_lo_byte() const -> byte;
  [[nodiscard]] auto get_hi_byte() const -> byte;

  [[nodiscard]] auto get_nibble(std::size_t index) const -> byte;
  [[nodiscard]] auto get_addr() const -> word;

  [[nodiscard]] auto get_opcode() const -> word;

 private:
  word m_opcode;
};
}  // namespace chip8

#endif
