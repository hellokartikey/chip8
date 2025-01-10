#ifndef HK_CHIP8_CLI_H
#define HK_CHIP8_CLI_H

#include <string_view>
#include <vector>

class cli_args {
 public:
  using args_t = std::vector<std::string_view>;

  cli_args(int argc, char* argv[]);

  auto is_present(std::string_view arg) -> bool;

  auto args() const -> const args_t&;

 private:
  args_t m_args;
};

#endif
