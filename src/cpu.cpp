#include "cpu.hpp"

auto chip8::read(word addr) -> byte {
  return memory[ addr & 0x0fff ];
}

auto chip8::write(word addr, word data) -> void {
  memory[ addr & 0x0fff ] = data;
}

auto chip8::exec() -> void {
  while (true) {
    auto begin = std::chrono::system_clock::now();

    /** Executing single instruction */
    fetch();
    execute();

    std::this_thread::sleep_until(begin + clock_rate);
  }
}

auto chip8::time() -> void {
  while (true) {
    auto begin = std::chrono::system_clock::now();

    if (is_timer_engaged[T]) {
      registers8[T]--;
    }

    if (is_timer_engaged[S]) {
      registers8[S]--;
    }

    if (registers8[T] == 0x00) {
      is_timer_engaged[T] = false;
    }

    if (registers8[S] == 0x00) {
      beep();
      is_timer_engaged[S] = false;
    }

    std::this_thread::sleep_until(begin + timer_rate);
  }
}

auto chip8::run() -> void {}

auto chip8::fetch() -> void {
  opcode = word( read( registers16[PC]++ ) ) << 8;
  opcode = opcode | read( registers16[PC]++ );
}

auto chip8::execute() -> void {}

auto chip8::init() -> void {}

auto chip8::reset() -> void {}

auto chip8::beep() -> void {}

