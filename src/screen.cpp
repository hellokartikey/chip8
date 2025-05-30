#include "screen.h"

#include <raylib.h>

#include <cstddef>

#include "common.h"

namespace chip8 {
auto screen::clear() -> void {
  for (auto& row : m_screen) {
    row.reset();
  }
}

auto screen::full() -> void {
  for (auto& row : m_screen) {
    row.set();
  }
}

auto screen::draw_screen() const -> void {
  int pos_x = 0;
  int pos_y = 0;

  BeginDrawing();

  ClearBackground(BG_COLOR);

  for (const auto& row : m_screen) {
    pos_x = 0;

    for (auto col = 0; col < row.size(); col++) {
      if (row[col]) {
        DrawRectangle(pos_x, pos_y, PIXEL, PIXEL, FG_COLOR);
      }
      pos_x += PIXEL;
    }
    pos_y += PIXEL;
  }

  EndDrawing();
}

auto screen::operator[](std::size_t idx_x, std::size_t idx_y) const -> bool {
  return m_screen.at(idx_y).test(idx_x);
}

auto screen::operator[](std::size_t idx_x, std::size_t idx_y) -> reference {
  return m_screen.at(idx_y)[idx_x];
}

auto screen::begin() -> iterator { return m_screen.begin(); }

auto screen::end() -> iterator { return m_screen.end(); }

auto screen::pixel_iter(std::size_t idx_x, std::size_t idx_y)
    -> pixel_iterator {
  return pixel_iterator(*this, idx_x, idx_y);
}

pixel_iterator::pixel_iterator(screen& p_screen, std::size_t pix_x,
                               std::size_t pix_y)
    : m_screen(&p_screen),
      m_idx_x(pix_x % WIDTH),
      m_idx_y(pix_y % HEIGHT),
      m_orig_x(m_idx_x),
      m_orig_y(m_idx_y) {}

auto pixel_iterator::operator++() -> pixel_iterator& {
  inc_idx();
  return *this;
}

auto pixel_iterator::operator++(int) -> pixel_iterator {
  auto old = *this;
  operator++();
  return old;
}

auto pixel_iterator::operator--() -> pixel_iterator& {
  dec_idx();
  return *this;
}

auto pixel_iterator::operator--(int) -> pixel_iterator {
  auto old = *this;
  operator--();
  return old;
}

auto pixel_iterator::operator*() -> screen::reference {
  auto& screen_v = *(this->m_screen);
  return screen_v[m_idx_x % WIDTH, m_idx_y % HEIGHT];
}

auto pixel_iterator::operator*() const -> bool {
  const auto& screen_v = *(this->m_screen);
  return screen_v[m_idx_x, m_idx_y];
}

auto pixel_iterator::inc_idx() -> void {
  m_idx_x++;
  if ((m_idx_x - m_orig_x) < 8) {
    return;
  }

  m_idx_x = m_orig_x;
  m_idx_y++;
}

auto pixel_iterator::dec_idx() -> void {
  if (m_idx_x == m_orig_x) {
    m_idx_y--;
    m_idx_x = m_orig_x + 8 - 1;
    return;
  }

  m_idx_x--;
}

auto pixel_iterator::origin() const -> position { return {m_orig_x, m_orig_y}; }

auto pixel_iterator::index() const -> position { return {m_idx_x, m_idx_y}; }
}  // namespace chip8
