#include <graphics/input_window.hpp>


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
    update();
    keypad(_window, TRUE);
}

input_window::~input_window(){
    /* Destructor */
}

void input_window::update(){
	wattron(_window, COLOR_PAIR(colorPair));
    box(_window, 0, 0);
	wattroff(_window, COLOR_PAIR(colorPair));
    for (int i = 0; i != lables.size(); i++){
        mvwprintw(_window, 1 + (height / 4) * i, 1, lables[i].c_str());
    }
    wrefresh(_window);
}

int input_window::run(){
    setCurrentWindow();
    char c;
    c = 0;
    while(c != 10){
        update();
        c = wgetch(_window);
    }
    setNormalWindow();
    update();
    return 0;
}
