#include <string>
#include <iostream>
#include <cstdlib>

#include "edit.h"
#include <histedit.h>

extern "C" {
    static std::string prompt("cmix> ");

    static EditLine* el = nullptr;

    char* edit_prompt(EditLine* el [[maybe_unused]]) {
        return const_cast<char*>("buggy> ");
    }

    void setup_lib_edit() {
        el = el_init((const char*)"cmix", stdin, stdout, stderr);

        if(!el) {
            std::cerr << "el_init failed" << std::endl;
            std::exit(1);
        }

        el_set(el, EL_PROMPT, &edit_prompt);
        el_set(el, EL_EDITOR, "emacs");
    }
}

std::string get_input(void) {
    int count = 0;

    if (el == nullptr) {
        setup_lib_edit();
    }

    const char* line = nullptr;

    while((line = el_gets(el, &count)) != nullptr) {
        if(count > 1) {
            return std::string(line);
        }
    }

    return std::string();
}
