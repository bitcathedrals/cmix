#include <iostream>
#include <chrono>
#include <format>

#include "wall_clock.h"

namespace clk = std::chrono;

Clocked::Clocked(std::string name) : name(name) {
    get_time(start_tick, start_time);
}

void Clocked::get_time(clocked_tick& tick, clocked_time& time) {
    tick = clk::steady_clock::now();
    time = clk::system_clock::now();
}

const std::chrono::local_time<std::chrono::nanoseconds> Clocked::timestamp(const clocked_time time) const {
    const auto wall_ns = clk::time_point_cast<clk::nanoseconds>(time);

    const auto local_zone = clk::current_zone();
    return local_zone->to_local(wall_ns);
}

Clocked::~Clocked() {
    clocked_tick end_tick;
    clocked_time end_time;

    get_time(end_tick, end_time);

    auto delta = clk::duration_cast<clk::nanoseconds>(end_tick - start_tick);

    std::cerr << "Clocked: " << name
              << " Start = " << timestamp(start_time)
              << " Elapsed = " << delta.count() << "ns"
              << " End = " << timestamp(end_time)
              << std::endl;
}
