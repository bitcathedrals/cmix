#include <stdexcept>
#include <vector>
#include <iterator>
#include <map>

#include "cpu/instruction.h"
#include "mixer/address.h"

#include "toolbox.h"

#include "cpu/instructions/lda.h"

std::shared_ptr<Instruction> InstructionFactory::insert(const std::string key, Instruction& instruction) {
    table[key] = std::make_shared<Instruction>(instruction);
    return table[key];
}

std::shared_ptr<Instruction> InstructionFactory::operator[](const std::string key) {
    return table[key];
}

class InstructionTable : public Singleton<InstructionTable> {
    friend class Singleton<InstructionTable>;

private:
    InstructionTable(void) = default;
};

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

void Instruction::assemble(const std::string assembly) {
    std::string::const_iterator begin = assembly.cbegin();
    std::string::const_iterator end = assembly.cend();

    Alphabetic opcode;
    opcode.match(begin, end);

    if(opcode.get_type() != Token::label::text || opcode.get_token().size() < 1) {
        throw std::invalid_argument("can't find instruction opcode in assembly: " + assembly);
    }

    InstructionFactory::getInstance()[opcode.get_token()]->assemble(begin, end);
}

void Instruction::assemble(std::string::const_iterator& begin [[maybe_unused]],
                           std::string::const_iterator& end [[maybe_unused]]) {
    throw std::logic_error("assemble base class virtual called");
}

void Instruction::encode(int address [[maybe_unused]],
                         int index [[maybe_unused]],
                         int field_lower [[maybe_unused]],
 int field_upper [[maybe_unused]])  {
    throw std::logic_error("assemble base class virtual called");
}

void Instruction::execute(void) const {
    switch(get_opcode()) {
        case static_cast<byte>(InstructionOpCodes::LDA):
            static_cast<const Instruction*>(this)-> opcode();
            break;

        default:
            throw std::logic_error("Instruction::execute fell off execute switch()");
    }
}

void Instruction::opcode(void) const {
    throw std::logic_error("Instruction::opcode base class method reached");
}
