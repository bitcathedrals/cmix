#include <string>
#include <memory>
#include <iostream>

#include "mixer/parser.h"
#include "mixer/address.h"

int main(const int argc, const char* argv[]) {
    if(argc < 2) {
        std::cerr << "address_comma_index" << std::endl;
        std::cerr << "address" << std::endl;
        return 0;
    }

    std::string address_comma_index("address_comma_index");
    std::string address("address");

    if(address_comma_index == argv[1]) {
        build_comma_index_parser()->graph(std::cout);
        return 0;
    }
    else if(address == argv[1]) {
        build_address_parser()->graph(std::cout);
        return 0;
    }

    std::cerr << "util/graph: no command found for: " << argv[1] << std::endl;
    return 1;
}
