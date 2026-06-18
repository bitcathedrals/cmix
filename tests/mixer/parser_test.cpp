#include <gtest/gtest.h>

#include "mixer/parser.h"

TEST(MixerParserSimple, MatchTopLevel) {
    std::string test_string("1234");

    Token p = Token::descent(Numeric(), test_string);

    EXPECT_EQ(p.get_type(), Token::label::number);
    EXPECT_EQ(p.get_token(), "1234");
}
