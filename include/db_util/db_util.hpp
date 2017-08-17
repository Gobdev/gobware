#ifndef DBUTIL_H
#define DBUTIL_H

#include <pqxx/pqxx>
#include <iostream>
#include <string>

using namespace pqxx;
using namespace std;

class db_util{

    public:
        db_util();
        ~db_util();
        string get_character(int i);
        void print_query(string sql);
        void enter_sentence(string orig, string hira, string trans, string cont);
        void enter_kanji(string kanji, string hira, string trans, string notes);

    private:
        connection* db_conn;
};

#endif
