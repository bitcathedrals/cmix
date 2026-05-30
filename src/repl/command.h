#ifndef REPL_COMMAND_H
#define REPL_COMMAND_H

#include <string>
#include <vector>

enum class Command {
    quit = 0,

    read = 1,
    write = 2,

    unknown = 32
};

const inline constexpr char CommandCount = 4;

struct CommandEntry {
    Command cmd;
    char word_count;
    std::string help;
};

extern CommandEntry CommandTable[CommandCount];

CommandEntry lookup_command(const Command x);

Command string_to_command(const std::string command);

#endif
