#include <wall_clock.h>

#include <iostream>

Clocked::Clocked(std::string name) : name(name),
                                     start(std::chrono::steady_clock::now()) {}

Clocked::~Clocked() {
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cerr << "Clocked: " << name
//              << "Start: " << start
//              << "End: " << end
              << "Elapsed: " << elapsed
              << std::endl;
}
