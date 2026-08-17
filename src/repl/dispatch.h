#ifndef REPL_DISPATCH_H
#define REPL_DISPATCH_H

#include <string>

#include "split.h"
#include "repl/command.h"

//
// these are exit codes.
//

enum class CmdStatus {
    ok = 0,

    general_failure = -1,
    bad_input = -2,
    bad_value = -3,
    out_of_range = -4,
};

std::string status_string(const CmdStatus s);

CmdStatus run_command(split_t p);

#endif
