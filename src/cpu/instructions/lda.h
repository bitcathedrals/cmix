#ifndef CPU_INSTRUCTIONS_LDA
#define CPU_INSTRUCTIONS_LDA

#include <memory>

#include "cpu/word.h"
#include "mixer/parser.h"
#include "cpu/instruction.h"

class LDA : public Instruction {
public:
    void opcode(void) const;

    virtual std::unique_ptr<Instruction> assemble(std::string::const_iterator begin,
                                                  std::string::const_iterator end) const;

    virtual ~LDA() = default;

private:
    void parse_field_spec(std::string::const_iterator begin,
                          std::string::const_iterator end,
                          int& lower,
                          int& upper) const;

    std::unique_ptr<Instruction> encode(int address,
                                        int index,
                                        int field_lower,
                                        int field_upper) const;
};

#endif
