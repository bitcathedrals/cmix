#ifndef WALL_CLOCK_H
#define WALL_CLOCK_H

#include <string>
#include <chrono>

class Clocked {
public:
    Clocked(std::string name);
    ~Clocked();

private:
    std::string name;

    std::chrono::steady_clock::time_point start;
};

#endif
