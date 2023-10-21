#include <libpq-fe.h>
#include <memory>
#include <string>

/*

int main() {
    PGconn* conn = PQconnectdb("dbname=mydatabase user=myuser password=mypassword hostaddr=127.0.0.1 port=5432");

    if (PQstatus(conn) == CONNECTION_OK) {
        std::cout << "Соединение с PostgreSQL успешно установлено!" << std::endl;

        PGresult* res = PQexec(conn, "SELECT * FROM mytable");

        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
            int numRows = PQntuples(res);
            int numCols = PQnfields(res);

            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    std::cout << PQgetvalue(res, i, j) << " ";
                }
                std::cout << std::endl;
            }
        } else {
            std::cout << "Ошибка выполнения SQL-запроса: " << PQerrorMessage(conn) << std::endl;
        }

        PQclear(res);
    } else {
        std::cout << "Ошибка соединения с PostgreSQL: " << PQerrorMessage(conn) << std::endl;
    }

    PQfinish(conn);
    return 0;
}
*/

class Database {
private:
    PGconn* connect_;
public:
    Database(const std::string &hostname, const std::string &port, const std::string &database, 
            const std::string &user, const std::string &password);
    Database(const std::string& connectionString);
    ~Database();

    void init(const std::string& hostname, const std::string& port, const std::string& database,
        const std::string& user, const std::string& password);
    void init(const std::string & connectionString);

    void insertQuery(const std::string& query);
};