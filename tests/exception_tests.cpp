#include <gtest/gtest.h>
#include <exception.h>

TEST(ExceptionCore, ThrowableStreamBase) {
    ThrowableStream throwable = ThrowableStream("ExceptionCore.ThrowableStream");

    std::ostringstream test;
    test << throwable;

    EXPECT_EQ(test.str(),
              "ExceptionCore.ThrowableStream:");
}
