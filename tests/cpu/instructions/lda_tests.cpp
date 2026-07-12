#include <memory>

#include <gtest/gtest.h>

#include "cpu/instructions/lda.h"
#include "cpu/cpu.h"

TEST(LDACpuTest, Encode) {
    LDA x;

    std::unique_ptr<Instruction> encoded = x.encode(12,  // address
                                                    13,  // index
                                                    1,   // lower
                                                    3);  // upper
    EXPECT_EQ(encoded->get_address(), 12);
    EXPECT_EQ(encoded->get_index(), 13);
    EXPECT_EQ(encoded->get_field_lower(), 1);
    EXPECT_EQ(encoded->get_field_upper(), 3);
    EXPECT_EQ(encoded->get_opcode(), 8);
}
