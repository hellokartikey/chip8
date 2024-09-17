#include <fmt/core.h>

#include "chip8.h"
#include "cli.h"
#include "instructions.h"

namespace op = chip8::opcode;
using chip8::regs;

using namespace std::literals;

auto main(int argc, char* argv[]) -> int {
  auto args = args_type(argv, argv + argc);

  fmt::print("chip8 emulator by hellokartikey!\n");

  auto interpreter = chip8::chip8{};

  if (is_arg_present(args, "-h") or is_arg_present(args, "--help")) {
    print_help(args);
    return 1;
  }

  if (is_arg_present(args, "-d") or is_arg_present(args, "--debug")) {
    interpreter.debug_shell();
  }

  return 0;
}
