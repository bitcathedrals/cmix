#include "cpu/instruction.h"

int Instruction::get_address(void) {
    return
        (operator[](static_cast<byte>(InstructionFields::address_begin)) * 100)
        + operator[](static_cast<byte>(InstructionFields::address_end));
}

byte Instruction::get_index(void) {
    return operator[](static_cast<byte>(InstructionFields::index));
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

byte Instruction::get_opcode(void) {
    return operator[](static_cast<byte>(InstructionFields::opcode));
}
