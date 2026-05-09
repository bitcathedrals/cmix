#ifndef WORD_FIXTURES_H
#define WORD_FIXTURES_H

#include <gtest/gtest.h>

#include <cpu/word.h>

class WordFixture : public testing::Test {
public:
    word mix_word;

    WordFixture(void) : mix_word(2,4,6,8,10) {};
};

#endif
