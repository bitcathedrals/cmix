#include <gtest/gtest.h>
#include <memory>

#include "mixer/parser.h"
#include "mixer/address.h"

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

TEST(MixerParserSimple, OptionalNotPresent) {
    std::string test_string("1234");

    production_t def;

    auto sign = std::make_unique<NumSign>();
    sign->set_optional()->set_name("sign");
    def.push_back(std::move(sign));

    def.push_back(std::make_unique<Numeric>());

    Token p = Token::descent(Token(std::move(def)), test_string);

    EXPECT_EQ(p.get_type(), Token::label::node);
    EXPECT_EQ(p.get_token(), "1234");
    EXPECT_EQ(std::stoi(p.get_token()), 1234);
}

TEST(MixerParserSimple, ComplexOk) {
    std::string test_string("1234 (10:2)");

    auto left_paren = std::make_unique<Special>();
    left_paren->set_name("left_paren");

    auto left_number = std::make_unique<Numeric>();
    left_number->set_name("left_number");

    auto field_middle = std::make_unique<Special>();
    field_middle->set_name("field_middle");

    auto right_number = std::make_unique<Numeric>();
    right_number->set_name("right_number");

    auto right_paren = std::make_unique<Special>();
    right_paren->set_name("right_paren");

    production_t field_def;

    field_def.push_back(std::move(left_paren));
    field_def.push_back(std::move(left_number));
    field_def.push_back(std::move(field_middle));
    field_def.push_back(std::move(right_number));
    field_def.push_back(std::move(right_paren));

    auto field_group = std::make_unique<Token>(std::move(field_def));
    field_group->set_name("field_group");

    production_t parser_def;

    auto leading_number = std::make_unique<Numeric>();
    leading_number->set_name("leading_number");

    parser_def.push_back(std::move(leading_number));
    parser_def.push_back(std::move(field_group));

    Token parser(std::move(parser_def));

    // descend

    Token AST = Token::descent(parser, test_string);

    EXPECT_EQ(AST.get_type(), Token::label::node);
    EXPECT_EQ(AST.size(), 2);
    EXPECT_EQ(AST[0].get_token(), "1234");
    EXPECT_EQ(AST[1].get_token(), "(10:2)");
}

TEST(MixerParserSimple, AddressCommaIndexOk) {
    std::string test_string("1234,4");

    auto p = Token::descent(build_address_parser(), test_string);

    EXPECT_EQ(p[0].get_type(), Token::label::node);

    EXPECT_EQ(p[0][0].get_type(), Token::label::number);
    EXPECT_EQ(p[0][0].get_token(), "1234");
    EXPECT_EQ(p[0][0].get_name(), "address_number");

    EXPECT_EQ(p[1].get_type(), Token::label::node);
    EXPECT_EQ(p[1][0].get_type(), Token::label::special);
    EXPECT_EQ(p[1][1].get_type(), Token::label::number);
    EXPECT_EQ(p[1][1].get_token(), "4");
}

TEST(MixerWalk, WalkEmptySlash) {
    std::string path("/");

    auto t = Token {};
    t.set_name("foo");

    auto ptr = t.walk(path);

    EXPECT_EQ(ptr->get_name(), "foo");
}

TEST(MixerWalk, WalkEmptyPath) {
    std::string path("");

    auto t = Token {};
    t.set_name("foo");

    auto ptr = t.walk(path);

    EXPECT_EQ(ptr->get_name(), "foo");
}

TEST(MixerWalk, PathAndNoTokens) {
    std::string path("/foo/bar/baz");

    Token t {};

    auto ptr = t.walk(path);

    EXPECT_EQ(ptr, nullptr);
}

TEST(MixerWalk,LongerPathThanTokens) {
    std::string path("/foo/bar/baz");

    Token t {};

    AST_t test_AST = std::vector<Token> {};

    test_AST.push_back(Token {});

    test_AST.back().set_name("foo");

    auto ptr = t.walk(path);

    EXPECT_EQ(ptr, nullptr);
}

TEST(MixerWalk,ShorterPathThanTokens) {
    std::string path("/foo");

    Token bar {};
    bar.set_name("bar");

    Token foo { std::move(AST_t { bar }) };
    foo.set_name("foo");

    Token t { std::move(AST_t { foo }) };

    auto ptr = t.walk(path);

    EXPECT_NE(ptr, nullptr);
}

TEST(MixerWalk, PathAndTokensSameLength) {
    std::string path("/foo/bar");

    Token bar {};
    bar.set_name("bar");

    Token foo { std::move(AST_t { bar }) };
    foo.set_name("foo");

    Token t { std::move(AST_t { foo }) };

    auto ptr = t.walk(path);

    EXPECT_NE(ptr, nullptr);
}

TEST(MixerWalk, WalkGetNode) {
    std::string path("/foo/bar");

    Token bar { Token::label::text, "check" };
    bar.set_name("bar");

    Token foo { std::move(AST_t { bar }) };
    foo.set_name("foo");

    Token t { std::move(AST_t { foo }) };

    auto ptr = t.walk(path);

    EXPECT_EQ(ptr->get_token(), "check");
}

TEST(MixerDepth, DepthSimple) {
    std::string test_string("1234,5");

    auto p = Token::descent(build_address_parser(), test_string);

    split_t depth = p.depth();

    EXPECT_EQ(depth.back(), "index_field");
}
