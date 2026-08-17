#include "mixer/address.h"

std::unique_ptr<Token> build_signed_number_parser(void) {
    production_t define;

    auto sign = std::make_unique<NumSign>();
    sign->set_optional()->set_name("address_sign");

    auto number = std::make_unique<Numeric>();
    number->set_name("address_number");

    define.push_back(std::move(sign));
    define.push_back(std::move(number));

    auto adr = std::make_unique<Token>(std::move(define));
    adr->set_name("address");

    return adr;
}

std::unique_ptr<Token> build_field_parser(void) {
    production_t define;

    auto left_paren = std::make_unique<Literal>('(');
    left_paren->set_name("field_left_paren");

    auto left_number = std::make_unique<Numeric>();
    left_number->set_name("field_left_number");

    auto field_middle = std::make_unique<Literal>(':');
    field_middle->set_name("field_middle");

    auto right_number = std::make_unique<Numeric>();
    right_number->set_name("field_right_number");

    auto right_paren = std::make_unique<Literal>(')');
    right_paren->set_name("right_paren");

    define.push_back(std::move(left_paren));
    define.push_back(std::move(left_number));
    define.push_back(std::move(field_middle));
    define.push_back(std::move(right_number));
    define.push_back(std::move(right_paren));

    return std::make_unique<Token>(std::move(define));
}

std::unique_ptr<Token> build_index_field_parser(void) {
    production_t define;

    auto comma = std::make_unique<Literal>(',');
    comma->set_name("idx_comma");

    auto index = std::make_unique<Numeric>();
    index->set_name("idx_index");

    auto field = build_field_parser();
    field->set_name("idx_field");

    define.push_back(std::move(comma));
    define.push_back(std::move(index));
    define.push_back(std::move(field));

    return std::make_unique<Token>(std::move(define));
}

std::unique_ptr<Token> build_address_parser(void) {
    // address
    production_t address;

    address.push_back(build_signed_number_parser());
    address.back()->set_name("address");

    // address index field

    address.push_back(build_index_field_parser());
    address.back()->set_optional()->set_name("index_field");

    // address field

    address.push_back(build_field_parser());
    address.back()->set_optional()->set_name("address_field");

    auto finished = std::make_unique<Token>(std::move(address));
    finished->set_name("root");

    return finished;
}
