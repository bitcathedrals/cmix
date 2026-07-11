#include <cpu/cpu.h>

#include <gtest/gtest.h>

#include "cpu/short.h"

//
// Constructor and Init tests.
//

TEST(ShortConstructorTests, DefaultConstructor) {
    Short test_short;

    EXPECT_EQ(0, test_short[1]);
    EXPECT_EQ(0, test_short[2]);
}

TEST(ShortConstructorTests, CopyConstructor) {
    Short other_short(1,2);

    Short test(other_short);

    EXPECT_EQ(1, test[1]);
    EXPECT_EQ(2, test[2]);
}


TEST(ShortConstructorTests, InitSetAndReadBack) {
    Short mix_short(2,4);

    EXPECT_EQ(2, mix_short[1]);
    EXPECT_EQ(4, mix_short[2]);
}

TEST(ShortUtilityTests, Reset) {
    Short mix_short(2,4);

    mix_short.reset();

    EXPECT_EQ(0, mix_short[1]);
    EXPECT_EQ(0, mix_short[2]);
}

//
// overflow
//

TEST(ShortOverflowTests, SimpleIsNotOverflowed) {
    Short mix_short;
    mix_short[1] = 48;

    EXPECT_EQ(mix_short.overflowed(1), false);
}

TEST(ShortOverflowTests, SimpleIsOverflow) {
    Short mix_short;

    mix_short[1] = 72;

    EXPECT_EQ(mix_short.overflowed(1), true);
}

//
// operators
//

TEST(ShortReadWriteTests, AssignOperatorNumber) {
    Short mix_short;
    mix_short [1] = 12;

    EXPECT_EQ(mix_short[1], 12);
}

TEST(ShortReadWriteTests, AssignOperatorParse) {
    Short mix_short;

    mix_short = parse_word("1::2");

    EXPECT_EQ(mix_short[1], 1);
    EXPECT_EQ(mix_short[2], 2);
}

TEST(ShortOperatorEqual, SimpleEqualsTrueTest) {
    Short left_short(1,2);
    Short right_short(1,2);

    EXPECT_EQ(left_short == right_short, true);
}

TEST(ShortOperatorEqual, SimpleEqualsFalseTest) {
    Short left_short(1,2);
    Short right_short(1,3);

    EXPECT_EQ(left_short == right_short, false);
}
