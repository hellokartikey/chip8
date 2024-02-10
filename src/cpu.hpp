#ifndef CHIP8_CPU_HPP
#define CHIP8_CPU_HPP

#include <array>
#include <bitset>
#include <chrono>
#include <stack>
#include <thread>

#include "common.hpp"

class chip8 {
  private:
    enum {V0, V1, V2, V3, V4, V5, V6, V8, V9, VA, VB, VC, VD, VE, VF, S, T};
    enum {I, PC};

 public:
  chip8() = default;
  ~chip8() = default;

  auto read(word addr) -> byte;
  auto write(word addr, word data) -> void;

  auto exec() -> void;
  auto time() -> void;

  auto run() -> void;

  auto fetch() -> void;
  auto execute() -> void;

  auto init() -> void;
  auto reset() -> void;

  auto beep() -> void;

  auto set_clock_rate_mhz(std::chrono::nanoseconds ns) -> void;

 private:
  std::array<byte, 0x1000> memory;
  std::array<byte, 0x12> registers8;
  std::array<word, 2> registers16;
  std::array<bool, 2> is_timer_engaged;

  std::bitset<16> keypad;

  std::stack<word> stack;

  std::chrono::nanoseconds clock_rate;
  std::chrono::milliseconds timer_rate;

  std::array<std::bitset<64>, 32> screen;

  word opcode;
};

#endif

