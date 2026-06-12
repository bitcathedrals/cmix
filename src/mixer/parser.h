#ifndef MIXER_PARSER_H
#define MIXER_PARSER_H

#include <algorithm>
#include <array>
#include <string>
#include <vector>

class Token {
public:
    enum class label {
        number,
        symbol,
        text,

        nothing,
        error,
        end
    };

    Token() : t {Token::label::end} {}

    Token(const Token& from) : t(from.t) ,
                               tokens(from.tokens),
                               tree(from.tree),
                               value(from.value) {}

    explicit Token(const Token::label label) : t {label} {}

    explicit Token(const Token::label type, const std::string capture) : t(type),
                                                                         value(capture) {}

    explicit Token(const Token::label type, const std::vector<Token>& children) : t(type),
                                                                                  tokens(children) {}

    virtual ~Token(void) {}


    Token& operator=(const Token& from);
    Token& operator=(const std::vector<Token> parse);

protected:
    virtual bool is_capture(const char x [[maybe_unused]]) { return false; };

private:
    Token::label t;
    std::vector<Token> tokens;

    std::vector<Token> tree;
    std::string value;

    static const std::array<char,4> constexpr terminal {' ', '\t', '\n', ','};

    bool is_terminal(const char x);

    Token match(std::string::const_iterator& i,
                std::string::const_iterator& end);

    Token parse(std::string::const_iterator& i,
                std::string::const_iterator& end);
};


class Alphabetic : public Token {
public:
    Alphabetic() : Token() {}

    Alphabetic(const Alphabetic& from) : Token(from) {}

    explicit Alphabetic(const Token::label label) : Token{label} {}

    explicit Alphabetic(const Token::label type, const std::string capture) : Token(type, capture) {}

    explicit Alphabetic(const Token::label type, const std::vector<Token>& children) : Token(type, children) {}
};

#endif
