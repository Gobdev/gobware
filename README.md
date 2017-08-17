# Gobware v0.2
Gobware currently only supports unix operating systems.  

## Currently Working Features:

  - Select a window.
  - Input text to be entered into database (not sent to the database at the moment).
  - Delete written text in input windows.
  
## Planned Features:

  - Send entered data to database.
  - Implement Bing translation in the currently unused window (since it's free).
  - Create a second binary that can utilize the database.

## Required libraries:

  - [NCurses](https://www.gnu.org/software/ncurses/)
  - [libpqxx](http://pqxx.org/development/libpqxx/)
  - [PostgreSQL](https://www.postgresql.org/)
  
## Installation

  - Install PSQL.  
  - Install NCurses.  
  - Install libpqxx, easiest done by following [this tutorial](https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm)  
  Start the PSQL server, then clone/fork this directory, and enter the directory. 
  Startup PSQL and create a database titled 'gobware'.  
  Connect to the database and run `\i src/db_util/db_setup.sql`. This should setup the database for you.  
  Then run  
  `$ make`  
  The generated binaries will be placed in `bin`. You can now start the program by typing `$ ./bin/config_tool`.
