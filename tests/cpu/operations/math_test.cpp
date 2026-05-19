#include <gtest/gtest.h>

#include <cpu/operations/ops.h>

TEST(MathOperation, Add) {
  Add op;

  EXPECT_EQ(op(1,2,3), 5);
}

