#include <string>
#include <iostream>

#include <histedit.h>

std::string get_input() {
    EditLine* el = el_init("cmix", stdin, stdout, stderr);
    History* hist = history_init();

    HistEvent ev;
    history(hist, &ev, H_SETSIZE, 100);

    el_set(el, EL_HIST, history, hist);
    el_set(el, EL_PROMPT, [](EditLine*) -> const char* { return ">>> "; });

    int count = 0;
    const char* line = el_gets(el, &count);

    std::string result;
    if (line && count > 0) {
        result = std::string(line, count);
        history(hist, &ev, H_ENTER, line);
    }

    history_end(hist);
    el_end(el);

    return result;
}
