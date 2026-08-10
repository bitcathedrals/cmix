#include "cpu/instructions/lda.h"
#include "cpu/cpu.h"

#include "mixer/address.h"
#include "cpu/instruction.h"

struct CompileUnit {
public:
    const Token parser;

    CompileUnit() : parser(*build_address_parser()) {
        InstructionFactory::getInstance().insert("LDA", LDA {});
//        InstructionTable[static_cast<int>(InstructionOpCodes::LDA)] = std::make_unique<LDA>();
    }
};

static CompileUnit unit;

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

    encode->set_opcode(static_cast<byte>(InstructionOpCodes::LDA))
        .set_address(address)
        .set_index(static_cast<byte>(index))
        .set_field(static_cast<byte>(field_lower),
                   static_cast<byte>(field_upper));

    return encode;
}

std::unique_ptr<Instruction> LDA::assemble(std::string::const_iterator& begin,
                                           std::string::const_iterator& end) const {

    auto parse = Token::descent(unit.parser, std::string(begin, end));

    auto adr_token = parse.walk("address");
    auto adr = std::stoi(adr_token->get_token());

    auto index_token = parse.walk("index_field/idx_index");
    int index = 0;

    if(index_token->get_type() == Token::label::number) {
        index = std::stoi(index_token->get_token());
    }

    auto field_left = parse.walk("index_field/idx_field/field_left_number");
    auto field_right = parse.walk("index_field/idx_field/field_right_number");

    int left=0;
    int right=5;

    if(field_left != nullptr && field_right != nullptr) {
        left = std::stoi(field_left->get_token());
        right = std::stoi(field_right->get_token());
    }

    return encode(adr, index, left, right);
}
