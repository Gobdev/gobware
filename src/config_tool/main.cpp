#include <iostream>
#include <pqxx/pqxx>
#include <db_util/db_util.hpp>
#include <graphics/window_handler.hpp>

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

int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    db_util db;
    choices[3] = db.get_character(0).substr(0, 27);

    initscr();
	start_color();
    clear();
    noecho();
    cbreak();	/* Line buffering disabled. pass on everything */
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
https://stackoverflow.com/questions/21745816/makefile-make-dependency-only-if-file-doesnt-exist
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	window_handler window_h = window_handler();
	window_h.handle_character('c');
    refresh();
    clrtoeol();
    refresh();
    endwin();
    return 0;
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
