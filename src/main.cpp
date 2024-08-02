#include <fmt/core.h>

#include "chip8.h"
#include "instructions.h"

namespace op = chip8::opcode;

auto main() -> int {
  fmt::print("chip8 emulator by hellokartikey!\n");

  auto interpreter = chip8::chip8{};

  interpreter.load_program({op::CLS(), op::JP(0x300), op::NOP(), op::RET()});

  interpreter.debug_shell();

  return 0;
}
