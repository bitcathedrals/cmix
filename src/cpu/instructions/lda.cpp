#include "cpu/instructions/lda.h"
#include "cpu/cpu.h"

struct insert_table {
    insert_table() {
        InstructionFactory["LDA"] = std::make_unique<LDA>();
        InstructionTable[static_cast<int>(InstructionOpCodes::LDA)] = std::make_unique<LDA>();
    }
};

static insert_table insert;

void LDA::opcode(void) const {
    insert_subrange_from_to(CPU.memory[get_address() + get_index()],
                            CPU.A,
                            get_field_lower(),
                            get_field_upper());
}

std::unique_ptr<Instruction> LDA::encode(int address,
                                         int index,
                                         int field_lower,
                                         int field_upper) const {
    auto encode = std::make_unique<LDA>();

    encode->set_opcode(8)
        .set_address(address)
        .set_index(static_cast<byte>(index))
        .set_field(static_cast<byte>(field_lower),
                   static_cast<byte>(field_upper));

    return encode;
}

std::unique_ptr<Instruction> LDA::assemble(std::string::const_iterator& begin,
                                           std::string::const_iterator& end) const {

    int address = 0;
    int index = 0;

    int field_lower = 0;
    int field_upper = 5;

    assemble_address(begin,
                     end,
                     address,
                     index,
                     field_lower,
                     field_upper);

    return encode(address, index, field_lower, field_upper);
}
