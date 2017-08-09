#include <graphics/selector_window.hpp>
#include <string>

selector_window::selector_window(int x, int y, int width, int height) :
                                 window(x, y, width, height){
    /* Constructor */
    update();
    keypad(_window, TRUE);
}

selector_window::~selector_window(){
    /* Destroy */
    for (vector<window*>::iterator it = windows.begin(); it != windows.end(); ++it){
        delete *it;
    }
}

void selector_window::update(){
	wattron(_window, COLOR_PAIR(colorPair));
    box(_window, 0, 0);
	wattroff(_window, COLOR_PAIR(colorPair));
    for (int i = 0; i != titles.size(); i++){
        if (i == current_index){
            wattron(_window, COLOR_PAIR(1));
        } else {
            wattron(_window, COLOR_PAIR(2));
        }
        mvwprintw(_window, 2 * (i + 1), 1, titles[i].c_str());
    }
    wrefresh(_window);
}

window* selector_window::handle_character(char ch){
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
                mvwprintw(_window, 10, 1, "Enter pressed.");
                cont = enter_pressed();
        }
        update();
    }
    curs_set(1);
}

bool selector_window::enter_pressed(){
    if (current_index >= titles.size() - 1){
        return false;
    } else if (current_index < 0) {
        return false;
    }
    return true;
}

void selector_window::add_window(window* new_window, string title){
    windows.push_back(new_window);
    titles.push_back(title);
}
