#include <gtest/gtest.h>

#include "fixture.h"

using RegisterAPI = EmulatorFixture;

TEST_F(RegisterAPI, DefaultValue) {
  EXPECT_EQ(emulator.get(chip8::regs::V0), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V1), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V2), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V3), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V4), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V5), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V6), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V7), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V8), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::V9), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::VA), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::VB), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::VC), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::VD), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::VE), 0x00);
  EXPECT_EQ(emulator.get(chip8::regs::VF), 0x00);
}

TEST_F(RegisterAPI, GetMethod) {
  emulator.get(chip8::regs::V0) = 0x01;
  emulator.get(chip8::regs::V1) = 0x12;
  emulator.get(chip8::regs::V2) = 0x23;
  emulator.get(chip8::regs::V3) = 0x34;
  emulator.get(chip8::regs::V4) = 0x45;
  emulator.get(chip8::regs::V5) = 0x56;
  emulator.get(chip8::regs::V6) = 0x67;
  emulator.get(chip8::regs::V7) = 0x78;
  emulator.get(chip8::regs::V8) = 0x89;
  emulator.get(chip8::regs::V9) = 0x9a;
  emulator.get(chip8::regs::VA) = 0xab;
  emulator.get(chip8::regs::VB) = 0xbc;
  emulator.get(chip8::regs::VC) = 0xcd;
  emulator.get(chip8::regs::VD) = 0xde;
  emulator.get(chip8::regs::VE) = 0xef;
  emulator.get(chip8::regs::VF) = 0xf0;

  EXPECT_EQ(emulator.get(chip8::regs::V0), 0x01);
  EXPECT_EQ(emulator.get(chip8::regs::V1), 0x12);
  EXPECT_EQ(emulator.get(chip8::regs::V2), 0x23);
  EXPECT_EQ(emulator.get(chip8::regs::V3), 0x34);
  EXPECT_EQ(emulator.get(chip8::regs::V4), 0x45);
  EXPECT_EQ(emulator.get(chip8::regs::V5), 0x56);
  EXPECT_EQ(emulator.get(chip8::regs::V6), 0x67);
  EXPECT_EQ(emulator.get(chip8::regs::V7), 0x78);
  EXPECT_EQ(emulator.get(chip8::regs::V8), 0x89);
  EXPECT_EQ(emulator.get(chip8::regs::V9), 0x9a);
  EXPECT_EQ(emulator.get(chip8::regs::VA), 0xab);
  EXPECT_EQ(emulator.get(chip8::regs::VB), 0xbc);
  EXPECT_EQ(emulator.get(chip8::regs::VC), 0xcd);
  EXPECT_EQ(emulator.get(chip8::regs::VD), 0xde);
  EXPECT_EQ(emulator.get(chip8::regs::VE), 0xef);
  EXPECT_EQ(emulator.get(chip8::regs::VF), 0xf0);
}
