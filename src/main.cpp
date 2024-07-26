#include <fmt/core.h>

#include "chip8.h"

auto main() -> int {
  fmt::print("chip8 emulator by hellokartikey!\n");

  auto interpreter = chip8::chip8{};

  interpreter.write(0x001b, 0x64);

  interpreter.print_memory(0x0008, 0x0045);

  return 0;
}
