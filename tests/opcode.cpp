#include <gtest/gtest.h>

#include "instructions.h"

TEST(Opcode, CLS) { EXPECT_EQ(chip8::opcode::CLS(), 0x00e0); }

TEST(Opcode, RET) { EXPECT_EQ(chip8::opcode::RET(), 0x00ee); }

TEST(Opcode, JP) {
  EXPECT_EQ(chip8::opcode::JP(0x0def), 0x1def);
  EXPECT_EQ(chip8::opcode::JP(0x1234), 0x1234);
  EXPECT_EQ(chip8::opcode::JP(0xabcd), 0x1bcd);
}

TEST(Opcode, CALL) {
  EXPECT_EQ(chip8::opcode::CALL(0x0def), 0x2def);
  EXPECT_EQ(chip8::opcode::CALL(0x1234), 0x2234);
  EXPECT_EQ(chip8::opcode::CALL(0xabcd), 0x2bcd);
}
