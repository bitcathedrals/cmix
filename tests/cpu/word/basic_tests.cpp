#include "cpu.h"

#include <gtest/gtest.h>

#include <cpu/word/word_fixtures.h>

TEST_F(SimpleWordFixture, Init) {
  ASSERT_EQ(2, mix_word[0]);
  ASSERT_EQ(4, mix_word[1]);
  ASSERT_EQ(6, mix_word[2]);
  ASSERT_EQ(8, mix_word[3]);
  ASSERT_EQ(10, mix_word[4]);
}

