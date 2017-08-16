#include <db_util/db_util.hpp>

using namespace std;
using namespace pqxx;

string translate_url = "https://translate.googleapis.com/translate_a/single?client=gtx&sl=en&tl=ja&dt=t&q={}";

db_util::db_util(){
    /* Connect to database. */
    db_conn = new connection("dbname = gobware "
                             "user = gob_user "
                             "password = psqlisstupid "
                             "hostaddr = 127.0.0.1 "
                             "port = 5432");
}

db_util::~db_util(){
    db_conn -> disconnect();
}



string db_util::get_character(int i){
    /* Create a non-transactional object. */
    nontransaction db_nontransaction(*db_conn);
    /* Execute SQL query */
    result db_result(db_nontransaction.exec("SELECT * FROM sentences;"));
    return (db_result[i][1].as<string>() + " - " + db_result[i][2].as<string>() + " - " + db_result[i][3].as<string>());
}

void db_util::print_query(string sql){
    nontransaction db_nontransaction(*db_conn);
    /* Execute SQL query */
    result db_result(db_nontransaction.exec(sql));
    for (result::const_iterator row = db_result.begin(); row != db_result.end(); row++){
        for (result::tuple::const_iterator field = row->begin(); field != row->end(); field++)
            cout << field->c_str() << '\t';
    cout << endl;
    }
}

/*void deprecated() {
    cout << system("pwd") << endl;
    string sql;
    try {
        db_conn = new pqxx::connection("dbname = jap_proj \
                                        user = jap_proj_user \
                                        password = psqlisstupid \
                                        hostaddr = 127.0.0.1 \
                                        port = 5432");
        if (db_conn -> is_open()) {
            cout << "Opened database successfully: " << db_conn -> dbname() << endl;
            /*sql = "INSERT INTO test values ('test1', 'test2');";
            execute_sql(sql);*/
/*            sql = "SELECT * FROM test;";
            pqxx::result res = execute_sql(sql);
            for (pqxx::result::const_iterator current = res.begin(); current != res.end(); current++){
                cout << "col = " << current[0].as<string>() << ", ";
                cout << "col2 = " << current[1].as<string>() << endl;
            }
        } else {
            cout << "Can't open database" << endl;
            return 1;
        }
        db_conn -> disconnect();
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }
}*/
