#include <gtest/gtest.h>
#include <exception.h>

// class ThrowableStream : public std::runtime_error {

TEST(ExceptionCore, ThrowableStreamBase) {
    ThrowableStream throwable = ThrowableStream("ExceptionCore.ThrowableStream");

    std::ostringstream test;
    test << throwable;

    EXPECT_EQ(test.str(), "runtime error - context: "
              + std::string("ExceptionCore.ThrowableStream nested: "));
}
