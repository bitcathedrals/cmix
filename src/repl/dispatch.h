#ifndef REPL_DISPATCH_H
#define REPL_DISPATCH_H

#include <string>
#include <vector>

enum Commands {
    quit,

    peek,
    poke,

    unknown
};

Commands string_to_command(const std::string command);

using parse_t = std::vector<std::string>;

parse_t parse_input(const char* input_cstring);

#endif
