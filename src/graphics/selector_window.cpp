#include <graphics/selector_window.hpp>
#include <string>

selector_window::selector_window(int x, int y, int width, int height) :
                                 window(x, y, width, height){
    /* Constructor */
    window* input;
    highlight = true;
    current_index = 0;
    setCurrentWindow();
    db = new db_util;
    input = new input_window(0, 0, COLS*2/3, LINES*3/5, "Sentence", db);
    add_window(input, "Enter sentence");

    input = new input_window(COLS*2/3, 0, COLS/3, LINES*3/5, "Word", db);
    add_window(input, "Enter word");

    input = new input_window(COLS/3, LINES*3/5, COLS*2/3, LINES - LINES*3/5, "shieet", db);
    add_window(input, "Translate");

    add_window(NULL, "Exit");
    keypad(_window, TRUE);
    update();
}

selector_window::~selector_window(){
    /* Destroy */
    for (vector<window*>::iterator it = windows.begin(); it != windows.end(); ++it){
        delete *it;
    }
}

void selector_window::update(){
    if (highlight)
        wattron(box_window, COLOR_PAIR(colorPair));
    box(box_window, 0, 0);
    wattroff(box_window, COLOR_PAIR(colorPair));
    for (int i = 0; i != titles.size(); i++){
        if (i == current_index && highlight){
            wattron(_window, COLOR_PAIR(1));
        }
        mvwprintw(_window, 1 + 2 * i, 0, titles[i].c_str());
        wattroff(_window, COLOR_PAIR(1));
    }
    wrefresh(box_window);
    wrefresh(_window);
}

int selector_window::run(){
    int c = 0;
    bool cont = true;
    curs_set(0);
    while(cont){
        c = wgetch(_window);
        switch(c){
            case KEY_UP:
                current_index -= current_index > 0 ? 1 : 0;
                break;
            case KEY_DOWN:
                current_index += current_index < titles.size() - 1 ? 1 : 0;
                break;
            case 10:
                cont = enter_pressed();
        }
        update();
    }
    curs_set(1);
    return 0;
}

bool selector_window::enter_pressed(){
    highlight = false;
    update();
    if (current_index >= titles.size() - 1){
        return false;
    } else if (current_index < 0) {
        return false;
    } else {
        windows[current_index] -> run();
    }
    highlight = true;
    return true;
}

void selector_window::add_window(window* new_window, string title){
    windows.push_back(new_window);
    titles.push_back(title);
}
