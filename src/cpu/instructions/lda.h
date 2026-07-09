#ifndef CPU_INSTRUCTIONS_LDA
#define CPU_INSTRUCTIONS_LDA

#include "cpu/word.h"
#include "mixer/parser.h"

class LDA : public Instruction {
public:
//    "adr lda l r addr"

    // void assemble(std::string assembly) {
    //     production_t def;

    //     // address to store instruction
    //     def.push_back(std::make_unique<Numeric>());

    //     // instruction name
    //     def.push_back(std::make_unique<Alphabetic>());

    //     // field upper, lower
    //     def.push_back(std::make_unique<Numeric>());
    //     def.push_back(std::make_unique<Numeric>());

    //     // adr
    //     def.push_back(std::make_unique<Numeric>());

    //     Token p = Token::descent(Token(std::move(def)), assembly);
    // }

    Word assemble(const std::string assembly) const;

    void opcode_handler(void) const {};
};

Word LDA::assemble(const std::string assembly [[maybe_unused]]) const {
    production_t definition;

    // instruction name

    definition.push_back(std::make_unique<Alphabetic>());

    Word rvalue {1,2,3,4,5};

    return rvalue;
}

#endif
