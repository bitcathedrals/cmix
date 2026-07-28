#include <sstream>
#include <regex>

#include "split.h"

std::ostream& operator<<(std::ostream& output, const split_t p) {
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

split_t parse_core(const std::string& input, std::regex r) {
    split_t parse;

    if(input == "") { return parse; };

    auto words_begin = std::sregex_iterator(input.begin(),
                                            input.end(),
                                            r);
    auto words_end = std::sregex_iterator();

    auto count = std::distance(words_begin, words_end);

    if(count < 1) { return parse; };

    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;

        if(match.str().size() < 1) {
            continue;
        }

        parse.push_back(match.str());
    }

    return parse;
}

split_t split_cli(const std::string& input) {
    return parse_core(input, std::regex("\\S+"));
}

split_t split_path(const std::string& input) {
    return parse_core(input, std::regex("[^/]+"));
}

split_t split_word(const char* input) {
    return parse_core(std::string(input), std::regex("[^:]+"));
}

split_t split_word(const std::string& input) {
    return parse_core(input, std::regex("[^:]+"));
}

// this is for variants to make a new split_t with variable arguments.

split_t make_spit(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3) {
    return split_t { x1, x2, x3 };
}

split_t make_spit(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3,
                   const std::string& x4) {

    return split_t { x1, x2, x3, x4 };
}
