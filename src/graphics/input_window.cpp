#include <graphics/input_window.hpp>

using namespace std;

input_window::input_window(int x, int y, int width, int height, string title) :
                           window(x, y, width, height){
    /* Constructor */
    this -> title = title;
    this -> current_index = 0;
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
	wattron(box_window, COLOR_PAIR(colorPair));
    werase(_window);
    box(box_window, 0, 0);
	wattroff(box_window, COLOR_PAIR(colorPair));
    for (int i = 0; i != lables.size(); i++){
        mvwprintw(_window, (height / 4) * i, 0, lables[i].c_str());
        mvwprintw(_window, 1 + (height / 4) * i, 1, input[i].c_str());
    }
    mvwprintw(_window, height - 4, 1, "Cancel");
    mvwprintw(_window, height - 4, width - 6, "Add");
    wmove(_window, 1 + (height / 4) * current_index, 1 + unicode_size(input[current_index].substr(0, string_index)));
    wrefresh(box_window);
    wrefresh(_window);
}

int input_window::run(){
    setCurrentWindow();
    curs_set(1);
    current_index = 0;
    int c;
    bool cont = true;
    c = 0;
    while(cont){
        update();
        c = wgetch(_window);
        cont = handle_character(c);
    }
    setNormalWindow();
    reset_input();
    update();
    curs_set(0);
    return 0;
}

bool input_window::handle_character(int c){
    switch(c){
        case KEY_DOWN:
            current_index += current_index < input.size() - 1 ? 1 : 0;
            string_index = unicode_size(input[current_index]);
            break;
        case KEY_UP:
            current_index -= current_index > 0 ? 1 : 0;
            string_index = unicode_size(input[current_index]);
            break;
        case KEY_LEFT:
            move_left();
            break;
        case KEY_RIGHT:
            move_right();
            break;
        case KEY_ENTER:
        case 10:
        case 27:
            return false;
        case KEY_BACKSPACE:
            if (input[current_index].size() > 0){
                while((input[current_index].at(string_index - 1) & 0xC0) == 0x80){
                    input[current_index].erase(--string_index, 1);
                }
                input[current_index].erase(--string_index, 1);
            }
            break;
        default:
            input[current_index] += c;
            string_index++;
    }
    return true;
}

void input_window::move_left(){
    string_index -= string_index > 0 ? 1 : 0;
    while(string_index > 0 && (input[current_index].at(--string_index) & 0xC0) == 0x80);
}

void input_window::move_right(){
    string_index += string_index < unicode_size(input[current_index]) ? 1 : 0;
    while(string_index < input[current_index].size() && ++string_index < input[current_index].size() && (input[current_index].at(string_index) & 0xC0) == 0x80);
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
        len++;
        *s++;
        if ((*s & 0xC0) == 0x80){
            len++;
            while((*s & 0xC0) == 0x80){
                *s++;
            }
        }
    }
    return len;
}
