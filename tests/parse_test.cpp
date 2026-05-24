#include <parse.h>

#include <gtest/gtest.h>

#include <cpu/defs.h>

using cmp_type = unsigned long;

TEST(ParseCliParsing, EmptyStringTest) {
    std::string empty {""};

    EXPECT_EQ(parse_cli(empty).size(), static_cast<cmp_type>(0));
}

TEST(ParseCliParsing, OneWordTest) {
    std::string one {"one"};

    EXPECT_EQ(parse_cli(one).size(), static_cast<cmp_type>(1));
    EXPECT_EQ(parse_cli(one)[0], std::string("one"));
}

TEST(ParseCliParsing, TwoWordTest) {
    std::string two {"one two"};

    EXPECT_EQ(parse_cli(two).size(), static_cast<cmp_type>(2));
    EXPECT_EQ(parse_cli(two)[0], std::string("one"));
    EXPECT_EQ(parse_cli(two)[1], std::string("two"));
}

//
// word parsing
//

TEST(ParseWordParsing, EmptyStringTest) {
    std::string empty {""};

    EXPECT_EQ(parse_word(empty).size(), static_cast<cmp_type>(0));
}

TEST(ParseWordParsing, SeperatorOnly) {
    std::string sep { "::" };
    parse_t p = parse_word(sep);

    EXPECT_EQ(p.size(), static_cast<cmp_type>(0));
}

TEST(ParseWordParsing, OneByteValue) {
    std::string input { "32" };
    parse_t p = parse_word(input);

    EXPECT_EQ(p.size(), static_cast<cmp_type>(1));
    EXPECT_EQ(p[0], "32");
}

TEST(ParseWordParsing, TwoByteValue) {
    std::string byte { "16::32" };
    parse_t p = parse_word(byte);

    EXPECT_EQ(p.size(), static_cast<cmp_type>(2));
    EXPECT_EQ(p[0], "16");
    EXPECT_EQ(p[1], "32");
}

TEST(ParseWordParsing, FullWord) {
    std::string input { "8::12::24::36::48" };
    parse_t p = parse_word(input);

    EXPECT_EQ(p.size(), static_cast<cmp_type>(5));

    EXPECT_EQ(p[0], "8");
    EXPECT_EQ(p[1], "12");
    EXPECT_EQ(p[2], "24");
    EXPECT_EQ(p[3], "36");
    EXPECT_EQ(p[4], "48");
}
