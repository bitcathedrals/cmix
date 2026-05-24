#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <vector>

using parse_t = std::vector<std::string>;

std::ostream& operator<<(std::ostream& output, const parse_t p);

std::istringstream istream_from_string(const std::string input);

parse_t parse_cli(const std::string& input);

parse_t parse_word(const std::string& input);

parse_t make_parse(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3);

parse_t make_parse(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3,
                   const std::string& x4);

#endif
