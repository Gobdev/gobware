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

        // Fields
        string title;
        vector<string> lables;
        int current_index;
};
