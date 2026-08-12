#include <memory>

#include <gtest/gtest.h>

#include "cpu/instructions/lda.h"
#include "cpu/cpu.h"

struct LDA_winch : public LDA {
    using LDA::encode;
};

TEST(LDACpuTest, Encode) {
    LDA_winch x;

    x.encode(12,  // address
             13,  // index
             1,   // lower
             3);  // upper

    EXPECT_EQ(x.get_address(), 12);
    EXPECT_EQ(x.get_index(), 13);
    EXPECT_EQ(x.get_field_lower(), 1);
    EXPECT_EQ(x.get_field_upper(), 3);
    EXPECT_EQ(x.get_opcode(), 8);
}

TEST(LDACpuTest, CpuInstructionTest) {
    CPU.reset();

    CPU.A = Word(12,12,12,12,12);

    CPU.memory[1] = Word(2,4,6,8,10);

    auto x = std::make_unique<LDA_winch>();

    x->encode(1, 0, 0, 8);
    x->set_field(2,4);

    x->opcode();

    EXPECT_EQ(CPU.A[1], 12);
    EXPECT_EQ(CPU.A[2], 4);
    EXPECT_EQ(CPU.A[3], 6);
    EXPECT_EQ(CPU.A[4], 8);
    EXPECT_EQ(CPU.A[5], 12);
}


TEST(LDACpuTest, CpuRunTest) {
    CPU.reset();

    CPU.A = Word(12,12,12,12,12);

    CPU.memory[1] = Word(2,4,6,8,10);

    auto x = std::make_unique<LDA_winch>();
    x->encode(1, 0, 0, 8);
    x->set_field(2,4);

    CPU.memory[0] = *x;

    CPU.run(0);

    EXPECT_EQ(CPU.A[1], 12);
    EXPECT_EQ(CPU.A[2], 4);
    EXPECT_EQ(CPU.A[3], 6);
    EXPECT_EQ(CPU.A[4], 8);
    EXPECT_EQ(CPU.A[5], 12);
}
