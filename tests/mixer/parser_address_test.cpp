#include <gtest/gtest.h>

#include <memory>
#include <iostream>
#include <fstream>

#include "mixer/parser.h"
#include "mixer/address.h"

TEST(MixerSimple, AddressSignedPositve) {
    std::string test_string("1234");

    Token p = Token::descent(build_signed_number_parser(), test_string);

    EXPECT_EQ(p.get_type(), Token::label::node);
    EXPECT_EQ(p.get_token(), "1234");
    EXPECT_EQ(std::stoi(p.get_token()), 1234);
}

TEST(MixerSimple, AddressSignedNegative) {
    std::string test_string("-1234");

    Token p = Token::descent(build_signed_number_parser(), test_string);

    EXPECT_EQ(p.walk("address_sign")->get_type(), Token::label::special);

    EXPECT_EQ(p.walk("address_number")->get_type(), Token::label::number);
    EXPECT_EQ(p.walk("address_number")->get_token(), "1234");
}

TEST(MixerAddress, AddressOnly) {
    std::string test_string("1234");

    auto p = Token::descent(build_address_parser(), test_string);

    auto number = p.walk("/address/address_number");

    ASSERT_NE(number, nullptr);

    EXPECT_EQ(number->get_token(), "1234");
}

TEST(MixerAddress, AddressIndexCorrect) {
    std::string test_string("1234,5");

    auto p = Token::descent(build_address_parser(), test_string);

    auto address = p.walk("address/address_number");

    ASSERT_NE(address, nullptr);

    EXPECT_EQ(address->get_type(), Token::label::number);
    EXPECT_EQ(address->get_token(), "1234");

    auto index = p.walk("index_field/idx_index");

    ASSERT_NE(index, nullptr);

    EXPECT_EQ(index->get_type(), Token::label::number);
    EXPECT_EQ(index->get_token(), "5");
}

TEST(MixerAddress, AddressFieldCorrect) {
    std::string test_string("1234(5:6)");

    auto p = Token::descent(build_address_parser(), test_string);

    auto address = p.walk("address/address_number");

    ASSERT_NE(address, nullptr);

    EXPECT_EQ(address->get_type(), Token::label::number);
    EXPECT_EQ(address->get_token(), "1234");

    auto field_left = p.walk("address_field/field_left_number");

    ASSERT_NE(field_left, nullptr);

    EXPECT_EQ(field_left->get_type(), Token::label::number);
    EXPECT_EQ(field_left->get_token(), "5");

    auto field_right = p.walk("address_field/field_right_number");

    ASSERT_NE(field_right, nullptr);

    EXPECT_EQ(field_right->get_type(), Token::label::number);
    EXPECT_EQ(field_right->get_token(), "6");
}

TEST(MixerAddress, AddressFieldBad) {
    std::string test_string("1234(:)");

    EXPECT_THROW(Token::descent(build_address_parser(), test_string), std::invalid_argument);
}

TEST(MixerAddress, AddressIndexFieldBad) {
    std::string test_string("1234,7(5:");

    EXPECT_THROW(Token::descent(build_address_parser(), test_string), std::invalid_argument);
}

TEST(MixerAddress, AddressIndexFieldCorrect) {
    std::string test_string("1234,5(6:7)");

    auto p = Token::descent(build_address_parser(), test_string);

    auto address = p.walk("address/address_number");

    ASSERT_NE(address, nullptr);

    EXPECT_EQ(address->get_type(), Token::label::number);
    EXPECT_EQ(address->get_token(), "1234");

    auto index = p.walk("index_field/idx_index");

    ASSERT_NE(index, nullptr);

    EXPECT_EQ(index->get_type(), Token::label::number);
    EXPECT_EQ(index->get_token(), "5");

    auto field_left = p.walk("index_field/idx_field/field_left_number");

    ASSERT_NE(field_left, nullptr);

    EXPECT_EQ(field_left->get_type(), Token::label::number);
    EXPECT_EQ(field_left->get_token(), "6");

    auto field_right = p.walk("index_field/idx_field/field_right_number");

    ASSERT_NE(field_right, nullptr);

    EXPECT_EQ(field_right->get_type(), Token::label::number);
    EXPECT_EQ(field_right->get_token(), "7");
}

