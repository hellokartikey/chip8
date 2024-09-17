#include "cli.h"

#include <fmt/base.h>
#include <fmt/ranges.h>
#include <fmt/std.h>

#include <algorithm>

auto is_arg_present(const args_type& args, std::string_view arg) -> bool {
  return std::ranges::contains(args, arg);
}

auto print_help(const args_type& args) -> void {
  fmt::print(
      "Usage: {} [OPTIONS]\n"
      "\n"
      "Options:\n"
      "  -d, --debug        Interactive debug shell\n"
      "  -r, --rom <ROM>    Load rom file\n"
      "  -h, --help         Print help\n"
      "  -v, --version      Print version\n",
      args[0]);
}
