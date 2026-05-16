#include <gtest/gtest.h>

#include <parse.h>

TEST(CliParsing, EmptyStringTest) {
    std::string empty {""};

    EXPECT_EQ(parse_cli(empty).size(), (unsigned long)0);
}

TEST(CliParsing, OneWordTest) {
    std::string one {"one"};

    EXPECT_EQ(parse_cli(one).size(), (unsigned long)1);
    EXPECT_EQ(parse_cli(one)[0], std::string("one"));
}

TEST(CLiParsing, TwoWordTest) {
    std::string two {"one two"};

    EXPECT_EQ(parse_cli(two).size(), (unsigned long)2);
    EXPECT_EQ(parse_cli(two)[0], std::string("one"));
    EXPECT_EQ(parse_cli(two)[1], std::string("two"));
}
