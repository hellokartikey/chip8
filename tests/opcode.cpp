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

TEST(Opcode, SE) {
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::V0, 0x64), 0x3064);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::V1, 0x12), 0x3112);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::V4, 0xde), 0x34de);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::V6, 0xad), 0x36ad);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::V7, 0xff), 0x37ff);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::VA, 0x00), 0x3a00);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::VB, 0x69), 0x3b69);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::VD, 0xbe), 0x3dbe);
  EXPECT_EQ(chip8::opcode::SE(chip8::regs::VF, 0xef), 0x3fef);
}

TEST(Opcode, SNE) {
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::V0, 0x64), 0x4064);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::V1, 0x12), 0x4112);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::V4, 0xde), 0x44de);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::V6, 0xad), 0x46ad);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::V7, 0xff), 0x47ff);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::VA, 0x00), 0x4a00);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::VB, 0x69), 0x4b69);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::VD, 0xbe), 0x4dbe);
  EXPECT_EQ(chip8::opcode::SNE(chip8::regs::VF, 0xef), 0x4fef);
}
