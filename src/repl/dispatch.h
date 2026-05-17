#ifndef REPL_DISPATCH
#define REPL_DISPATCH

#include <parse.h>
#include <repl/command.h>

//
// these are exit codes.
//

enum class Cmd_Status {
    general_failure = -1,
    bad_input = -2,
    bad_value = -3,
    out_of_range = -4,

    ok = -24
};

Cmd_Status run_command(const parse_t p);

#endif
