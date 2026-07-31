#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <iostream>
#include <vector>

using split_t = std::vector<std::string>;

std::ostream& operator<<(std::ostream& output, const split_t p);

std::istringstream istream_from_string(const std::string input);

std::string split_join(const split_t& split, const std::string delimiter = ",");

split_t split_cli(const std::string& input);

split_t split_path(const std::string& input);

split_t split_word(const std::string& input);

split_t make_spit(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3);

split_t make_spit(const std::string& x1,
                   const std::string& x2,
                   const std::string& x3,
                   const std::string& x4);

#endif
