#ifndef HK_CHIP8_SCREEN_H
#define HK_CHIP8_SCREEN_H

#include "common.h"

namespace chip8 {
class screen {
 public:
  static constexpr auto WIDTH = 64Z;
  static constexpr auto HEIGHT = 32Z;

  static constexpr auto PIXEL = 10;

  using row_type = std::bitset<WIDTH>;
  using inner_type = std::array<row_type, HEIGHT>;
  using iterator = inner_type::iterator;
  using reference = row_type::reference;

  explicit screen() = default;
  explicit screen(screen_tag_t /* unused */);
  ~screen();

  screen(const screen&) = default;
  screen(screen&&) = default;

  auto operator=(const screen&) -> screen& = default;
  auto operator=(screen&&) -> screen& = default;

  auto clear() -> void;
  auto full() -> void;

  auto draw_screen() const -> void;

  [[nodiscard]] auto is_init_raylib() const -> bool;
  auto init_raylib() -> void;
  auto close_raylib() -> void;

  // Index using (x, y)
  auto operator[](std::size_t idx_x, std::size_t idx_y) const -> bool;
  auto operator[](std::size_t idx_x, std::size_t idx_y) -> reference;

  auto begin() -> iterator;
  auto end() -> iterator;

 private:
  inner_type m_screen;
  bool m_is_init_raylib{false};
};
}  // namespace chip8

#endif
