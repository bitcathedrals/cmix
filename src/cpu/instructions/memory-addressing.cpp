#include "cpu/instructions/lda.h"
#include "cpu/cpu.h"

#include "mixer/address.h"
#include "cpu/instruction.h"

LDA test_monkey;

struct CompileUnit {
public:
    const Token parser;

    CompileUnit() : parser(*build_address_parser()) {
        InstructionFactory::getInstance().insert("LDA", test_monkey);
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

void LDA::encode(int address,
                 int index,
                 int field_lower,
                 int field_upper) {
    set_opcode(static_cast<byte>(InstructionOpCodes::LDA))
        .set_address(address)
        .set_index(static_cast<byte>(index))
        .set_field(static_cast<byte>(field_lower),
                   static_cast<byte>(field_upper));
}

void LDA::assemble(std::string::const_iterator& begin,
                   std::string::const_iterator& end) {

    auto parse = Token::descent(unit.parser, std::string(begin, end));

    auto adr_token = parse.walk("address");
    auto adr = std::stoi(adr_token->get_token());

    auto index_token = parse.walk("index_field/idx_index");
    int index = 0;

    if(index_token != nullptr && index_token->get_type() == Token::label::number) {
        index = std::stoi(index_token->get_token());
    }

    int left=0;
    auto field_left = parse.walk("index_field/idx_field/field_left_number");

    if(field_left != nullptr && field_left->get_type() == Token::label::number) {
        left = std::stoi(field_left->get_token());
    }

    auto field_right = parse.walk("index_field/idx_field/field_right_number");
    int right=5;

    if(field_right != nullptr && field_right->get_type() == Token::label::number) {
        right = std::stoi(field_right->get_token());
    }

    encode(adr, index, left, right);
}
