#ifndef WORD_FIXTURES_H
#define WORD_FIXTURES_H

#include <gtest/gtest.h>

#include "cpu.h"

class SimpleWordFixture : public testing::Test {
public:
    word mix_word;

    SimpleWordFixture(void) : mix_word(2,4,6,8,10) {};
};

#endif
