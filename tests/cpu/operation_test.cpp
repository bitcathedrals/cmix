#include <sstream>
#include <string>
#include <cstdlib>

#include <gtest/gtest.h>

#include <exception.h>
#include <cpu/operation.h>

TEST(OperationTests, TestUndefinedOperationBase) {
    int i = 3;
    int x = 5;
    int v = 9;

    UndefinedOperation undef(i, x, v);

    std::ostringstream out;

    out << undef;

    std::string expected(" undefined operation parameters are: ");
    expected += " i value " + std::to_string(i);
    expected += " x value " + std::to_string(x);
    expected += " v value " + std::to_string(v);

    EXPECT_EQ(out.str(), expected);
}
