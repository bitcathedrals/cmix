#include <stdexcept>
#include <string>
#include <regex>

#include "repl/command.h"

CommandEntry CommandTable[CommandCount] = {
    {Command::quit, 1, "quit cmix."},
    {Command::read, 1, "read <i> = print memory at <i>"},
    {Command::write, 7, "write <i> <x> = write word at i with x,x,x,x,x"}
};

CommandEntry lookup_command(const Command x) {
    for(auto i = 0; i <CommandCount; i++) {
        if (CommandTable[i].cmd == x) {
            return CommandTable[i];
        }
    }

    throw std::out_of_range("lookup_command: command not found");
};

Command string_to_command(const std::string command) {
    if(command == "quit") return Command::quit;

    if(command == "r") return Command::read;
    if(command == "w") return Command::write;

    return Command::unknown;
}
