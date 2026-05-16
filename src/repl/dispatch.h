#ifndef REPL_DISPATCH_H
#define REPL_DISPATCH_H

#include <string>
#include <vector>

#include <parse.h>

enum class Command {
    quit = 0,

    read = 1,
    write = 2,

    unknown = 32
};

static inline const char CommandCount = 4;

struct CommandEntry {
    Command cmd;
    char word_count;
    std::string help;
};

extern CommandEntry CommandTable[CommandCount];

CommandEntry lookup_command(const Command x);

Command string_to_command(const std::string command);

#endif
