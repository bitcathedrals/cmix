#include <iostream>

#include <equals.h>

EqualsTest::EqualsTest () {
    for(auto i = 0; i < memory_capacity; i++) {
        int x = i % 4;

        if (x < 0 || x > 4) {
            std::cerr << "value out of range: i = "
                      << i
                      << " x = "
                      << x
                      << std::endl;
        }
    }
}
