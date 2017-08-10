#include <graphics/window.hpp>
#include <string>

window::window(int x, int y, int width, int height){
    this -> x = x;
    this -> y = y;
    this -> width = width;
    this -> height = height;
    box_window = newwin(height, width, y, x);
    _window = newwin(height - 2, width - 2, y + 1, x + 1);
    wborder(_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
}

window::~window(){
    wborder(box_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(box_window);
	delwin(_window);
	delwin(box_window);
}

void window::setCurrentWindow(){
    this -> colorPair = 1;
}

void window::setNormalWindow(){
    this -> colorPair = 2;
}
