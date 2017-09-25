#ifndef INPUT_WINDOW_H
#define INPUT_WINDOW_H

#include <graphics/window.hpp>
#include <db_util/db_util.hpp>
#include <string>
#include <vector>

using namespace std;

class input_window : public window {

    public:
        input_window(int x, int y, int width, int height, string title, db_util* db);
        ~input_window();

    private:
        // Functions.
        void update();
        int run();
        void reset_input();
        bool handle_character(int c);
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        void backspace();
        void del();
        void send_to_database();
        void print_add();

        // Fields
        string title;
        vector<string> lables;
        vector<string> input;
        int current_index;
        int string_index;
        db_util* db;
};

#endif
