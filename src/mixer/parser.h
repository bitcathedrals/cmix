#ifndef MIXER_PARSER_H
#define MIXER_PARSER_H

#include <array>
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
        number = 0,
        symbol = 1,
        text = 2,
        special = 3,

        node = 4,

        nothing = 5,
        error = 6,
        end = 7
    };

    Token();
    Token(Token&& from) = default;

    explicit Token(const Token::label label);

    explicit Token(const Token::label type,
                   const std::string capture);

    explicit Token(AST_t&& parse);
    explicit Token(production_t&& children);

    Token(const Token& t) = default;

    virtual ~Token(void) = default;

    void operator=(AST_t&& parse);

    int size(void) const { return tree.size(); }
    const Token& operator[](size_t index) const;

    Token* set_name(const std::string name);
    Token* set_optional(void);

    std::string get_name(void) const;
    bool get_optional(void) const { return optional; };
    Token::label get_type(void) const { return t; }
    const std::string get_token(void) const;
    const std::vector<Token>& get_production(void) const { return tree; }

    static Token descent(const Token& definition, const std::string text);
    static Token descent(const std::unique_ptr<const Token> definition, const std::string text);

    Token match(std::string::const_iterator& i,
                std::string::const_iterator& end) const;

    Token parse(std::string::const_iterator& i,
                std::string::const_iterator& end) const;

    friend std::ostream& operator<<(std::ostream& out, const Token& token);

    void graph_tree(std::ostream& out);

protected:
    virtual bool is_capture(const char x [[maybe_unused]]) const;

private:
    std::string name;

    Token::label t;

    production_t tokens;
    bool optional = false;

    AST_t tree;
    std::string value;

    static constexpr std::array<char, 4> terminal {' ', '\t', '\n', ','};

    bool is_terminal(const char x) const;

    void skip_terminal(std::string::const_iterator& i,
                       std::string::const_iterator& n) const;

    void graph_header(std::ostream& output);
    void graph_footer(std::ostream& output);

    void graph_define(std::string label, std::ostream& output);
    void graph_node(std::string parent, std::ostream& output);
};

std::ostream& operator<<(std::ostream& out, const Token& token);

class Alphabetic : public Token {
public:
    Alphabetic() : Token(Token::label::text) {}
    Alphabetic(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override;
};

class NumSign : public Token {
public:
    NumSign() : Token(Token::label::special) {}
    NumSign(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override;
};

class Numeric : public Token {
public:
    Numeric() : Token(Token::label::number) {}
    Numeric(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override;
};

class AlphaNumeric : public Token {
public:
    AlphaNumeric() : Token(Token::label::symbol) {}
    AlphaNumeric(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override;
};

class Special : public Token {
public:
    Special() : Token(Token::label::special) {}
    Special(const Token::label label) : Token(label) {}

private:
    virtual bool is_capture(const char x) const override;
};

#endif
