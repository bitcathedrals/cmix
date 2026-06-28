#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H

#include "cpu/defs.h"
#include "cpu/word.h"

enum class InstructionFields : byte {
    address_begin = 1,
    address_end = 2,
    index = 3,
    field = 4,
    opcode = 5
};

class Instruction : public Word {
public:
    int get_address();

    byte get_index();

    byte get_field();

    byte get_field_lower();
    byte get_field_upper();

    byte get_opcode();
};

#endif
