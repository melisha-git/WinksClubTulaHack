#include <libpq-fe.h>
#include <memory>
#include <string>
#include <boost/json.hpp>

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
    void execDml(const std::string& query);
    boost::json::array selectDml(const std::string& query);
};