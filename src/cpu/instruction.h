#ifndef CPU_INSTRUCTION_H
#define CPU_INSTRUCTION_H

#include <string>

#include "cpu/defs.h"
#include "cpu/word.h"
#include "mixer/parser.h"

enum class InstructionFields : byte {
    address_begin = 0,
    address_end = 1,
    index = 2,
    field = 3,
    opcode = 4
};

class Instruction : public Word {
public:
    int get_address();

    void set_address(int value);
    void set_address(byte upper, byte lower);
    void set_address(std::string value);

    byte get_index();

    void set_index(byte v);
    void set_index(std::string value);

    byte get_field();
    byte get_field_lower();
    byte get_field_upper();

    void set_field(byte v);
    void set_field(byte upper, byte lower);
    void set_field(std::string value);

    byte get_opcode();

    void set_opcode(byte v);
    void set_opcode(std::string value);


    void copy_subrange(byte lower, byte upper);
};

class LDA : public Instruction {
public:
//    "adr lda l r addr"

    void encode(std::string assembly) {
        production_t def;

        // address to store instruction
        def.push_back(std::make_unique<Numeric>());

        // instruction name
        def.push_back(std::make_unique<Alphabetic>());

        // field upper, lower
        def.push_back(std::make_unique<Numeric>());
        def.push_back(std::make_unique<Numeric>());

        // adr
        def.push_back(std::make_unique<Numeric>());

        Token p = Token::descent(Token(std::move(def)), assembly);
    }

};

#endif
