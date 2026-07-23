#include <string>
#include <memory>
#include <iostream>

#include "mixer/parser.h"
#include "mixer/address.h"

int main(int argc, const char* argv[]) {
    std::string address_comma_index("address_comma_index");

    if(address_comma_index == argv[1]) {
        build_comma_index_parser().graph_tree(std::cout);
    }
}
