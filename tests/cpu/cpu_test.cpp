#include <cpu.h>

#include <gtest/gtest.h>

#include <cpu/word.h>
#include <cpu.h>

//
// test memory array, type and set
//

TEST(CpuData, MemoryTestType) {
    ASSERT_EQ(typeid(Word), typeid(memory[0]));
}

TEST(CpuData, MemoryTestSetAndRead) {
    memory[0][0] = 16;
    ASSERT_EQ(memory[0][0], 16);
}

//
// Register A
//

TEST(CpuData, RegisterATestType) {
    ASSERT_EQ(typeid(Word), typeid(A));
}

TEST(CpuData, RegisterATestSetAndRead) {
    A[0] = 16;
    ASSERT_EQ(A[0], 16);
}

//
// Register X
//

TEST(CpuData, RegisterXTestType) {
    ASSERT_EQ(typeid(Word), typeid(X));
}

TEST(CpuData, RegisterXTestSetAndRead) {
    X[0] = 16;
    ASSERT_EQ(X[0], 16);
}
