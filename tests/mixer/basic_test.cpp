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

TEST(MixerBasicToken, MatchLowerCase) {
    std::string lower("aa");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Alphabetic matcher;

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::text);
    EXPECT_EQ(token.get_token().size(), static_cast<size_t>(2));
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
