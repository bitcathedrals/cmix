#ifndef WALL_CLOCK_H
#define WALL_CLOCK_H

#include <string>
#include <chrono>

using clocked_tick = std::chrono::steady_clock::time_point;
using clocked_time = std::chrono::system_clock::time_point;

class Clocked {
public:
    Clocked(std::string name);
    ~Clocked();

private:
    void get_time(clocked_tick& tick, clocked_time& time);

    const std::chrono::local_time<std::chrono::nanoseconds> timestamp(const clocked_time time) const;

    std::string name;

    clocked_tick start_tick;
    clocked_time start_time;
};

#endif
