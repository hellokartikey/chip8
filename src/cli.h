#ifndef HK_CHIP8_CLI_H
#define HK_CHIP8_CLI_H

#include <string_view>
#include <vector>

using args_type = std::vector<std::string_view>;

auto is_arg_present(const args_type& args, std::string_view arg) -> bool;

auto print_help(const args_type& args) -> void;

#endif
