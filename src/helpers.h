#ifndef HK_CHIP8_HELPERS_H
#define HK_CHIP8_HELPERS_H

#include <magic_enum/magic_enum.hpp>
#include <string>
#include <string_view>
#include <type_traits>

template <typename To, typename From>
constexpr auto as(const From& from) -> To {
  if constexpr (std::is_enum_v<To>) {
    // String to Enum
    return magic_enum::enum_cast<To>(from).value();
  } else if constexpr (std::is_enum_v<From>) {
    // Enum to String
    if constexpr (std::is_same_v<To, std::string>) {
      return as<std::string>(as<std::string_view>(from));
    } else if constexpr (std::is_same_v<To, std::string_view>) {
      return magic_enum::enum_name(from);
    } else {
      return static_cast<To>(from);
    }
  } else {
    return static_cast<To>(from);
  }
}

#endif
