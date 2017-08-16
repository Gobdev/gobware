#include <graphics/window.hpp>
#include <string>
#include <vector>

using namespace std;

class input_window : public window {

    public:
        input_window(int x, int y, int width, int height, string title);
        ~input_window();

    private:
        // Functions
        void update();
        int run();
        void reset_input();
        int unicode_size(string unicode_string);
        bool handle_character(int c);
        void move_left();
        void move_right();
        void move_up();
        void move_down();

        // Fields
        string title;
        vector<string> lables;
        vector<string> input;
        int current_index;
        int string_index;
};
