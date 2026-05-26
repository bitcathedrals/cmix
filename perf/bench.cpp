#include <string>

#include <repl/dispatch.h>
#include <parse.h>
#include <edit.h>

int main(int argc, char* argv[]) {
    std::cerr << "cmix benchmarking." << std::endl;

    std::cerr << "Command-line arguments:";

    for(auto count = 0; count < argc; count++) {
        if (count < 1) {
            continue;
        }

        std::cerr << argv[count];
    }

    std::cerr << std::endl;

    return 0;
}
