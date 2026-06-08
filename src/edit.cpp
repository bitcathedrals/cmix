#include <string>
#include <iostream>
#include <cstdlib>

#include <histedit.h>

#include "edit.h"

extern "C" {
    static std::string prompt("cmix> ");

    static EditLine* el = nullptr;

    History* history_ptr = nullptr;
    HistEvent hev;
    int history_size = 512;

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

        history_ptr = history_init();
        history(history_ptr, &hev, H_SETSIZE, history_size);

        el_set(el, EL_HIST, history, history_ptr);
    }

    void store_history(const char* line) {
        history(history_ptr, &hev, H_ENTER, line);
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
            store_history(line);

            return std::string(line);
        }
    }

    return std::string();
}
