#include <fmt/base.h>

#include "chip8.h"
#include "cli.h"
#include "common.h"

auto main(int argc, char* argv[]) -> int {
  auto args = cli_args(argc, argv);

  fmt::print("chip8 emulator by hellokartikey!\n");

  if (not args.is_valid()) {
    fmt::print(stderr, "Invalid usage.\n");
    args.help();
    return 2;
  }

  auto interpreter = chip8::chip8{chip8::with_screen};

  if (args.has_rom()) {
    interpreter.load_rom(args.rom());
  }

  if (args.is_debug()) {
    interpreter.debug_shell();
  } else {
    interpreter.exec_all();
  }

  return 0;
}
