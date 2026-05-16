#include <sstream>
#include <regex>

#include <parse.h>

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

parse_t parse_word_cli(const std::string& input) {
    return parse_core(input, std::regex("[^:]+"));
}
