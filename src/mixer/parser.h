#ifndef MIXER_PARSER_H
#define MIXER_PARSER_H

#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <memory>
#include <iostream>

class Token;

using production_t = std::vector<std::unique_ptr<Token>>;
using AST_t = std::vector<Token>;

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

    Token();
    Token(Token&& from) = default;

    explicit Token(const Token::label label);

    explicit Token(const Token::label type,
                   const std::string capture);

    explicit Token(AST_t&& parse);
    explicit Token(production_t&& children);

    virtual ~Token(void) = default;

    void operator=(AST_t&& parse);
    const Token& operator[](int index) const;

    Token& set_optional(void);

    Token::label get_type(void) const { return t; }
    const std::string get_token(void) const { return value; }
    const std::vector<Token>& get_production(void) const { return tree; }

    static Token descent(const Token& definition, const std::string text);

    Token match(std::string::const_iterator& i,
                std::string::const_iterator& end) const;

    Token parse(std::string::const_iterator& i,
                std::string::const_iterator& end) const;

    friend std::ostream& operator<<(std::ostream& out, const Token& token);

protected:
    virtual bool is_capture(const char x [[maybe_unused]]) const;

private:
    Token::label t;

    production_t tokens;
    bool optional = false;

    AST_t tree;
    std::string value;

    static const std::array<char,4> constexpr terminal {' ', '\t', '\n', ','};

    bool is_terminal(const char x) const;

    void skip_terminal(std::string::const_iterator& i,
                       std::string::const_iterator& n) const;
};

std::ostream& operator<<(std::ostream& out, const Token& token);

class Alphabetic : public Token {
public:
    Alphabetic() : Token(Token::label::text) {}
    Alphabetic(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override {
        if (std::isalpha(x)) {
             return true;
         }

         return false;
    };
};

class Numeric : public Token {
public:
    Numeric() : Token(Token::label::number) {}
    Numeric(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override {
         if (std::isdigit(x)) {
             return true;
         }

         return false;
    };
};

class AlphaNumeric : public Token {
public:
    AlphaNumeric() : Token(Token::label::symbol) {}
    AlphaNumeric(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override {
        if (std::isalnum(x)) {
            return true;
        }

        return false;
    };
};

#endif
