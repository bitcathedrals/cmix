#include <gtest/gtest.h>

#include <cpu/word.h>
#include <cpu/cpu.h>


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
