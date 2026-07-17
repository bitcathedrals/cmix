#include <gtest/gtest.h>
#include <memory>

#include "mixer/parser.h"

TEST(MixerParserSimple, MatchTopLevel) {
    std::string test_string("1234");

    Token p = Token::descent(Numeric(), test_string);

    EXPECT_EQ(p.get_type(), Token::label::number);
    EXPECT_EQ(p.get_token(), "1234");
}

TEST(MixerParserSimple, SimpleAST) {
    std::string test_string("12 34");

    production_t def;

    def.push_back(std::make_unique<Numeric>());
    def.push_back(std::make_unique<Numeric>());

    Token p = Token::descent(Token(std::move(def)), test_string);

    EXPECT_EQ(p.get_type(), Token::label::node);

    EXPECT_EQ(p[0].get_type(), Token::label::number);
    EXPECT_EQ(p[0].get_token(), "12");

    EXPECT_EQ(p[1].get_type(), Token::label::number);
    EXPECT_EQ(p[1].get_token(), "34");
}


TEST(MixerParserSimple, OptionalPresent) {
    std::string test_string("-1234");

    production_t def;

    auto sign = std::make_unique<NumSign>();
    sign->set_optional()->set_name("sign");
    def.push_back(std::move(sign));

    def.push_back(std::make_unique<Numeric>());

    Token p = Token::descent(Token(std::move(def)), test_string);

    EXPECT_EQ(p.get_type(), Token::label::node);
    EXPECT_EQ(p.get_token(), "-1234");
    EXPECT_EQ(std::stoi(p.get_token()), -1234);
}
