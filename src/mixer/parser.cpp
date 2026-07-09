#include <algorithm>

#include "mixer/parser.h"

Token::Token() : t {Token::label::end} {}

Token::Token(const Token::label label) : t {label} {}

Token::Token(const Token::label type,
             const std::string capture) : t {type},
                                          value(capture) {}

Token::Token(AST_t&& parse) : t {Token::label::node},
                              tree {std::move(parse)} {}

Token::Token(production_t&& children) : t(Token::label::node) {
    tokens = std::move(children);
}

void Token::operator=(AST_t&& parse) {
    tree = std::move(parse);
}

const Token& Token::operator[](int index) const {
    return tree[index];
}

Token& Token::set_optional(void) {
    optional = true;
    return *this;
}

bool Token::is_capture(const char x [[maybe_unused]]) const {
    throw std::logic_error("is_capture should never be called in the Token base class");
    return false;
};

bool Token::is_terminal(const char x) const {
    if(terminal[0] == x ||
       terminal[1] == x ||
       terminal[2] == x ||
       terminal[3] == x) {
        return true;
    }

    return false;
}

void Token::skip_terminal(std::string::const_iterator& i,
                          std::string::const_iterator& end) const {

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
                   std::string::const_iterator& end) const {

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
                   std::string::const_iterator& end) const {
    AST_t parse;

    for(const auto& x : tokens) {
        if (x->get_type() == Token::label::node) {
            parse.push_back(x->parse(i, end));
        }
        else {
            parse.push_back(x->match(i, end));
        }
    }

    if (parse.size() < 1) {
        return Token(Token::label::nothing);
    }

    return Token(std::move(parse));
}

Token Token::descent(const Token& definition, const std::string text) {
    auto i = text.cbegin();
    auto end = text.cend();

    if (definition.get_type() == Token::label::node) {
        return definition.parse(i, end);
    }
    else {
        return definition.match(i, end);
    }
}

std::ostream& operator<<(std::ostream& out, const Token& token) {
    std::string label;

    switch(token.t) {
        case Token::label::number:
            label = "number";
            break;
        case Token::label::text:
            label = "text";
            break;
        case Token::label::symbol:
            label = "symbol";
            break;
        case Token::label::special:
            label = "special";
            break;

        case Token::label::node:
            label = "node";
            break;

        case Token::label::nothing:
            label = "nothing";
            break;
        case Token::label::error:
            label = "error";
            break;
        case Token::label::end:
            label = "end";
            break;
    }

    out << " label = " << label
        << " value = " << token.value;

    return out;
}

bool Alphabetic::is_capture(const char x) const {
    if (std::isalpha(x)) {
        return true;
    }

    return false;
}

bool Numeric::is_capture(const char x) const {
    if (std::isdigit(x)) {
        return true;
    }

    return false;
}

 bool AlphaNumeric::is_capture(const char x) const {
     if (std::isalnum(x)) {
         return true;
     }

     return false;
 }

 bool Punctuation::is_capture(const char x) const {
     if (std::ispunct(x)) {
         return true;
     }

     return false;
  }
