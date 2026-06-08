#include <sstream>
#include <regex>

#include "parse.h"

std::ostream& operator<<(std::ostream& output, const parse_t p) {
    output << p[0]
           << p[1]
           << p[2]
           << p[3]
           << p[4]
           << p[5];

    return output;
}


std::istringstream istream_from_string(const std::string input) {
    return std::istringstream(input);
}

parse_t parse_core(const std::string& input, std::regex r) {
    parse_t parse;

    if(input == "") { return parse; };

    auto words_begin = std::sregex_iterator(input.begin(),
                                            input.end(),
                                            r);
    auto words_end = std::sregex_iterator();

    auto count = std::distance(words_begin, words_end);

    if(count < 1) { return parse; };

    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        parse.push_back(match.str());
    }

    return parse;

}

parse_t parse_cli(const std::string& input) {
    return parse_core(input, std::regex("\\S+"));
}

parse_t parse_word(const char* input) {
    return parse_core(std::string(input), std::regex("[^:]+"));
}

parse_t parse_word(const std::string& input) {
    return parse_core(input, std::regex("[^:]+"));
}


// this is for variants to make a new parse_t with variable arguments.

parse_t make_parse(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3) {
    parse_t p;

    p[0] = x1;
    p[1] = x2;
    p[2] = x3;

    return p;
}

parse_t make_parse(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3,
                   const std::string& x4) {
    parse_t p;

    p[0] = x1;
    p[1] = x2;
    p[2] = x3;
    p[3] = x4;

    return p;
}
