#include <stdexcept>
#include <vector>
#include <iterator>
#include <map>
#include <memory>

#include "cpu/instruction.h"
#include "mixer/parser.h"

#include "cpu/instructions/lda.h"

std::map<std::string, std::unique_ptr<Instruction>> InstructionFactory;
std::map<int, std::unique_ptr<Instruction>> InstructionTable;

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


std::unique_ptr<Instruction> Instruction::assemble(std::string::const_iterator begin [[maybe_unused]],
                                                   std::string::const_iterator end [[maybe_unused]]) const {
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
