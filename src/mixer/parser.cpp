#include <format>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "mixer/parser.h"

Token::Token() : t {Token::label::nothing}  {}

Token::Token(const Token& other) : name(other.name),
                                   t(other.t),
                                   optional(other.optional),
                                   tree(other.tree),
                                   value(other.value) {

    for (const auto& token_ptr : other.tokens) {
        if (token_ptr) {
            tokens.push_back(token_ptr->clone());
        } else {
            tokens.push_back(nullptr);
        }
    }
}

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

const Token& Token::operator[](size_t index) const {
    if(index >= tree.size()) {
        throw std::out_of_range(std::format("id: \"{}\" out of range Token& [] index = {} in tree.size() {}",
                                            get_name(),
                                            index,
                                            tree.size()));
    }

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

const std::unique_ptr<Token> Token::walk(const Token& node, split_t path) {
    if(path.empty()) {
        return nullptr;
    }

    for(size_t i = 0; i < node.tree.size(); i++) {
        if(node.tree[i].get_name() == path.front()) {
            if(path.size() == 1) {
                return node.tree[i].clone();
            }

            path.erase(path.begin());
            return walk(node.tree[i], path);
        }
    }

    return nullptr;
}

const std::unique_ptr<Token> Token::walk(const std::string path) {
    split_t split = split_path(path);

    if(split.size() < 1) {
        return std::make_unique<Token>(*this);
    }

    return walk(*this, split);
}


bool Token::is_capture(const char x [[maybe_unused]]) const {
    throw std::logic_error("is_capture should never be called in the Token base class");
    return false;
};

bool Token::is_terminal(const char x) const {
    for(const auto& t : terminal) {
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

static void parse_fail_throw(const AST_t& parse,
                             const Token& token,

                             const std::string::const_iterator& backtrack,
                             const std::string::const_iterator& begin) {
    std::string diagnostic;

    std::string type((token.get_type() == Token::label::node) ? "parse" : "match");

    if(parse.size() < 1) {
        diagnostic = "<nothing emitted>";
    }
    else {
        const Token& last = parse.back();
        diagnostic = last.get_token();
    }

    throw std::invalid_argument(std::format("{} {} failed {} characters after checkpoint \"{}\" over: \"{}\" ",
                                            type,
                                            token.get_name(),
                                            std::distance(backtrack, begin),
                                            diagnostic,
                                           *begin));
}

bool Token::rest_are_optional(const size_t i) const {
    for(auto y = i + 1; y < tokens.size(); y++) {
        if(!tokens[y]->get_optional()) {
            return false;
        }
    }

    return true;
}

Token Token::parse(std::string::const_iterator& begin,
                   std::string::const_iterator& end) const {
    AST_t parse;

    auto backtrack = begin;

    for(size_t i = 0; i < tokens.size(); i++) {
        if(begin == end) {
            if(rest_are_optional(i)) {
                break;
            }

            return Token { Token::label::rollback };
        }

        if (tokens[i]->get_type() == Token::label::node) {
            auto ascent = tokens[i]->parse(begin, end);

            switch(ascent.get_type()) {
                using enum Token::label;

                case rollback:
                    if(tokens[i]->get_optional()) {
                        begin = backtrack;
                        continue;
                    }

                    return Token { Token::label::rollback };

                    break;

                case nothing:
                    if(tokens[i]->get_optional()) {
                        begin = backtrack;
                        continue;
                    }

                    parse_fail_throw(parse, *tokens[i], backtrack, begin);

                    break;

                default:
                    backtrack = begin;

                    parse.push_back(std::move(ascent));
                    parse.back().set_name(tokens[i]->get_name());

                    continue;
            };
        }

        auto ascent = tokens[i]->match(begin, end);

        if(ascent.get_type() == Token::label::nothing) {
            if(tokens[i]->get_optional()) {
                begin = backtrack;
                continue;
            }

            parse_fail_throw(parse, *tokens[i], backtrack, begin);
        }

        backtrack = begin;

        parse.push_back(std::move(ascent));
        parse.back().set_name(tokens[i]->get_name());
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
    } catch(const std::invalid_argument& exception) {
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
    } catch(const std::invalid_argument& exception) {
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
        case Token::label::rollback:
            label = "rollback";
            break;
    }

    out << " label = " << label
        << " value = " << token.value;

    return out;
}

void Token::graph_header(std::ostream& output) {
    output << "digraph { "
           << std::endl << "    rank=TB" << std::endl;
}

void Token::graph_footer(std::ostream& output) {
    output << "}" << std::endl;
}

void Token::graph_define(std::string label, std::ostream& output) {
    output << label << " [label = \"" << label << "\"]" << std::endl;
}

void Token::graph_node(std::ostream& output) {
    std::string name = get_name();
    if (get_optional()) {
        name = name + " :optional";
    }

    graph_define(name, output);

    for(size_t i = 0; i < tokens.size(); i++) {
        output << "    " << tokens[i]->get_name() <<  " -> " <<   get_name() << std::endl;
        tokens[i]->graph_node(output);
    }
}

void Token::graph_ast_internal(std::ostream& output) {
    std::string name = get_name();

    graph_define(name, output);

    for(size_t i = 0; i < tree.size(); i++) {
        output << "    " << tree[i].get_name() <<  " -> " <<   get_name() << std::endl;
        tree[i].graph_ast_internal(output);
    }
}

void Token::graph(std::ostream& output) {
    graph_header(output);

    graph_node(output);

    graph_footer(output);
}

void Token::graph_ast(std::ostream& output) {
    graph_header(output);

    graph_ast_internal(output);

    graph_footer(output);
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

 bool Special::is_capture(const char x) const {
     if (std::ispunct(x)) {
         return true;
     }

     return false;
 }

