#include "cpu.hpp"

auto chip8::read(word addr) -> byte {
  return memory[ addr & 0x0fff ];
}

auto chip8::write(word addr, byte data) -> void {
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

    if (is_T) {
      T--;
    }

    if (is_S) {
      S--;
    }

    if (T == 0x00) {
      is_T = false;
    }

    if (S == 0x00) {
      beep();
      is_S = false;
    }

    std::this_thread::sleep_until(begin + timer_rate);
  }
}

auto chip8::run() -> void {}

auto chip8::fetch() -> void {
  opcode = word( read( PC++ ) ) << 8;
  opcode = opcode | read( PC++ );
}

auto chip8::execute() -> void {}

auto chip8::init() -> void {}

auto chip8::reset() -> void {}

auto chip8::beep() -> void {}

