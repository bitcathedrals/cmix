#include <gtest/gtest.h>

#include "mixer/parser.h"

TEST(MixerParserRegression, IsCaptureVirtual) {
    EXPECT_NO_THROW(
        std::string test_string("1234");

        auto begin_itr = test_string.cbegin();
        auto end_itr = test_string.cend();

        const Token& t = Numeric();
        Token p = t.match(begin_itr, end_itr);
        );
}
