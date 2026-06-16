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

void Token::skip_terminal(std::string::const_iterator& i,
                          std::string::const_iterator& end) {

    while(i != end) {
        char x = *i;

        for(char z : terminal) {
            if (x == z) {
                goto next_char;
            }
        }

        return; // if it's not a terminal

    next_char: i++;
    }
}

Token Token::match(std::string::const_iterator& i,
                   std::string::const_iterator& end) {

    skip_terminal(i, end);

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

Token Token::parse(std::string::const_iterator& i,
                   std::string::const_iterator& end) {
    std::vector<Token> parse;

    for(auto x : tokens) {
        if (x.get_type() == Token::label::node) {
            parse.push_back(x.parse(i, end));
        }
        else {
            parse.push_back(x.match(i, end));
        }
    }

    Token tmp(Token::label::node);
    tmp = parse;

    return tmp;
}
