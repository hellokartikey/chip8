#include <gtest/gtest.h>

#include "instructions.h"

namespace op = chip8::opcode;
using chip8::regs;

TEST(Opcode, CLS) { EXPECT_EQ(op::CLS(), 0x00e0); }

TEST(Opcode, RET) { EXPECT_EQ(op::RET(), 0x00ee); }

TEST(Opcode, JP) {
  EXPECT_EQ(op::JP(0x0def), 0x1def);
  EXPECT_EQ(op::JP(0x1234), 0x1234);
  EXPECT_EQ(op::JP(0xabcd), 0x1bcd);
}

TEST(Opcode, CALL) {
  EXPECT_EQ(op::CALL(0x0def), 0x2def);
  EXPECT_EQ(op::CALL(0x1234), 0x2234);
  EXPECT_EQ(op::CALL(0xabcd), 0x2bcd);
}

TEST(Opcode, SEbyte) {
  EXPECT_EQ(op::SE(regs::V0, 0x64), 0x3064);
  EXPECT_EQ(op::SE(regs::V1, 0x12), 0x3112);
  EXPECT_EQ(op::SE(regs::V4, 0xde), 0x34de);
  EXPECT_EQ(op::SE(regs::V6, 0xad), 0x36ad);
  EXPECT_EQ(op::SE(regs::V7, 0xff), 0x37ff);
  EXPECT_EQ(op::SE(regs::VA, 0x00), 0x3a00);
  EXPECT_EQ(op::SE(regs::VB, 0x69), 0x3b69);
  EXPECT_EQ(op::SE(regs::VD, 0xbe), 0x3dbe);
  EXPECT_EQ(op::SE(regs::VF, 0xef), 0x3fef);
}

TEST(Opcode, SNE) {
  EXPECT_EQ(op::SNE(regs::V0, 0x64), 0x4064);
  EXPECT_EQ(op::SNE(regs::V1, 0x12), 0x4112);
  EXPECT_EQ(op::SNE(regs::V4, 0xde), 0x44de);
  EXPECT_EQ(op::SNE(regs::V6, 0xad), 0x46ad);
  EXPECT_EQ(op::SNE(regs::V7, 0xff), 0x47ff);
  EXPECT_EQ(op::SNE(regs::VA, 0x00), 0x4a00);
  EXPECT_EQ(op::SNE(regs::VB, 0x69), 0x4b69);
  EXPECT_EQ(op::SNE(regs::VD, 0xbe), 0x4dbe);
  EXPECT_EQ(op::SNE(regs::VF, 0xef), 0x4fef);
}

TEST(Opcode, SEregs) {
  EXPECT_EQ(op::SE(regs::V0, regs::V0), 0x5000);
  EXPECT_EQ(op::SE(regs::VA, regs::VF), 0x5af0);
  EXPECT_EQ(op::SE(regs::VB, regs::VC), 0x5bc0);
  EXPECT_EQ(op::SE(regs::V6, regs::VA), 0x56a0);
  EXPECT_EQ(op::SE(regs::V7, regs::V4), 0x5740);
  EXPECT_EQ(op::SE(regs::V3, regs::V2), 0x5320);
  EXPECT_EQ(op::SE(regs::V5, regs::V9), 0x5590);
  EXPECT_EQ(op::SE(regs::VD, regs::V0), 0x5d00);
  EXPECT_EQ(op::SE(regs::V0, regs::V1), 0x5010);
  EXPECT_EQ(op::SE(regs::V7, regs::V6), 0x5760);
  EXPECT_EQ(op::SE(regs::V2, regs::V8), 0x5280);
}

TEST(Opcode, LDbyte) {
  EXPECT_EQ(op::LD(regs::V0, 0x50), 0x6050);
  EXPECT_EQ(op::LD(regs::V1, 0x51), 0x6151);
  EXPECT_EQ(op::LD(regs::V2, 0x52), 0x6252);
  EXPECT_EQ(op::LD(regs::V3, 0x53), 0x6353);
  EXPECT_EQ(op::LD(regs::V4, 0x54), 0x6454);
  EXPECT_EQ(op::LD(regs::V5, 0x55), 0x6555);
  EXPECT_EQ(op::LD(regs::V6, 0x56), 0x6656);
  EXPECT_EQ(op::LD(regs::V7, 0x57), 0x6757);
  EXPECT_EQ(op::LD(regs::V8, 0x58), 0x6858);
  EXPECT_EQ(op::LD(regs::V9, 0x59), 0x6959);
  EXPECT_EQ(op::LD(regs::VA, 0x5a), 0x6a5a);
  EXPECT_EQ(op::LD(regs::VB, 0x5b), 0x6b5b);
  EXPECT_EQ(op::LD(regs::VC, 0x5c), 0x6c5c);
  EXPECT_EQ(op::LD(regs::VD, 0x5d), 0x6d5d);
  EXPECT_EQ(op::LD(regs::VE, 0x5e), 0x6e5e);
  EXPECT_EQ(op::LD(regs::VF, 0x5f), 0x6f5f);
}
