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

//
// word parsing
//

TEST(WordParsing, EmptyStringTest) {
    std::string empty {""};

    EXPECT_EQ(parse_word_cli(empty).size(), (unsigned long)0);
}

TEST(WordParsing, SeperatorOnly) {
    std::string sep { "::" };
    parse_t p = parse_word_cli(sep);

    EXPECT_EQ(p.size(), (unsigned long)0);
}

TEST(WordParsing, OneByteValue) {
    std::string byte { "32" };
    parse_t p = parse_word_cli(byte);

    EXPECT_EQ(p.size(), (unsigned long)1);
    EXPECT_EQ(p[0], "32");
}

TEST(WordParsing, TwoByteValue) {
    std::string byte { "16::32" };
    parse_t p = parse_word_cli(byte);

    EXPECT_EQ(p.size(), (unsigned long)2);
    EXPECT_EQ(p[0], "16");
    EXPECT_EQ(p[1], "32");
}

TEST(WordParsing, FullWord) {
    std::string input { "8::12::24::36::48" };
    parse_t p = parse_word_cli(input);

    EXPECT_EQ(p.size(), (unsigned long)5);

    EXPECT_EQ(p[0], "8");
    EXPECT_EQ(p[1], "12");
    EXPECT_EQ(p[2], "24");
    EXPECT_EQ(p[3], "36");
    EXPECT_EQ(p[4], "48");
}

