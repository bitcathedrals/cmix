#include <string>

#include <repl/dispatch.h>
#include <parse.h>
#include <edit.h>

int main() {
    std::cerr << "Welcome to cmix." << std::endl;

    do {
        std::string input = get_input();

        parse_t parse = parse_cli(input);

        if (parse.empty()) {
            std::cerr << "cmix: no command given.";
            continue;
        }

        Command cmd = string_to_command(parse[0]);

        if (cmd == Command::unknown) {
            std::cerr << "cmix: unknown command." << std::endl;
            continue;
        }

        std::cout << "You entered: " << input << std::endl;

        if (cmd == Command::quit) {
            break;
        }

        std::cerr << "cmix: cannot handle input = "
                  << input << std::endl;
    } while(true);

    return 0;
}
