#include "cli.h"

cli_args::cli_args(int argc, char* argv[]) : m_args(argv, argv + argc) {}

auto cli_args::is_present(std::string_view key) -> bool {
  for (const auto& arg : args()) {
    if (arg == key) {
      return true;
    }
  }

  return false;
}

auto cli_args::args() const -> const args_t& { return m_args; }
