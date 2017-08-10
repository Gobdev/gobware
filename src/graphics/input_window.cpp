#include <graphics/input_window.hpp>

using namespace std;

input_window::input_window(int x, int y, int width, int height, string title) :
                           window(x, y, width, height){
    /* Constructor */
    this -> title = title;
    lables.push_back("Kanji");
    lables.push_back("Hiragana");
    lables.push_back("Translation");
    if (title == "Sentence") {
        lables.push_back("Context");
    } else {
        lables.push_back("Notes");
    }
    for (int i = 0; i < lables.size(); i++){
        input.push_back("");
    }
    update();
    keypad(_window, TRUE);
}

input_window::~input_window(){
    /* Destructor */
}

void input_window::update(){
	wattron(_window, COLOR_PAIR(colorPair));
    werase(_window);
    box(_window, 0, 0);
	wattroff(_window, COLOR_PAIR(colorPair));
    for (int i = 0; i != lables.size(); i++){
        mvwprintw(_window, 1 + (height / 4) * i, 1, lables[i].c_str());
        mvwprintw(_window, 2 + (height / 4) * i, 2, input[i].c_str());
    }
    wmove(_window, 2 + (height / 4) * current_index, 2 + unicode_size(input[current_index]));
    wrefresh(_window);
}

int input_window::run(){
    setCurrentWindow();
    curs_set(1);
    int c;
    bool cont = true;
    c = 0;
    while(cont){
        update();
        c = wgetch(_window);
        switch(c){
            case KEY_DOWN:
                current_index -= current_index > 0 ? 1 : 0;
                break;
            case KEY_UP:
                current_index += current_index < input.size() - 1 ? 1 : 0;
                break;
            case KEY_ENTER:
            case 10:
                cont = false;
                break;
            case KEY_BACKSPACE:
                input[current_index].erase(input[current_index].size() - 1);
                break;
            default:
                input[current_index] += c;
        }
    }
    setNormalWindow();
    reset_input();
    update();
    curs_set(0);
    return 0;
}

void input_window::reset_input(){
    for (vector<string>::iterator it = input.begin(); it != input.end(); ++it){
        *it = "";
    }
}

int input_window::unicode_size(string unicode_string){
    int len = 0;
    const char* s = unicode_string.c_str();
    while(*s){
        len += (*s++ & 0xC0) != 0x80;
    }
    return len;
}
