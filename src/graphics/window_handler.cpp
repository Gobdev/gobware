#include <graphics/window_handler.hpp>
#include <iostream>

window_handler::window_handler(){
    /* Setup windows */
    selector = new selector_window(0, LINES*3/5, COLS/3, LINES - LINES*3/5);
    selector -> setCurrentWindow();

    selector2 = new selector_window(0, 0, COLS*2/3, LINES*3/5);
    selector -> add_window(selector2, "Enter sentence");

    selector2 = new selector_window(COLS*2/3, 0, COLS, LINES*3/5);
    selector -> add_window(selector2, "Enter word");

    selector2 = new selector_window(COLS/3, LINES*3/5, COLS, LINES - LINES*3/5);
    selector -> add_window(selector2, "Translate");

    selector -> add_window(NULL, "Exit");

    currentActiveWindow = selector;
    currentActiveWindow -> update();
}

window_handler::~window_handler(){
    delete selector;
}

void window_handler::handle_character(char ch){
    window* newWindow;
    newWindow = currentActiveWindow -> handle_character(ch);
    /*if (newWindow != currentActiveWindow){
        currentActiveWindow -> setNormalWindow();
        newWindow -> setCurrentWindow();
        currentActiveWindow = newWindow;
        currentActiveWindow -> update();
    }
    currentActiveWindow -> update();*/
}
