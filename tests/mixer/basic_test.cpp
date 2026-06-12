#include <gtest/gtest.h>

#include "mixer/parser.h"

TEST(MixerBasicToken, MatchNoInput) {
    std::string empty;

    std::string::const_iterator begin = empty.cbegin();
    std::string::const_iterator end = empty.cend();

    Alphabetic alpha(Token::label::text);

    Token token = alpha.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::nothing);
}


TEST(MixerBasicToken, MatchLowerCase) {
    std::string lower("aa");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Alphabetic matcher(Token::label::text);

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::text);
}
