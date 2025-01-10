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

auto cli_args::count() const -> std::size_t { return m_args.size(); }

auto cli_args::operator[](std::size_t idx) const -> std::string_view {
  return m_args[idx];
}
