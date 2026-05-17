#include <iostream>

#include <parse.h>
#include <cpu/cpu.h>
#include <repl/dispatch.h>

Cmd_Status exec_read(const parse_t p);
Cmd_Status exec_write(const parse_t p);

Cmd_Status run_command(const parse_t p) {
    char size = p.size();

    if(size < 1) {
        std::cerr << "cmix: empty command." << std::endl;
        return Cmd_Status::bad_input;
    }

    Command cmd = string_to_command(p[0]);

    if(cmd == Command::unknown) {
        std::cerr << "cmix: unknown command: " << p[0] << std::endl;
    }

    switch (cmd) {
    case Command::quit:
        return Cmd_Status::ok;

    case Command::read:
        return exec_read(p);
        break;

    case Command::write:
        return exec_write(p);
        break;

    case Command::unknown:
        break;
    }

    std::cerr << "cmix unhandled command: " << p[0] << std::endl;
    return Cmd_Status::bad_input;
}

Cmd_Status exec_read(const parse_t p) {
    const int read_parse_size = 3;

    int size = std::atoi(p[0].c_str());

    if (size != read_parse_size) {
        std::cerr << "cmix bad input, expected " << size << p << std::endl;
        return Cmd_Status::bad_input;
    }

    if (p[1] == "reg") {
        if (p[2] == "X") {
            std::cerr << CPU.A << std::endl;
        }

        if (p[2] == "Z") {
            std::cerr << CPU.X << std::endl;
        }
    }

    if (p[1] == "mem") {
        int address = std::atoi(p[2].c_str());

        if ((address >= 0) && (address < memory_capacity)) {
            std::cerr << CPU.memory[address] << std::endl;
        }
        else {
            std::cerr << "cmix: bad address: " << p[2] << std::endl;
            return Cmd_Status::out_of_range;
        }
    }

    std::cerr << "cmix unknown type (reg/mem): " << p[1] << std::endl;
    return Cmd_Status::bad_input;
}

