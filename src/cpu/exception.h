#ifndef CPU_EXCEPTION_H
#define CPU_EXCEPTION_H

#include <iostream>
#include <string>
#include <chrono>
#include <stdexcept>

class GeneralException : std::runtime_error {

public:
    GeneralException(std::string context) : runtime_error(context),
                                            context(context),
                                            timestamp(std::chrono::system_clock::now()) {
    }

    friend std::ostream& operator<<(std::ostream& output,
                                    const GeneralException general);

private:
    const std::string context;
    const std::chrono::time_point<std::chrono::system_clock> timestamp;
};

#endif
