#include <graphics/window.hpp>
#include <string>

window::window(int x, int y, int width, int height){
    _window = newwin(height, width, y, x);
}

window::~window(){
    wborder(_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(_window);
	delwin(_window);
}

void window::setCurrentWindow(){
    this -> colorPair = 1;
}

void window::setNormalWindow(){
    this -> colorPair = 2;
}
