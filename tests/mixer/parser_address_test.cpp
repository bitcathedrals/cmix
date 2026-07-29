#include <gtest/gtest.h>
#include <memory>

#include "mixer/parser.h"
#include "mixer/address.h"

TEST(MixerAddress, AddressOnly) {
    std::string test_string("1234");

    auto p = Token::descent(build_address_parser(), test_string);

    EXPECT_EQ(p[0].get_type(), Token::label::node);

    auto address = p.walk("address_address/address_number");

    ASSERT_NE(address, nullptr);

    EXPECT_EQ(address->get_type(), Token::label::number);
    EXPECT_EQ(address->get_token(), "1234");
}

TEST(MixerAddress, CommaAddressIndexCorrect) {
    std::string test_string("1234,4");

    auto p = Token::descent(build_address_parser(), test_string);

    EXPECT_EQ(p[0].get_type(), Token::label::node);

    auto address = p.walk("address_address/address_number");

    ASSERT_NE(address, nullptr);

    EXPECT_EQ(address->get_type(), Token::label::number);
    EXPECT_EQ(address->get_token(), "1234");

    auto comma_index = p.walk("address_comma_index/CommaIndex_index");

    ASSERT_NE(comma_index, nullptr);

    EXPECT_EQ(comma_index->get_type(), Token::label::number);
    EXPECT_EQ(comma_index->get_token(), "4");
}
