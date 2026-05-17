#include <cpu/cpu.h>

#include <gtest/gtest.h>

#include <cpu/word.h>
#include <cpu/word/fixtures.h>

//
// Constructor and Init tests.
//

TEST(SimpleWordTests, DefaultConstructor) {
    Word test_word;

    EXPECT_EQ(0, test_word[0]);
    EXPECT_EQ(0, test_word[1]);
    EXPECT_EQ(0, test_word[2]);
    EXPECT_EQ(0, test_word[3]);
    EXPECT_EQ(0, test_word[4]);
}

TEST_F(WordFixture, InitSetAndReadBack) {
    Word test_word(2,4,6,8,10);

  EXPECT_EQ(2, mix_word[0]);
  EXPECT_EQ(4, mix_word[1]);
  EXPECT_EQ(6, mix_word[2]);
  EXPECT_EQ(8, mix_word[3]);
  EXPECT_EQ(10, mix_word[4]);
}

TEST_F(WordFixture, CopyConstructor) {
    Word test_word(2,4,6,8,10);
    Word foo(mix_word);

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
// parsing
//


//
// copy ranges
//
