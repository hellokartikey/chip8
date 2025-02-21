#ifndef HK_CHIP8_CLI_H
#define HK_CHIP8_CLI_H

#include <string_view>
#include <vector>

// TODO - Use a proper library for cli args
class cli_args {
 public:
  using args_t = std::vector<std::string_view>;

  cli_args(int argc, char** argv);

  [[nodiscard]] auto is_present(std::string_view key) const -> bool;

  [[nodiscard]] auto args() const -> const args_t&;
  [[nodiscard]] auto count() const -> std::size_t;

  auto operator[](std::size_t idx) const -> std::string_view;

  [[nodiscard]] auto is_debug() const -> bool;
  [[nodiscard]] auto is_valid() const -> bool;

  [[nodiscard]] auto has_rom() const -> bool;
  [[nodiscard]] auto rom() const -> std::string_view;

  auto help() const -> void;

 private:
  args_t m_args;
};

#endif
