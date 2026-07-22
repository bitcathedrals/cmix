#include <format>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "mixer/parser.h"

Token::Token() : t {Token::label::end}  {}

Token::Token(const Token::label label) : t {label} {}

Token::Token(const Token::label type,
             const std::string capture) : t {type},
                                          value(capture) {}

Token::Token(AST_t&& parse) : t {Token::label::node},
                              tree {std::move(parse)} {}

Token::Token(production_t&& children) : t(Token::label::node) {
    tokens = std::move(children);
}

Token* Token::set_name(const std::string ast_name) {
    name = ast_name;
    return this;
}

std::string Token::get_name(void) const {
    return name;
}

void Token::operator=(AST_t&& parse) {
    tree = std::move(parse);
}

const Token& Token::operator[](int index) const {
    return tree[index];
}

const std::string Token::get_token(void) const {
    if(t == Token::label::node) {
        std::string traversed;

        for(size_t i = 0; i < tree.size(); i++) {
            traversed += tree[i].get_token();
        }

        return traversed;
    }

    return value;
}

Token* Token::set_optional(void) {
    optional = true;
    return this;
}

bool Token::is_capture(const char x [[maybe_unused]]) const {
    throw std::logic_error("is_capture should never be called in the Token base class");
    return false;
};

bool Token::is_terminal(const char x) const {
    for(auto t : terminal) {
        if(x == t) {
            return true;
        }
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

Token Token::parse(std::string::const_iterator& begin,
                   std::string::const_iterator& end) const {
    AST_t parse;

    auto backtrack = begin;

    for(size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i]->get_type() == Token::label::node) {
            auto ascent = tokens[i]->parse(begin, end);

            if(ascent.get_type() == Token::label::nothing) {
                if(tokens[i]->optional) {
                    begin = backtrack;
                    continue;
                }

                std::string diagnostic;

                if(parse.size() < 1) {
                    diagnostic = "<none>";
                }
                else {
                    const Token& last = parse.back();
                    diagnostic = last.get_token();
                }

                throw std::invalid_argument(std::format("Token::parse {} failed {} characters after checkpoint \"{}\"",
                                                        tokens[i]->get_name(),
                                                        std::distance(backtrack, begin),
                                                        diagnostic));
            }

            backtrack = begin;
            parse.push_back(std::move(ascent));
        }
        else {
            auto ascent = tokens[i]->match(begin, end);

            if(ascent.get_type() == Token::label::nothing) {
                if(tokens[i]->get_optional()) {
                    begin = backtrack;
                    continue;
                }

                std::string diagnostic;

                if(parse.size() < 1) {
                    diagnostic = "<none>";
                }
                else {
                    const Token& last = parse.back();
                    diagnostic = last.get_token();
                }

                throw std::invalid_argument(std::format("Token::match {} failed {} characters after checkpoint \"{}\"",
                                                        tokens[i]->get_name(),
                                                        std::distance(backtrack, begin),
                                                        diagnostic));
            }

            backtrack = begin;
            parse.push_back(std::move(ascent));
        }

        if(begin == end) {
            break;
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

    try {
        if (definition.get_type() == Token::label::node) {
            return definition.parse(i, end);
        }
        else {
            return definition.match(i, end);
        }
    } catch(std::invalid_argument exception) {
        std::cerr << "cmix parser fail: " << exception.what() << "on input: " << text << std::endl;
        throw;
    }
}

Token Token::descent(const std::unique_ptr<const Token> definition, const std::string text) {
    auto i = text.cbegin();
    auto end = text.cend();

    try {
        if (definition->get_type() == Token::label::node) {
            return definition->parse(i, end);
        }
        else {
            return definition->match(i, end);
        }
    } catch(std::invalid_argument exception) {
        std::cerr << "cmix parser fail: " << exception.what() << "on input: " << text << std::endl;
        throw;
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

bool NumSign::is_capture(const char x) const {
    if (x == '+' || x == '-') {
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
