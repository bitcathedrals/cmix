#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu/defs.h"

static constexpr byte address_begin = 0;
static constexpr byte address_end = 1;
static constexpr byte index = 2;
static constexpr byte field = 3;
static constexpr byte opcode = 4;

enum opcodes {
    LDA = 8,
    STA = 24,
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    ENTA = 48,
    ENTX = 55
};

class instruction : public word {
public:
    const String name("LDA");


};

#endif
