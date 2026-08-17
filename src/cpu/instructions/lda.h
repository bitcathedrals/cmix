#ifndef CPU_INSTRUCTIONS_LDA
#define CPU_INSTRUCTIONS_LDA

#include <memory>

#include "cpu/instruction.h"

class LDA : public Instruction {
public:
    void opcode(void) const;

    virtual ~LDA() = default;

protected:
    virtual void assemble(std::string::const_iterator& begin,
                          std::string::const_iterator& end) override;

    virtual void encode(int address,
                        int index,
                        int field_lower,
                        int field_upper) override;
};

#endif
