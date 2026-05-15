#include <repl/dispatch.h>

#include <string>
#include <regex>

// foo = CommandEntry(Command::quit, 1, "foo");

CommandEntry CommandTable[CommandCount] = {
    {Command::quit, 1, "quit cmix."},
    {Command::read, 1, "read <i> = print memory at <i>"},
    {Command::write, 7, "write <i> <x> = write word at i with x,x,x,x,x"}
};

Command string_to_command(const std::string command) {
    if(command == "quit") return Command::quit;

    if(command == "read") return Command::read;
    if(command == "write") return Command::write;

    return Command::unknown;
}

parse_t parse_input(const char* input_cstring) {
    parse_t parse;

    if(nullptr == input_cstring) { return parse; };

    std::string input(input_cstring);
    std::regex non_white_space("\\S+");

    auto words_begin = std::sregex_iterator(input.begin(),
                                            input.end(),
                                            non_white_space);
    auto words_end = std::sregex_iterator();

    auto count = std::distance(words_begin, words_end);

    if(count < 1) { return parse; };

    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        parse.push_back(match.str());
    }

    return parse;
}
