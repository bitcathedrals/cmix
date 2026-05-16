#ifndef PARSE_H
#define PARSE_H

#include <iostream>

using parse_t = std::vector<std::string>;

std::istringstream istream_from_string(const std::string input);

parse_t parse_cli(const std::string& input);

parse_t parse_word_cli(const std::string& input);

#endif
