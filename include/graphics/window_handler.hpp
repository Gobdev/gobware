#include <iostream>
#include <ncurses.h>
#include <graphics/selector_window.hpp>

class window_handler{

    public:
        window_handler();
        ~window_handler();
        void handle_character(char ch);

    private:
        selector_window* selector;
        window* selector2;
        window* currentActiveWindow;
};
