#include "stack.h"

#include <gtest/gtest.h>

class StackAPI : public testing::Test {
 protected:
  chip8::stack stack;
};

TEST_F(StackAPI, FullAPITest) {
  EXPECT_EQ(stack.pop(), 0x0000);
  EXPECT_EQ(stack.top(), 0x0000);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_TRUE(stack.empty());
  EXPECT_FALSE(stack.full());

  stack.push(0x1234);

  EXPECT_EQ(stack.top(), 0x1234);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_FALSE(stack.empty());
  EXPECT_FALSE(stack.full());

  stack.push(0xabcd);

  EXPECT_EQ(stack.top(), 0xabcd);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_FALSE(stack.empty());
  EXPECT_FALSE(stack.full());

  EXPECT_EQ(stack.pop(), 0xabcd);
  EXPECT_EQ(stack.top(), 0x1234);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_FALSE(stack.empty());
  EXPECT_FALSE(stack.full());

  EXPECT_EQ(stack.pop(), 0x1234);
  EXPECT_EQ(stack.top(), 0x0000);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_TRUE(stack.empty());
  EXPECT_FALSE(stack.full());
}

TEST_F(StackAPI, OverflowProtection) {
  // Fill the stack
  for (auto i = 0; i < 8; i++) {
    stack.push(0xdead);
    stack.push(0xbeef);
  }

  // Should not be able to push this
  stack.push(0x1234);

  EXPECT_EQ(stack.top(), 0xbeef);
  EXPECT_NE(stack.top(), 0x1234);
  EXPECT_TRUE(stack.full());
}
