#include <stdexcept>
#include <string>
#include <regex>

#include "repl/command.h"

CommandEntry CommandTable[CommandCount] = {
    {Command::quit, 0, "quit cmix."},
    {Command::read, 1, "read <i> = print memory at <i>"},
    {Command::write, 2, "write <i> <x> = write word at i with x,x,x,x,x"},
    {Command::help, 3, "give help on commands"}
};

CommandEntry lookup_command(const Command x) {
    for(auto i = 0; i < CommandCount; i++) {
        if (CommandTable[i].cmd == x) {
            return CommandTable[i];
        }
    }

    throw std::out_of_range("lookup_command: command not found");
};

Command string_to_command(const std::string command) {
    if(command == "q") return Command::quit;
    if(command == "?") return Command::help;

    if(command == "r") return Command::read;
    if(command == "w") return Command::write;

    return Command::unknown;
}
