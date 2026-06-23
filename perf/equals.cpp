#include <iostream>

#include "randomized.h"
#include "equals.h"

EqualsTest::EqualsTest () {
    for(auto i = 0; i < memory_capacity; i++) {
        int x = i % stripe_count;

        if (x < 0 || x > 3) {
            std::cerr << "stripe index out of range: i = "
                      << i
                      << " x = " << x
                      << std::endl;
        }

        cpu.memory[i] = stripes[x];
    }
}

void EqualsTest::test(int iterations) {
    Randomized random(0, memory_capacity);

    int true_count = 0;
    int false_count = 0;

    Word compare(stripes[0]);

    for (auto i = 0; i < iterations; i++) {
        if(cpu.memory[random.next()] == compare) {
            true_count++;
            continue;
        }

        false_count++;
    }

    std::cerr << "equals: iterations = " << iterations
              << " true count = " << true_count
              << " false count = " << false_count
              << std::endl;

}
