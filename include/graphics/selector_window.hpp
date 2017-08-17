#include <graphics/input_window.hpp>
#include <db_util/db_util.hpp>
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
        bool highlight;
        db_util* db;
};
