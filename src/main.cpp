#include <fmt/core.h>

#include "chip8.h"
#include "instructions.h"

namespace op = chip8::opcode;
using chip8::regs;

auto main() -> int {
  fmt::print("chip8 emulator by hellokartikey!\n");

  auto interpreter = chip8::chip8{};

  interpreter.load_program({op::ADD(regs::V1, regs::V2)});

  interpreter.debug_shell();

  return 0;
}
