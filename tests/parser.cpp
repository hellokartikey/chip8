#include "parser.h"

#include <gtest/gtest.h>

class OpcodeParser : public testing::Test {
 protected:
  chip8::parsed_instruction opcode{0xabcd};
};

TEST_F(OpcodeParser, GetBytesIndex) {
  EXPECT_EQ(opcode.get_byte(0), 0xcd);
  EXPECT_EQ(opcode.get_byte(1), 0xab);
}

TEST_F(OpcodeParser, GetHiLoBytes) {
  EXPECT_EQ(opcode.get_lo_byte(), 0xcd);
  EXPECT_EQ(opcode.get_hi_byte(), 0xab);
}

TEST_F(OpcodeParser, GetNibbleIndex) {
  EXPECT_EQ(opcode.get_nibble(0), 0x0d);
  EXPECT_EQ(opcode.get_nibble(1), 0x0c);
  EXPECT_EQ(opcode.get_nibble(2), 0x0b);
  EXPECT_EQ(opcode.get_nibble(3), 0x0a);
}

TEST_F(OpcodeParser, GetAddress) { EXPECT_EQ(opcode.get_addr(), 0x0bcd); }

TEST_F(OpcodeParser, GetOpcode) { EXPECT_EQ(opcode.get_opcode(), 0xabcd); }
