#include <string>
#include <iostream>

#include "edit.h"

int main() {
    std::cout << "Welcome to cmix. " << std::endl;

    std::string input = get_input();
    std::cout << "You entered: " << input << std::endl;
    return 0;
}
