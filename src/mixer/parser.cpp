#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "mixer/parser.h"

bool Token::is_terminal(const char x) {
    if(terminal[0] == x ||
       terminal[1] == x ||
       terminal[2] == x ||
       terminal[3] == x) {
        return true;
    }

    return false;
}

Token Token::match(std::string::const_iterator& i,
                   std::string::const_iterator& end) {

    std::string capture;

    while(i != end) {
        char x = *i;

        if (is_capture(x)) {
            capture.push_back(x);
            i++;
        }
        else {
            break;
        }
    }

    if (capture.size() < 1) {
        return Token(Token::label::nothing);
    }

    return Token(t, capture);
}


Token Token::parse(std::string::const_iterator& i [[maybe_unused]],
                   std::string::const_iterator& end [[maybe_unused]]) {

    return Token();
}
