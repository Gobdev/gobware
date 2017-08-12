#include <iostream>
#include <pqxx/pqxx>
#include <db_util/db_util.hpp>
#include <graphics/selector_window.hpp>
#include <graphics/input_window.hpp>

using namespace std;

pqxx::connection* db_conn;

#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

string choices[] = {
			"Choice 1",
			"Choice 2",
			"Choice 3",
			"Choice 4",
			"Exit",
		  };
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
int handle_windows();

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c, return_code;

    db_util db;
    choices[3] = db.get_character(0).substr(0, 27);

    initscr();
	start_color();
    clear();
    noecho();
    //cbreak();	/* Line buffering disabled. pass on everything */
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	return_code = handle_windows();
    refresh();
    clrtoeol();
    refresh();
    endwin();
    return return_code;
}

int handle_windows(){
	/* Setup windows */
	int return_code;
    selector_window* selector;
	selector = new selector_window(0, LINES*3/5, COLS/3, LINES - LINES*3/5);
    selector -> setCurrentWindow();

    window* selector2 = new input_window(0, 0, COLS*2/3, LINES*3/5, "Sentence");
    selector -> add_window(selector2, "Enter sentence");

    selector2 = new input_window(COLS*2/3, 0, COLS/3, LINES*3/5, "Word");
    selector -> add_window(selector2, "Enter word");

    selector2 = new input_window(COLS/3, LINES*3/5, COLS*2/3, LINES - LINES*3/5, "shieet");
    selector -> add_window(selector2, "Translate");

    selector -> add_window(NULL, "Exit");

    selector -> update();
	return_code = selector -> run();
	//delete selector;
	return return_code;
}


void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i)
    {	if(highlight == i + 1) /* High light the present choice */
        {	wattron(menu_win, A_REVERSE);
            mvwphttps://stackoverflow.com/questions/21745816/makefile-make-dependency-only-if-file-doesnt-existrintw(menu_win, y, x, choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, choices[i].c_str());
        ++y;
    }
    wrefresh(menu_win);
}

/*void unused(){

    print_menu(menu_win, highlight);
    while(1)
    {	c = wgetch(menu_win);
        switch(c)
        {	case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                mvprintw(24, 0, "Character pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                //refresh();
                break;
        }
        print_menu(menu_win, highlight);
        if(choice != 0)	/* User did a choice come out of the infinite loop */
            /*break;
    }
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
}*/
