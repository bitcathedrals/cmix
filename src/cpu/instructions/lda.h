#ifndef CPU_INSTRUCTIONS_LDA
#define CPU_INSTRUCTIONS_LDA

#include "mixer/parser.h"

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

    void opcode_handler(void) const {};
};

#endif
