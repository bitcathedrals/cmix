#include <string>
#include <iostream>

#include <histedit.h>

static std::string prompt_string("cmix> ");

static const char* prompt([[maybe_unused]] EditLine *e)
{
    return prompt_string.c_str();
}

std::string get_input() {
    int count = 0;

    EditLine* el = el_init("cmix", stdin, stdout, stderr);

    History* hist = history_init();
    HistEvent ev;
    history(hist, &ev, H_SETSIZE, 100);
    el_set(el, EL_HIST, history, hist);

    el_set(el, EL_PROMPT, &prompt);
    el_set(el, EL_EDITOR, "emacs");

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
