#include <string>

#include <repl/dispatch.h>
#include <parse.h>
#include <edit.h>

#include <repl/dispatch.h>

#include <gtest/gtest.h>

void parser_minimal_descent(void);
void parser_minimal_AST(void);

int all_tests(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

bool run_debug(parse_t cli, int argc, char**argv) {
    std::string command = cli[0];

    if(command == "/help") {
        std::cerr << "[help]" << std::endl
                  << "/test-all = run all tests" << std::endl
                  << "/parser-ast" << std::endl
                  << "/parser-minimal = bare descent example" << std::endl;
        return true;
    }

    if(command == "/test-all") {
        all_tests(argc, argv);
        return true;
    }

    if(command == "/parser-minimal") {
        parser_minimal_descent();
        return true;
    }

    if(command == "/parser-ast") {
        parser_minimal_AST();
        return true;
    }

    return false;
}

int main(int argc, char**argv) {
    std::cerr << "Welcome to cmix Debugging, down the rabbit hole we go!" << std::endl;

    do {
        std::string input = get_input();

        parse_t parse = parse_cli(input);

        if (parse.empty()) {
            std::cerr << "cmix: no command given.";
            continue;
        }

        if (run_debug(parse, argc, argv)) {
            continue;
        }

        CmdStatus status = run_command(parse);

        std::cerr << cmd_string(parse) << " command terminated with status: "
                  << status_string(status) << std::endl;
    } while(true);

    return 0;
}
