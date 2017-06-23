#include <pqxx/pqxx>
#include <iostream>

using namespace pqxx;
using namespace std;

class db_util{

    public:
        db_util();
        ~db_util();
        string get_character();
        void print_query(string sql);

    private:
        connection* db_conn;
};
