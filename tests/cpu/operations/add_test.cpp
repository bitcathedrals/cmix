#include "cpu.h"

#include <gtest/gtest.h>

TEST(Operation, Add) {
  add op;

  EXPECT_EQ(op(1,2,3), 5);
}

