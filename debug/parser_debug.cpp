#include <string>
#include <iostream>

#include "mixer/parser.h"

void parser_minimal_descent(void) {
    std::string test_string("1234");

    Token p = Token::descent(Numeric(), test_string);

    Token::label t = p.get_type();

    std::string captured = p.get_token();

    std::cerr << "t is: " << static_cast<int>(t) << " token is: " << captured << std::endl;
}
