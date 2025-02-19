#ifndef HK_CHIP8_TIMER_H
#define HK_CHIP8_TIMER_H

#include <chrono>
#include <concepts>
#include <functional>

#include "common.h"

namespace chip8 {
using namespace std::literals;

class timer {
  static constexpr auto DELAY = 16ms;

 public:
  template <std::invocable Callback>
  timer(Callback callback)
      : m_callback(callback), m_last_tick(std::chrono::steady_clock::now()) {}

  auto tick() -> void {
    if (auto now = std::chrono::steady_clock::now();
        (now - m_last_tick) >= DELAY) {
      m_last_tick = now;
      m_callback();
    }
  }

 private:
  std::chrono::steady_clock::time_point m_last_tick;
  std::function<void(void)> m_callback;
};
}  // namespace chip8

#endif
