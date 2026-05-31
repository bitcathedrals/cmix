#include <string>

#include <repl/dispatch.h>
#include <parse.h>
#include <edit.h>

#include <repl/dispatch.h>

int main() {
    std::cerr << "Welcome to cmix Debugging, down the rabbit hole we go!" << std::endl;

    do {
        std::string input = get_input();

        parse_t parse = parse_cli(input);

        if (parse.empty()) {
            std::cerr << "cmix: no command given.";
            continue;
        }

        CmdStatus status = run_command(parse);

        std::cerr << cmd_string(parse) << " command terminated with status: "
                  << status_string(status) << std::endl;
    } while(true);

    return 0;
}
