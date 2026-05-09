#include "cpu.h"

#include <gtest/gtest.h>

#include <cpu/word/fixtures.h>

//
// Constructor and Init tests.
//

TEST(SimpleWordTests, DefaultConstructor) {
    word test_word;

    ASSERT_EQ(0, test_word[0]);
    ASSERT_EQ(0, test_word[1]);
    ASSERT_EQ(0, test_word[2]);
    ASSERT_EQ(0, test_word[3]);
    ASSERT_EQ(0, test_word[4]);
}

TEST_F(WordFixture, InitSetAndReadBack) {
  ASSERT_EQ(2, mix_word[0]);
  ASSERT_EQ(4, mix_word[1]);
  ASSERT_EQ(6, mix_word[2]);
  ASSERT_EQ(8, mix_word[3]);
  ASSERT_EQ(10, mix_word[4]);
}

TEST_F(WordFixture, SetValuesInConstructor) {
    word foo(1,3,5,9,11);

    ASSERT_EQ(1, foo[0]);
    ASSERT_EQ(3, foo[1]);
    ASSERT_EQ(5, foo[2]);
    ASSERT_EQ(9, foo[3]);
    ASSERT_EQ(11, foo[4]);
}

TEST_F(WordFixture, CopyConstructor) {
    word foo(mix_word);

    ASSERT_EQ(2, foo[0]);
    ASSERT_EQ(4, foo[1]);
    ASSERT_EQ(6, foo[2]);
    ASSERT_EQ(8, foo[3]);
    ASSERT_EQ(10, foo[4]);
}

//
// operators
//

TEST_F(WordFixture, SetViaIndexOperator) {
    mix_word[1] = 12;

    EXPECT_EQ(mix_word[1], 12);
}

//
// overflow
//

TEST_F(WordFixture, SimpleIsNotOverflowed) {
    mix_word[1] = 48;

    EXPECT_EQ(mix_word.overflowed(1), false);
}

TEST_F(WordFixture, SimpleIsOverflow) {
    mix_word[1] = 72;

    EXPECT_EQ(mix_word.overflowed(1), true);
}

//
// copy ranges
//
