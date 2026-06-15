#include <gtest/gtest.h>

#include "mixer/parser.h"

TEST(MixerBasicToken, NumberAfterTerminals) {
    std::string lower("  22");

    std::string::const_iterator begin = lower.cbegin();
    std::string::const_iterator end = lower.cend();

    Numeric matcher(Token::label::number);

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::number);
    EXPECT_EQ(token.get_match().size(), static_cast<size_t>(2));
};
