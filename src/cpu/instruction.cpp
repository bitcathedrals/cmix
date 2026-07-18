#include <stdexcept>
#include <vector>
#include <iterator>
#include <map>
#include <memory>
#include <string>

#include "cpu/instruction.h"
#include "mixer/parser.h"

#include "cpu/instructions/lda.h"

std::map<std::string, std::unique_ptr<Instruction>> InstructionFactory;
std::map<int, std::unique_ptr<Instruction>> InstructionTable;

Instruction::Instruction(void) : address_parser(build_address_parser()) {

}

int Instruction::get_address(void) const {
    return
        (operator[](static_cast<byte>(InstructionFields::address_begin)) * 100)
        + operator[](static_cast<byte>(InstructionFields::address_end));
}

Instruction& Instruction::set_address(int v) {
    byte upper = v / 100;
    byte lower = v % 100;

    operator[](static_cast<byte>(InstructionFields::address_begin)) = upper;
    operator[](static_cast<byte>(InstructionFields::address_end)) = lower;

    return *this;
}

Instruction& Instruction::set_address(byte upper, byte lower) {
    operator[](static_cast<byte>(InstructionFields::address_begin)) = upper;
    operator[](static_cast<byte>(InstructionFields::address_end)) = lower;

    return *this;
}

Instruction& Instruction::set_address(std::string value) {
    int v = std::stoi(value);
    set_address(v);

    return *this;
}

byte Instruction::get_index(void) const {
    return operator[](static_cast<byte>(InstructionFields::index));
}

Instruction& Instruction::set_index(byte v) {
    operator[](static_cast<byte>(InstructionFields::index)) = v;

    return *this;
}

Instruction& Instruction::set_index(std::string value) {
    operator[](static_cast<byte>(InstructionFields::index)) = std::stoi(value);

    return *this;
}

byte Instruction::get_field(void) const {
    return operator[](static_cast<byte>(InstructionFields::field));
}

byte Instruction::get_field_lower(void) const {
    return get_field() / 8;
}

byte Instruction::get_field_upper(void) const {
    return get_field() % 8;
}

Instruction& Instruction::set_field(byte v) {
    operator[](static_cast<byte>(InstructionFields::field)) = v;

    return *this;
}

Instruction& Instruction::set_field(std::string value) {
    operator[](static_cast<byte>(InstructionFields::field)) = std::stoi(value);

    return *this;
}

Instruction& Instruction::set_field(byte lower, byte upper) {
    byte v = lower * 8;
    v = v + upper;

    operator[](static_cast<byte>(InstructionFields::field)) = v;

    return *this;
}

byte Instruction::get_opcode(void) const {
    return operator[](static_cast<byte>(InstructionFields::opcode));
}

Instruction& Instruction::set_opcode(byte x) {
    operator[](static_cast<byte>(InstructionFields::opcode)) = x;

    return *this;
}

Instruction& Instruction::set_opcode(std::string value) {
    operator[](static_cast<byte>(InstructionFields::field)) = static_cast<byte>(std::stoi(value));

    return *this;
}

std::pair<int, std::unique_ptr<Instruction>> Instruction::assemble(const std::string assembly) const {
    std::string::const_iterator begin = assembly.cbegin();
    std::string::const_iterator end = assembly.cend();

    int instruction_adr = -1;

    Numeric address;
    address.match(begin, end);

    if(address.get_type() == Token::label::number && address.get_token().size() > 0) {
        instruction_adr = std::stoi(address.get_token());
    }

    Alphabetic opcode;
    opcode.match(begin, end);

    if(opcode.get_type() != Token::label::text || opcode.get_token().size() < 1) {
        throw std::invalid_argument("can't find instruction opcode in assembly: " + assembly);
    }

    return std::pair<int,std::unique_ptr<Instruction>>(instruction_adr,
                                                       InstructionFactory[opcode.get_token()]->assemble(begin, end));
}

std::unique_ptr<Instruction> Instruction::assemble(std::string::const_iterator& begin [[maybe_unused]],
                                                   std::string::const_iterator& end [[maybe_unused]]) const {
    throw std::logic_error("assemble base class virtual called");
}

std::unique_ptr<Instruction> Instruction::encode(int address [[maybe_unused]],
                                    int index [[maybe_unused]],
                                    int field_lower [[maybe_unused]],
                                    int field_upper [[maybe_unused]]) const {
    throw std::logic_error("assemble base class virtual called");
}
void Instruction::execute(void) const {
    switch(get_opcode()) {
        case static_cast<byte>(InstructionOpCodes::LDA):
            static_cast<const LDA*>(this)->opcode();
            break;

        default:
            throw std::logic_error("Instruction::execute fell off execute switch()");
    }
}

void Instruction::opcode(void) const {
    throw std::logic_error("Instruction::opcode base class method reached");
}

void Instruction::assemble_field(std::string::const_iterator& begin,
                                 std::string::const_iterator& end,

                                 int& lower,
                                 int& upper) const {

    Numeric left_match;
    Token left_token = left_match.match(begin, end);

    if(left_token.get_type() != Token::label::number) {
        throw std::invalid_argument("invalid assembly: left field missing or mangled.");
    }

    Punctuation field_splitter;
    Token split = field_splitter.match(begin,end);

    if(split.get_type() != Token::label::special) {
        throw std::invalid_argument("invalid assembly: middle \":\" split missing");
    }

    Numeric right_match;
    Token right_token = right_match.match(begin, end);

    if(right_token.get_type() != Token::label::number) {
        throw std::invalid_argument("invalid assembly: right numeric missing or mangled.");
    }

    lower = std::stoi(left_token.get_token());
    upper = std::stoi(right_token.get_token());
}

std::unique_ptr<Token> Instruction::build_address_parser(void) {
    production_t def;

    auto sign = std::make_unique<NumSign>();
    sign->set_optional()->set_name("Address sign");

    def.push_back(std::move(sign));

    auto address = std::make_unique<Numeric>();
    address->set_name("Address numeric");

    def.push_back(std::move(address));

    return std::make_unique<Token>(std::move(def));
}

void Instruction::assemble_address(std::string::const_iterator& begin,
                                   std::string::const_iterator& end,

                                   int& address,
                                   int& index,
                                   int& field_lower,
                                   int& field_upper) const {
    address = 0;
    index = 0;

    field_lower = 0;
    field_upper = 5;

    Numeric adr_match;
    adr_match.match(begin, end);

    if(adr_match.get_type() != Token::label::number) {
        throw std::invalid_argument("invalid assembly: address missing or mangled.");
    }

    address = std::stoi(adr_match.get_token());

    Punctuation comma_or_lparen;
    comma_or_lparen.match(begin,end);

    if(comma_or_lparen.get_type() == Token::label::nothing) {
        encode(address, index, field_lower, field_upper);
        return;
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
    }
    else if(comma_or_lparen.get_token() == "(") {
        assemble_field(begin, end, field_lower, field_upper);
    }
    else {
        throw std::invalid_argument("invalid assembly: expected ( or ,");
    }
}
