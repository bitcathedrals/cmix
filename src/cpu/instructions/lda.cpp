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

    encode->set_opcode(8);

    encode->set_address(address);

    encode->set_index(static_cast<byte>(index));

    encode->set_field(static_cast<byte>(field_lower),
                      static_cast<byte>(field_upper));

    return encode;
}

void LDA::parse_field_spec(std::string::const_iterator begin,
                           std::string::const_iterator end,
                           int& lower,
                           int& upper) const {

    Numeric left_match;
    left_match.match(begin, end);

    if(left_match.get_type() != Token::label::number) {
        throw std::invalid_argument("invalid assembly: left field missing or mangled.");
    }

    Punctuation field_splitter;
    field_splitter.match(begin,end);

    if(field_splitter.get_type() != Token::label::special) {
        throw std::invalid_argument("invalid assembly: middle \":\" split missing");
    }

    Numeric right_match;
    right_match.match(begin, end);

    if(right_match.get_type() != Token::label::number) {
        throw std::invalid_argument("invalid assembly: right numeric missing or mangled.");
    }

    lower = std::stoi(left_match.get_token());
    upper = std::stoi(right_match.get_token());
}

std::unique_ptr<Instruction> LDA::assemble(std::string::const_iterator begin,
                                           std::string::const_iterator end) const {
    int address = 0;
    int index = 0;

    int field_lower = 0;
    int field_upper = 5;

    Numeric adr_match;
    adr_match.match(begin, end);

    if(adr_match.get_type() != Token::label::number) {
        throw std::invalid_argument("invalid assembly: address missing or mangled.");
    }

    address = std::stoi(adr_match.get_token());

    Punctuation comma_or_lparen;
    comma_or_lparen.match(begin,end);

    if(comma_or_lparen.get_type() == Token::label::nothing) {
        return encode(address, index, field_lower, field_upper);
    }

    if(comma_or_lparen.get_type() != Token::label::special) {
        throw std::invalid_argument("invalid assembly: after address is not: ,(");
    }

    if(comma_or_lparen.get_token() == ",") {
        Numeric index_value;
        index_value.match(begin,end);

        if(index_value.get_type() != Token::label::number) {
            throw std::invalid_argument("invalid assembly: after comma an index value is required");
        }

        index = std::stoi(index_value.get_token());

        parse_field_spec(begin,end,field_lower,field_upper);
    }
    else if(comma_or_lparen.get_token() == "(") {
        parse_field_spec(begin, end, field_lower, field_upper);
    }
    else {
        throw std::invalid_argument("invalid assembly: expected ( or ,");
    }

    return encode(address, index, field_lower, field_upper);
}
