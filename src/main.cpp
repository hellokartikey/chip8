#include <fmt/core.h>

#include "chip8.h"

auto main() -> int {
  fmt::print("chip8 emulator by hellokartikey!\n");

  auto interpreter = chip8::chip8{};

  return 0;
}
