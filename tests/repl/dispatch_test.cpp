#include <string>

#include <gtest/gtest.h>

#include <parse.h>
#include <repl/dispatch.h>

class DispatchParsingFixture  : public testing::Test {
public:
    std::string empty {""};

    std::string one {"one"};
    std::string two {"one two"};
};

TEST_F(DispatchParsingFixture, EmptyStringTest) {
    EXPECT_EQ(parse_cli(empty).size(), (unsigned long)0);
}

TEST_F(DispatchParsingFixture, OneWordTest) {
    EXPECT_EQ(parse_cli(one).size(), (unsigned long)1);
    EXPECT_EQ(parse_cli(one)[0], std::string("one"));
}

TEST_F(DispatchParsingFixture, TwoWordTest) {
    EXPECT_EQ(parse_cli(two).size(), (unsigned long)2);
    EXPECT_EQ(parse_cli(two)[0], std::string("one"));
    EXPECT_EQ(parse_cli(two)[1], std::string("two"));
}
