#ifndef HK_CHIP8_HELPERS_H
#define HK_CHIP8_HELPERS_H

#include <magic_enum/magic_enum.hpp>
#include <string>
#include <string_view>
#include <type_traits>

// Enum to String
template <typename To, typename From>
  requires std::is_enum_v<From> && std::is_same_v<To, std::string_view>
constexpr auto as(const From& reg) -> To {
  return magic_enum::enum_name(reg);
}

template <typename To, typename From>
  requires std::is_enum_v<From> && std::is_same_v<To, std::string>
constexpr auto as(const From& reg) -> To {
  return static_cast<std::string>(as<std::string_view>(reg));
}

// String to Enum
template <typename To, typename From>
  requires std::is_enum_v<To> && std::is_same_v<From, std::string>
constexpr auto as(const From& str) -> To {
  return magic_enum::enum_cast<To>(str).value();
}

template <typename To, typename From>
auto as(const From& from) {
  return static_cast<To>(from);
}

#endif
