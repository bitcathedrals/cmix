#include <gtest/gtest.h>

#include "cpu/instruction.h"

TEST(InstructionBasic, GetAddress) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::address_begin)] = 12;
    x[static_cast<byte>(InstructionFields::address_end)] = 42;

    EXPECT_EQ(x.get_address(), 1242);
};

TEST(InstructionBasic, GetIndex) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::index)] = 12;

    EXPECT_EQ(x.get_index(), 12);
}

TEST(InstructionBasic, GetField) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::field)] = 22;

    EXPECT_EQ(x.get_field(), 22);
}

TEST(InstructionBasic, GetFieldLowerUpper) {
    Instruction x;

    x[static_cast<byte>(InstructionFields::field)] = 22;

    EXPECT_EQ(x.get_field_upper(), 2);
    EXPECT_EQ(x.get_field_lower(), 6);
}
