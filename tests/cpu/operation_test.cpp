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

    std::string expected("Operation base class reached, undefined operation");
    expected += " parameters are:";
    expected += " i value " + std::to_string(i);
    expected += " x value " + std::to_string(x);
    expected += " v value " + std::to_string(v);

    EXPECT_EQ(out.str(), expected);
}

TEST(OperationTests, ArithmeticExceptionTest) {
    ArithmeticException test_exception("test", 42);

    std::ostringstream out;

    std::string expected("test Arithmetic Exception value = ");
    expected += std::to_string(static_cast<int>(42));

    out << test_exception;

    EXPECT_EQ(out.str(), expected);
}
