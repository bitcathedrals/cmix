#include "split.h"

#include <gtest/gtest.h>

#include "cpu/defs.h"

TEST(SplitCli, EmptyStringTest) {
    std::string empty {""};

    EXPECT_EQ(split_cli(empty).size(), static_cast<size_t>(0));
}

TEST(SplitCli, OneWordTest) {
    std::string one {"one"};

    EXPECT_EQ(split_cli(one).size(), static_cast<size_t>(1));
    EXPECT_EQ(split_cli(one)[0], std::string("one"));
}

TEST(SplitCli, TwoWordTest) {
    std::string two {"one two"};

    EXPECT_EQ(split_cli(two).size(), static_cast<size_t>(2));
    EXPECT_EQ(split_cli(two)[0], std::string("one"));
    EXPECT_EQ(split_cli(two)[1], std::string("two"));
}


TEST(SplitWord, EmptyStringTest) {
    std::string empty {""};

    EXPECT_EQ(split_word(empty).size(), static_cast<size_t>(0));
}

TEST(SplitWord, SeperatorOnly) {
    std::string sep { ":" };
    split_t p = split_word(sep);

    EXPECT_EQ(p.size(), static_cast<size_t>(0));
}

TEST(SplitWord, OneByteValue) {
    std::string input { "32" };
    split_t p = split_word(input);

    EXPECT_EQ(p.size(), static_cast<size_t>(1));
    EXPECT_EQ(p[0], "32");
}

TEST(SplitWord, TwoByteValue) {
    std::string byte { "16:32" };
    split_t p = split_word(byte);

    EXPECT_EQ(p.size(), static_cast<size_t>(2));
    EXPECT_EQ(p[0], "16");
    EXPECT_EQ(p[1], "32");
}

TEST(SplitWord, FullWord) {
    std::string input { "8:12:24:36:48" };
    split_t p = split_word(input);

    EXPECT_EQ(p.size(), static_cast<size_t>(5));

    EXPECT_EQ(p[0], "8");
    EXPECT_EQ(p[1], "12");
    EXPECT_EQ(p[2], "24");
    EXPECT_EQ(p[3], "36");
    EXPECT_EQ(p[4], "48");
}

TEST(SplitPath, EmptyStringTest) {
    std::string empty {""};

    EXPECT_EQ(split_path(empty).size(), static_cast<size_t>(0));
}


TEST(SplitPath, EmptySplitTest) {
    std::string empty {"/"};

    EXPECT_EQ(split_path(empty).size(), static_cast<size_t>(0));
}

TEST(SplitPath, OneSegment) {
    std::string one {"/foo"};

    auto foo = split_path(one);

    EXPECT_EQ(foo[0], std::string("foo"));
}

TEST(SplitPath, TwoSegments) {
    std::string two {"/foo/bar"};

    auto two_vec = split_path(two);

    EXPECT_EQ(two_vec[0], std::string("foo"));
    EXPECT_EQ(two_vec[1], std::string("bar"));
}
