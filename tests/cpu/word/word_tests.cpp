#include <cpu/cpu.h>

#include <gtest/gtest.h>

#include <cpu/word.h>

//
// Constructor and Init tests.
//

TEST(WordConstructorTests, DefaultConstructor) {
    Word test_word;

    EXPECT_EQ(0, test_word[0]);
    EXPECT_EQ(0, test_word[1]);
    EXPECT_EQ(0, test_word[2]);
    EXPECT_EQ(0, test_word[3]);
    EXPECT_EQ(0, test_word[4]);
}

TEST(WordConstructorTests, CopyConstructor) {
    Word other_word(1,2,3,4,5);

    Word test(other_word);

    EXPECT_EQ(1, test[0]);
    EXPECT_EQ(2, test[1]);
    EXPECT_EQ(3, test[2]);
    EXPECT_EQ(4, test[3]);
    EXPECT_EQ(5, test[4]);
}


TEST(WordConstructorTests, InitSetAndReadBack) {
    Word mix_word(2,4,6,8,10);

    EXPECT_EQ(2, mix_word[0]);
    EXPECT_EQ(4, mix_word[1]);
    EXPECT_EQ(6, mix_word[2]);
    EXPECT_EQ(8, mix_word[3]);
    EXPECT_EQ(10, mix_word[4]);
}

//
// overflow
//

TEST(WordOverflowTests, SimpleIsNotOverflowed) {
    Word mix_word;
    mix_word[1] = 48;

    EXPECT_EQ(mix_word.overflowed(1), false);
}

TEST(WordOverflowTests, SimpleIsOverflow) {
    Word mix_word;

    mix_word[1] = 72;

    EXPECT_EQ(mix_word.overflowed(1), true);
}

//
// operators
//

TEST(WordReadWriteTests, AssignOperatorNumber) {
    Word mix_word;
    mix_word [1] = 12;

    EXPECT_EQ(mix_word[1], 12);
}

TEST(WordReadWriteTests, AssignOperatorParse) {
    Word mix_word;

    mix_word = parse_word("1::2::3::4::5");

    EXPECT_EQ(mix_word[0], 1);
    EXPECT_EQ(mix_word[1], 2);
    EXPECT_EQ(mix_word[2], 3);
    EXPECT_EQ(mix_word[3], 4);
    EXPECT_EQ(mix_word[4], 5);
}

TEST(WordOperatorEqual, SimpleEqualsTrueTest) {
    Word left_word(1,2,3,4,5);
    Word right_word(1,2,3,4,5);

    EXPECT_EQ(left_word == right_word, true);
}

TEST(WordOperatorEqual, SimpleEqualsFalseTest) {
    Word left_word(1,2,3,4,5);
    Word right_word(1,3,5,9,13);

    EXPECT_EQ(left_word == right_word, false);
}
