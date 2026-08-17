#include <cctype>
#include <gtest/gtest.h>

#include "mixer/parser.h"

TEST(MixerBasicToken, MatchNoInput) {
    std::string empty;

    std::string::const_iterator begin = empty.cbegin();
    std::string::const_iterator end = empty.cend();

    Alphabetic alpha;

    Token token = alpha.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::nothing);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(0));
}

TEST(MixerBasicToken, MatchWhitespaceSkip) {
    std::string ws("  ");

    std::string::const_iterator ws_start = ws.cbegin();

    std::string::const_iterator ws_begin = ws.cbegin();
    std::string::const_iterator ws_end = ws.cend();

    Alphabetic ws_skip;
    ws_skip.match(ws_begin, ws_end);

    EXPECT_EQ(std::distance(ws_start,ws_begin), 2);
}

TEST(MixerBasicToken, MatchLowerCase) {
    std::string lower("aa");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Alphabetic matcher;

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::text);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(2));
    EXPECT_EQ(token.get_token(), "aa");
}

TEST(MixerBasicToken, MatchInjectNumbers) {
    std::string lower("22aa");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Alphabetic matcher;

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::nothing);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(0));
}

//
// Numeric
//

TEST(MixerBasicToken, NumberMatchTest) {
    std::string lower("22aa");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Numeric matcher;

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::number);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(2));
    EXPECT_EQ(token.get_token(), "22");
}

TEST(MixerBasicToken, NumberUnreachableTest) {
    std::string lower("aa22");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Numeric matcher;

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::nothing);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(0));
}

TEST(MixerBasicToken, NumberGappedTest) {
    std::string lower("22 44");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Numeric matcher;

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::number);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(2));
}

//
// punctuation
//

TEST(MixerBasicToken, SpecialTest) {
    std::string lower("!!");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Special matcher;

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::special);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(2));
    EXPECT_EQ(token.get_token(), "!!");
}

TEST(MixerBasicToken, LiteralTestMatch) {
    std::string lower(":");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Literal matcher(':');

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::special);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(1));
    EXPECT_EQ(token.get_token(), ":");
}

TEST(MixerBasicToken, StopBeforeEndAndReturn) {
    Numeric matcher;

    std::string input("1234,");

    std::string::const_iterator begin = input.cbegin();
    std::string::const_iterator end = input.cend();

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::number);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(4));
    EXPECT_EQ(token.get_token(), "1234");

}
