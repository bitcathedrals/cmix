#include <gtest/gtest.h>

#include <cpu/word.h>
#include <cpu/cpu.h>

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
