#include <fmt/base.h>

#include <cxxopts.hpp>
#include <filesystem>

#include "chip8.h"
#include "common.h"

auto main(int argc, char* argv[]) -> int {
  auto args = cxxopts::Options("chip8");
  args.allow_unrecognised_options();

  // clang-format off
  args.add_options()
    ("d,debug", "Enable debugging")
    ("h,help", "Display help")
    ("r,rom", "Load ROM file", cxxopts::value<std::filesystem::path>())
  ;
  // clang-format on

  auto options = args.parse(argc, argv);

  fmt::println("chip8 emulator by hellokartikey!");

  if (options.count("help") != 0) {
    fmt::println(stderr, "{}", args.help());
    return 1;
  }

  auto interpreter = chip8::chip8{chip8::with_screen};

  if (options.count("rom") != 0) {
    interpreter.load_rom(options["rom"].as<std::filesystem::path>());
  }

  if (options.count("debug") != 0) {
    interpreter.debug_shell();
  } else {
    interpreter.exec_all();
  }

  return 0;
}
