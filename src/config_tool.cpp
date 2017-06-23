#include <iostream>
#include <pqxx/pqxx>
#include <db_util.hpp>

using namespace std;

pqxx::connection* db_conn;


int main(int argc, char* argv[]){
    db_util db;
    cout << db.get_character() << endl;
}
