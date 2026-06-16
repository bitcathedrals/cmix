#ifndef MIXER_PARSER_H
#define MIXER_PARSER_H

#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include <cctype>

class Token {
public:
    enum class label {
        number,
        symbol,
        text,

        node,

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

    explicit Token(const Token::label type,
                   const std::string capture) : t {type}, value(capture) {}

    explicit Token(const std::vector<Token>& children) : t(Token::label::node),
                                                         tokens(children) {}
    virtual ~Token(void) {}

    void operator=(const std::vector<Token> parse) {tree = parse;};

    Token& set_optional(void) {
        optional = true;
        return *this;
    }

    Token::label get_type(void) const { return t; }
    const std::string get_match(void) const { return value; }
    const std::vector<Token>& get_parse(void) const { return tree; }

    Token match(std::string::const_iterator& i,
                std::string::const_iterator& end);

    Token parse(std::string::const_iterator& i,
                std::string::const_iterator& end);

protected:
    virtual bool is_capture(const char x [[maybe_unused]]) { return false; };

private:
    Token::label t;

    std::vector<Token> tokens;
    bool optional = false;

    std::vector<Token> tree;
    std::string value;

    static const std::array<char,4> constexpr terminal {' ', '\t', '\n', ','};

    bool is_terminal(const char x);

    void skip_terminal(std::string::const_iterator& i,
                       std::string::const_iterator& n);
};

class Alphabetic : public Token {
public:
    Alphabetic() : Token(Token::label::text) {}
    Alphabetic(const Alphabetic& from) : Token(from) {}

    Alphabetic(const Token::label label) : Token(label) {}
protected:
    virtual bool is_capture(const char x) {
        if (std::isalpha(x)) {
             return true;
         }

        return false;
    };
};

class Numeric : public Token {
public:
    Numeric() : Token(Token::label::number) {}
    Numeric(const Numeric& from) : Token(from) {}

    Numeric(const Token::label label) : Token(label) {}

protected:
    virtual bool is_capture(const char x) {
         if (std::isdigit(x)) {
             return true;
         }

         return false;
    };
};

class AlphaNumeric : public Token {
public:
    AlphaNumeric() : Token(Token::label::symbol) {}
    AlphaNumeric(const AlphaNumeric& from) : Token(from) {}

    AlphaNumeric(const Token::label label) : Token(label) {}

protected:
    virtual bool is_capture(const char x) {
        if (std::isalnum(x)) {
            return true;
        }

        return false;
    };
};

#endif
