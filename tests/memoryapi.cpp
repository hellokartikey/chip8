#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>

#include "fixture.h"

using MemoryAPI = EmulatorFixture;

TEST_F(MemoryAPI, DefaultInitialization) {
  auto result = std::ranges::all_of(
      emulator.dump_memory() | std::views::drop(0x1ff),  // Drop the fonts
      [](auto value) { return value == 0x00; });
  EXPECT_EQ(result, true);
}

TEST_F(MemoryAPI, ReadWriteByte) {
  emulator.write(0x0123, 0xab);

  EXPECT_EQ(emulator.read(0x0123), 0xab);
}

TEST_F(MemoryAPI, ReadWriteWord) {
  emulator.write16(0x0123, 0xabcd);

  EXPECT_EQ(emulator.read16(0x0123), 0xabcd);
}
