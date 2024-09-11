#include "screen.h"

#include <raylib.h>

#include "common.h"

namespace chip8 {
screen::screen(screen_tag_t /* unused */) { init_raylib(); }

screen::~screen() { close_raylib(); }

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
  if (not m_is_init_raylib) {
    return;
  }

  int pos_x = 0;
  int pos_y = 0;

  BeginDrawing();

  ClearBackground(BLACK);

  for (const auto& row : m_screen) {
    pos_x = 0;

    for (auto col = 0; col < row.size(); col++) {
      if (row[col]) {
        DrawRectangle(pos_x, pos_y, PIXEL, PIXEL, WHITE);
      }
      pos_x += PIXEL;
    }
    pos_y += PIXEL;
  }

  EndDrawing();
}

auto screen::is_init_raylib() const -> bool { return m_is_init_raylib; }

auto screen::init_raylib() -> void {
  if (not m_is_init_raylib) {
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(WIDTH * PIXEL, HEIGHT * PIXEL, "hellokartikey - CHIP8 Emulator");

    m_is_init_raylib = true;
  }
}

auto screen::close_raylib() -> void {
  if (m_is_init_raylib) {
    CloseWindow();
    m_is_init_raylib = false;
  }
}

auto screen::operator[](std::size_t idx_x, std::size_t idx_y) const -> bool {
  return m_screen.at(idx_y).test(idx_x);
}

auto screen::operator[](std::size_t idx_x, std::size_t idx_y) -> reference {
  return m_screen.at(idx_y)[idx_x];
}

auto screen::begin() -> iterator { return m_screen.begin(); }

auto screen::end() -> iterator { return m_screen.end(); }
}  // namespace chip8
