#include <iostream>

#include <iostream>
#include <string>
#include <histedit.h> // Core libedit header

// Callback for the prompt
const char* prompt(EditLine *e) {
    return "my_shell> ";
}

int main() {
    // 1. Initialize EditLine
    // "sh" is the program name for .editrc settings
    EditLine *el = el_init("sh", stdin, stdout, stderr);
    el_set(el, EL_PROMPT, &prompt);
    el_set(el, EL_EDITOR, "emacs"); // Set default mode

    // 2. Initialize History
    History *myhistory = history_init();
    HistEvent ev;
    history(myhistory, &ev, H_SETSIZE, 800);
    el_set(el, EL_HIST, history, myhistory);

    int count;
    const char *line;

    // 3. Main Loop
    while ((line = el_gets(el, &count)) != NULL && count > 0) {
        std::string input(line);
        if (!input.empty() && input != "\n") {
            history(myhistory, &ev, H_ENTER, line); // Add to history
            std::cout << "You entered: " << input;
        }
    }

    // 4. Cleanup
    history_end(myhistory);
    el_end(el);
    return 0;
}




int main(void)
{
  std::cout << "enter a line" <<std::endl;
}
