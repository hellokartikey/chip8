#include "cli.h"

#include <fmt/base.h>

#include <algorithm>
#include <cstddef>
#include <string_view>

using namespace std::literals;

cli_args::cli_args(int argc, char** argv) : m_args(argv, argv + argc) {}

auto cli_args::is_present(std::string_view key) const -> bool {
  return std::ranges::any_of(m_args,
                             [&](const auto& item) { return item == key; });
}

auto cli_args::args() const -> const args_t& { return m_args; }

auto cli_args::count() const -> std::size_t { return m_args.size(); }

auto cli_args::operator[](std::size_t idx) const -> std::string_view {
  return m_args[idx];
}

auto cli_args::is_debug() const -> bool { return is_present("--debug"sv); }

auto cli_args::is_valid() const -> bool { return is_debug() or has_rom(); }

auto cli_args::help() const -> void {
  fmt::print(stderr, "Usage:\n\t{} [--debug] <ROM>\n", (*this)[0]);
}

auto cli_args::has_rom() const -> bool { return count() >= 2; }

auto cli_args::rom() const -> std::string_view {
  // TODO - Make rom arg position independent
  if (has_rom()) {
    return (*this)[1];
  }

  return ""sv;
}
