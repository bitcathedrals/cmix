#include <gtest/gtest.h>

#include "cpu/word.h"
#include "cpu/cpu.h"

//
// test memory array, type and set
//

TEST(CpuData, CopyCPU) {
    for(auto i=0;i < memory_capacity; i++) {
        CPU.memory[i][0] = 1;
        CPU.memory[i][1] = 2;
        CPU.memory[i][2] = 3;
        CPU.memory[i][3] = 4;
        CPU.memory[i][4] = 5;
    }

    Cpu copy(CPU);

    for(auto i=0;i < memory_capacity; i++) {
        ASSERT_EQ(copy.memory[i][0], 1);
        ASSERT_EQ(copy.memory[i][1], 2);
        ASSERT_EQ(copy.memory[i][2], 3);
        ASSERT_EQ(copy.memory[i][3], 4);
        ASSERT_EQ(copy.memory[i][4], 5);
    }
}

//
// test memory array, type and set
//

TEST(CpuData, MemoryTestSetAndRead) {
    CPU.memory[0][0] = 16;
    ASSERT_EQ(CPU.memory[0][0], 16);
}

//
// Register A
//

TEST(CpuData, RegisterATestSetAndRead) {
    CPU.A[0] = 16;
    ASSERT_EQ(CPU.A[0], 16);
}

//
// Register X
//

TEST(CpuData, RegisterXTestSetAndRead) {
    CPU.X[0] = 16;
    ASSERT_EQ(CPU.X[0], 16);
}

TEST(CpuData, Reset) {
    CPU.memory[0][1] = 42;

    CPU.X[1] = 16;
    CPU.A[1] = 16;

    CPU.I1[1] = 42;
    CPU.I2[1] = 42;
    CPU.I3[1] = 42;
    CPU.I4[1] = 42;
    CPU.I5[1] = 42;
    CPU.I6[1] = 42;

    CPU.J[1] = 42;

    CPU.overflow = true;

    CPU.compare = Cpu::ComparisonIndicator::LESS;

    CPU.reset();

    EXPECT_EQ(CPU.memory[0][1], 0);

    EXPECT_EQ(CPU.X[1], 0);
    EXPECT_EQ(CPU.A[1], 0);

    EXPECT_EQ(CPU.I1[1], 0);
    EXPECT_EQ(CPU.I2[1], 0);
    EXPECT_EQ(CPU.I3[1], 0);
    EXPECT_EQ(CPU.I4[1], 0);
    EXPECT_EQ(CPU.I5[1], 0);
    EXPECT_EQ(CPU.I6[1], 0);

    EXPECT_EQ(CPU.J[1], 0);

    EXPECT_EQ(CPU.overflow, false);

    EXPECT_EQ(CPU.compare, Cpu::ComparisonIndicator::UNSET);

}
