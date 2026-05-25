#include <string>
#include <chrono>

class Clocked {
    Clocked(std::string name);
    ~Clocked();

private:
    std::string name;

    std::chrono::steady_clock::time_point start;
};
