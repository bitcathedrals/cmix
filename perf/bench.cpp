#include <iostream>
#include <string>

#include <randomized.h>

#include <equals.h>

void random_test() {
    Randomized r(0,3999);

    for(auto i = 0; i < 5; i++) {
        int x = r.next();
        std::cerr << x << "...";
    }
}

void equals_test() {
    EqualsTest equals;
}

int main(int argc, char* argv[]) {
    std::cerr << "cmix benchmarking. " << std::endl;

    for(auto count = 0; count < argc; count++) {
        if (count < 1) {
            continue;
        }

        std::string metric(argv[count]);

        if(metric == "random") {
            std::cerr << "randomized test...";
            random_test();
            std::cerr << "done." << std::endl;

            continue;
        }

        if(metric == "equals") {
            std::cerr << "equals test..." << std::endl;
            equals_test();
            std::cerr << "done." << std::endl;

            continue;
        }

        std::cerr << "unrecognized metric: " << metric << std::endl;
    }

    return 0;
}
