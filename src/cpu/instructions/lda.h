#ifndef CPU_INSTRUCTIONS_LDA
#define CPU_INSTRUCTIONS_LDA

#include <memory>

#include "cpu/word.h"
#include "mixer/parser.h"
#include "cpu/instruction.h"

class LDA : public Instruction {
public:
    void opcode(void) const;

    virtual ~LDA() = default;


 protected:
    virtual std::unique_ptr<Instruction> assemble(std::string::const_iterator& begin,
                                                  std::string::const_iterator& end) const override;

    virtual std::unique_ptr<Instruction> encode(int address,
                                                int index,
                                                int field_lower,
                                                int field_upper) const override;
};

#endif
