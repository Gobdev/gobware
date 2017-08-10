#include <graphics/window.hpp>
#include <string>
#include <vector>

using namespace std;

class selector_window : public window {

    public:
        selector_window(int x, int y, int width, int height);
        ~selector_window();
        void update();
        int run();
        void add_window(window* new_window, string title);

    private:
        // Functions
        bool enter_pressed();

        // Fields
        int x;
        int y;
        int width;
        int height;
        vector<window*> windows;
        vector<string> titles;
        int current_index;
};
