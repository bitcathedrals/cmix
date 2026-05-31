#include <string>
#include <iostream>

#include <editline/readline.h>

static const char* prompt_string = "cmix> ";

std::string get_input() {
    std::string result;

    char* input = nullptr;

    // Loop continuously to read user input
    while ((input = readline(prompt_string)) != NULL) {
        if (input[0] != '\0') {
            add_history(input);

            result = input;

            free(input);

            break;
        }

        std::cerr << "cmix: error, try again." << std::endl;
    }

    return result;
}
