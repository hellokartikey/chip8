#ifndef HK_CHIP8_CLI_H
#define HK_CHIP8_CLI_H

#include <string_view>
#include <vector>

class cli_args {
 public:
  using args_t = std::vector<std::string_view>;

  cli_args(int argc, char* argv[]);

  auto is_present(std::string_view arg) const -> bool;

  auto args() const -> const args_t&;
  auto count() const -> std::size_t;

  auto operator[](std::size_t idx) const -> std::string_view;

  auto is_debug() const -> bool;
  auto is_valid() const -> bool;

  auto has_rom() const -> bool;
  auto rom() const -> std::string_view;

  auto help() const -> void;

 private:
  args_t m_args;
};

#endif
