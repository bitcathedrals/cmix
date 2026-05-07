#include <gtest/gtest.h>

#include <cpu/operations/ops.h>

TEST(Operation, Add) {
  add op;

  EXPECT_EQ(op(1,2,3), 5);
}

