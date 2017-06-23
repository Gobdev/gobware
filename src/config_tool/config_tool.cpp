#include <iostream>
#include <ncurses.h>
#include <pqxx/pqxx>
#include <db_util/db_util.hpp>

using namespace std;

pqxx::connection* db_conn;


int main(int argc, char* argv[]){
    setlocale(LC_ALL, "");
    db_util db;
    /*cout << db.get_character() << endl;
    string input = "";
    while(input != "q"){
        getline(cin, input);
        if (input != "q")
            db.print_query(input);
    }*/
    initscr();			                /* Start curses mode 		      */
    
    while(1){
    	printw(db.get_character().c_str());	/* Print Hello World		      */
    	refresh();			                /* Print it on to the real screen */
    	getch();			                /* Wait for user input            */
    }
	endwin();			                /* End curses mode                */

	return 0;
}
