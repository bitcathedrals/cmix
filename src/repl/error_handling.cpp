#include <string>
#include <iostream>

#include "repl/error_handling.h"

CmdStatus repl_ok(void) {
    std::cerr << "cmix success. Thank You!";

    return CmdStatus::ok;
}
