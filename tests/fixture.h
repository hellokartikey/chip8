#include <gtest/gtest.h>

#include "chip8.h"

class EmulatorFixture : public testing::Test {
 protected:
  chip8::chip8 emulator;
};
