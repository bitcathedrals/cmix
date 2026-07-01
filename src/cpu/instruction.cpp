#include <vector>
#include <iterator>

#include "cpu/instruction.h"

int Instruction::get_address(void) {
    return
        (operator[](static_cast<byte>(InstructionFields::address_begin)) * 100)
        + operator[](static_cast<byte>(InstructionFields::address_end));
}

void Instruction::set_address(int v) {
    byte upper = v / 100;
    byte lower = v % 100;

    operator[](static_cast<byte>(InstructionFields::address_begin)) = upper;
    operator[](static_cast<byte>(InstructionFields::address_end)) = lower;
}

void Instruction::set_address(byte upper, byte lower) {
    operator[](static_cast<byte>(InstructionFields::address_begin)) = upper;
    operator[](static_cast<byte>(InstructionFields::address_end)) = lower;
}

void Instruction::set_address(std::string value) {
    int v = std::stoi(value);
    set_address(v);
}

byte Instruction::get_index(void) {
    return operator[](static_cast<byte>(InstructionFields::index));
}

void Instruction::set_index(byte v) {
    operator[](static_cast<byte>(InstructionFields::index)) = v;
}

void Instruction::set_index(std::string value) {
    operator[](static_cast<byte>(InstructionFields::index)) = std::stoi(value);
}

byte Instruction::get_field(void) {
    return operator[](static_cast<byte>(InstructionFields::field));
}

byte Instruction::get_field_lower(void) {
    return get_field() % 8;
}

byte Instruction::get_field_upper(void) {
    return get_field() / 8;
}

void Instruction::set_field(byte v) {
    operator[](static_cast<byte>(InstructionFields::field)) = v;
}

void Instruction::set_field(std::string value) {
    operator[](static_cast<byte>(InstructionFields::field)) = std::stoi(value);
}

void Instruction::set_field(byte upper, byte lower) {
    byte v = upper * 8;
    v = v + lower;

    operator[](static_cast<byte>(InstructionFields::field)) = v;
}

byte Instruction::get_opcode(void) {
    return operator[](static_cast<byte>(InstructionFields::opcode));
}

void Instruction::set_opcode(byte x) {
    operator[](static_cast<byte>(InstructionFields::opcode)) = x;
}

void Instruction::set_opcode(std::string value) {
    operator[](static_cast<byte>(InstructionFields::field)) = static_cast<byte>(std::stoi(value));
}
