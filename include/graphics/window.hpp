#ifndef WINDOW_H
#define WINDOW_H
#include <ncurses.h>

class window {
    public:
        void setCurrentWindow();
        void setNormalWindow();
        virtual void update() = 0;
        virtual int run() = 0;
        window(int x, int y, int width, int height);
        ~window();

    protected:
        WINDOW* _window;
        int colorPair = 2;
};
#endif
