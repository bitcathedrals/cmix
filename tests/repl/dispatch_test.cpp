#include <gtest/gtest.h>

#include <repl/dispatch.h>

class DispatchParsingFixture  : public testing::Test {
public:
    const char* null = nullptr;

    const char* empty = "";

    const char* one = "one";
    const char* two = "one two";
};

TEST_F(DispatchParsingFixture, NullPointerTest) {
    EXPECT_EQ(parse_input(null).size(), (unsigned long)0);
}

TEST_F(DispatchParsingFixture, EmptyStringTest) {
    EXPECT_EQ(parse_input(empty).size(), (unsigned long)0);
}

TEST_F(DispatchParsingFixture, OneWordTest) {
    EXPECT_EQ(parse_input(one).size(), (unsigned long)1);
    EXPECT_EQ(parse_input(one)[0], std::string("one"));
}

TEST_F(DispatchParsingFixture, TwoWordTest) {
    EXPECT_EQ(parse_input(two).size(), (unsigned long)2);
    EXPECT_EQ(parse_input(two)[0], std::string("one"));
    EXPECT_EQ(parse_input(two)[1], std::string("two"));
}
