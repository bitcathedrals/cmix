#include <gtest/gtest.h>

#include "cpu/instruction.h"

TEST(InstructionBasic, GetAddress) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::address_begin)] = 12;
    x[static_cast<byte>(InstructionFields::address_end)] = 42;

    EXPECT_EQ(x.get_address(), 1242);
};

TEST(InstructionBasic, SetAddressInt) {
    Instruction x;

    x.set_address(1242);

    EXPECT_EQ(x[static_cast<byte>(InstructionFields::address_begin)], 12);
    EXPECT_EQ(x[static_cast<byte>(InstructionFields::address_end)], 42);

    EXPECT_EQ(x.get_address(), 1242);
};

TEST(InstructionBasic, SetAddressUpperLower) {
    Instruction x;

    x.set_address(12, 42);

    EXPECT_EQ(x[static_cast<byte>(InstructionFields::address_begin)], 12);
    EXPECT_EQ(x[static_cast<byte>(InstructionFields::address_end)], 42);

    EXPECT_EQ(x.get_address(), 1242);
};

TEST(InstructionBasic, SetAddressString) {
    Instruction x;

    x.set_address("1242");

    EXPECT_EQ(x[static_cast<byte>(InstructionFields::address_begin)], 12);
    EXPECT_EQ(x[static_cast<byte>(InstructionFields::address_end)], 42);

    EXPECT_EQ(x.get_address(), 1242);
};

TEST(InstructionBasic, GetIndex) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::index)] = 12;

    EXPECT_EQ(x.get_index(), 12);
}

TEST(InstructionBasic, SetIndexInt) {
    Instruction x;

    x.set_index(42);

    EXPECT_EQ(x.get_index(), 42);
}

TEST(InstructionBasic, SetIndexString) {
    Instruction x;

    x.set_index("42");

    EXPECT_EQ(x.get_index(), 42);
}


TEST(InstructionBasic, GetField) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::field)] = 22;

    EXPECT_EQ(x.get_field(), 22);
}

TEST(InstructionBasic, GetFieldLowerAndUpper) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::field)] = 13;

    EXPECT_EQ(x.get_field_lower(), 1);
    EXPECT_EQ(x.get_field_upper(), 5);
}


TEST(InstructionBasic, SetFieldByte) {
    Instruction x;

    x.set_field(11);

    EXPECT_EQ(x.get_field_lower(), 1);
    EXPECT_EQ(x.get_field_upper(), 3);
}

TEST(InstructionBasic, SetFieldString) {
    Instruction x;

    x.set_field("13");

    EXPECT_EQ(x.get_field_lower(), 1);
    EXPECT_EQ(x.get_field_upper(), 5);
}

TEST(InstructionBasic, SetOpcode) {
    Instruction x;

    x.set_opcode(42);

    EXPECT_EQ(x.get_opcode(), 42);
}

TEST(InstructionBasic, GetOpcode) {
    Instruction x;

    x.set_opcode(42);

    EXPECT_EQ(x.get_opcode(), 42);
}
