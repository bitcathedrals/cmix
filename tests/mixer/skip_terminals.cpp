#include <gtest/gtest.h>

#include "mixer/parser.h"

TEST(MixerBasicToken, NumberAfterTerminals) {
    std::string blank_then_number("  22");

    std::string::const_iterator begin = blank_then_number.cbegin();
    std::string::const_iterator end = blank_then_number.cend();

    Numeric matcher(Token::label::number);

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::number);
    EXPECT_EQ(token.get_match().size(), static_cast<size_t>(2));
};


TEST(MixerBasicToken, EmptyString) {
    std::string empty("");

    std::string::const_iterator begin = empty.cbegin();
    std::string::const_iterator end = empty.cend();

    Numeric matcher(Token::label::number);

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::nothing);
    EXPECT_EQ(token.get_match().size(), static_cast<size_t>(0));
};


TEST(MixerBasicToken, AillTerminals) {
    std::string empty("  ");

    std::string::const_iterator begin = empty.cbegin();
    std::string::const_iterator end = empty.cend();

    Numeric matcher(Token::label::number);

    Token token = matcher.match(begin, end);

    EXPECT_EQ(token.get_type(), Token::label::nothing);
    EXPECT_EQ(token.get_match().size(), static_cast<size_t>(0));
};
