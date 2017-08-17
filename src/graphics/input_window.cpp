#include <graphics/input_window.hpp>
#include <gobcode/unicode.hpp>
#include <string>

using namespace std;
using namespace unicode;

input_window::input_window(int x, int y, int width, int height, string title, db_util* db) :
                           window(x, y, width, height){
    /* Constructor */
    this -> title = title;
    this -> current_index = 0;
    this -> db = db;
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
    print_add();
    if (current_index < input.size())
        wmove(_window, 1 + (height / 4) * current_index, 1 + unicode_size(input[current_index].substr(0, string_index)));
    wrefresh(box_window);
    wrefresh(_window);
}

void input_window::print_add(){
    if (current_index == input.size())
        wattron(_window, COLOR_PAIR(colorPair));
    mvwprintw(_window, height - 4, width / 2 - 4, "Add");
    wattroff(_window, COLOR_PAIR(colorPair));
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
            move_down();
            break;
        case KEY_UP:
            move_up();
            break;
        case KEY_LEFT:
            move_left();
            break;
        case KEY_RIGHT:
            move_right();
            break;
        case KEY_ENTER:
        case 10:
            if (current_index != input.size())
                break;
            send_to_database();
        case 27:
            current_index = 0;
            update();
            return false;
        case KEY_BACKSPACE:
            backspace();
            break;
        case KEY_DC:
            del();
            break;
        default:
            if (current_index < input.size()){
                input[current_index].insert(string_index, 1, c);
                string_index++;
        }
    }
    return true;
}

void input_window::move_down(){
    current_index += current_index < input.size() ? 1 : 0;
    if (current_index < input.size())
        string_index = unicode_size(input[current_index]);
    else
        curs_set(0);
}

void input_window::move_up(){
    current_index -= current_index > 0 ? 1 : 0;
    if (current_index < input.size()){
        curs_set(1);
        string_index = unicode_size(input[current_index]);
    }
}

void input_window::move_left(){
    if (current_index < input.size()){
        string_index -= string_index > 0 ? 1 : 0;
        while(string_index > 0 && is_unicode_char(input[current_index].at(string_index))){
            string_index--;
        }
    }
}

void input_window::move_right(){
    if (current_index < input.size()){
        string_index += string_index < unicode_size(input[current_index]) ? 1 : 0;
        while(string_index < input[current_index].size() && is_unicode_char(input[current_index].at(string_index))){
            string_index++;
        }
    }
}

void input_window::backspace(){
    if (current_index < input.size() && input[current_index].size() > 0){
        while(string_index > 0 && is_unicode_char(input[current_index].at(string_index - 1))){
            input[current_index].erase(--string_index, 1);
        }
        if (string_index > 0)
            input[current_index].erase(--string_index, 1);
    }
}

void input_window::del(){
   if (current_index < input.size() && string_index < input[current_index].size()){
        input[current_index].erase(string_index, 1);
        while(string_index < input[current_index].size() && is_unicode_char(input[current_index].at(string_index))){
            input[current_index].erase(string_index, 1);
        }
    }
}

void input_window::reset_input(){
    for (vector<string>::iterator it = input.begin(); it != input.end(); ++it){
        *it = "";
    }
}

void input_window::send_to_database(){
    for (vector<string>::iterator it = input.begin(); it != input.end(); ++it){
        if (*it == "")
            return;
    }
    if (title == "Sentence")
        db -> enter_sentence(input[0], input[1], input[2], input[3]);
    else
        db -> enter_kanji(input[0], input[1], input[2], input[3]);
}
