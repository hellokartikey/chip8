#include <fmt/core.h>

#include "chip8.h"
#include "cli.h"
#include "screen.h"

namespace op = chip8::opcode;
using chip8::regs;

using namespace std::literals;

auto main(int argc, char* argv[]) -> int {
  auto args = cli_args(argc, argv);

  fmt::print("chip8 emulator by hellokartikey!\n");

  auto interpreter = chip8::chip8{chip8::with_screen};

  if (args.is_present("--debug")) {
    interpreter.debug_shell();
  }

  if (args.count() == 2) {
    interpreter.load_rom(args[1]);
    interpreter.exec_all();
  } else {
    fmt::print(stderr, "ROM not provided...\n");
  }

  return 0;
}
