#include <memory>

#include <gtest/gtest.h>

#include "cpu/instructions/lda.h"
#include "cpu/cpu.h"

struct LDA_winch : public LDA {
    using LDA::encode;
};

TEST(LDACpuTest, Encode) {
    LDA_winch x;

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

TEST(LDACpuTest, CpuTest) {
    LDA_winch x;

    CPU.reset();

    CPU.A = Word(12,12,12,12,12);

    CPU.memory[1] = Word(2,4,6,8,10);

    CPU.memory[0] = *x.encode(1,
                              0,
                              2,
                              4);
    CPU.run(0);

    EXPECT_EQ(CPU.A[1], 12);
    EXPECT_EQ(CPU.A[2], 4);
    EXPECT_EQ(CPU.A[3], 6);
    EXPECT_EQ(CPU.A[4], 8);
    EXPECT_EQ(CPU.A[5], 12);
}
