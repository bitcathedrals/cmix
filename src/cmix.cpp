#include <string>
#include <edit.h>

#include "repl/dispatch.h"
#include "split.h"

int main() {
    std::cerr << "Welcome to cmix." << std::endl;

    do {
        std::string input = get_input();

        split_t parse = split_cli(input);

        if (parse.empty()) {
            std::cerr << "cmix: no command given.";
            continue;
        }

        Command cmd = string_to_command(parse[0]);

        if (cmd == Command::unknown) {
            std::cerr << "cmix: unknown command: "
                      << parse
                      << std::endl;
            continue;
        }

        if (cmd == Command::quit) {
            return 0;
        }

        CmdStatus status = run_command(parse);

        std::cerr << parse
                  << " command terminated with status: "
                  << status_string(status) << std::endl;
    } while(true);

    return -1;
}
