#include "Database.hpp"
#include <stdexcept>

Database::Database(const std::string& hostname, const std::string& port, const std::string& database, const std::string& user, const std::string& password) 
	: connect_(nullptr) {
	
	init(hostname, port, database, user, password);
}

Database::Database(const std::string& connectionString) {
	init(connectionString);
}

Database::~Database() {
	if (connect_ != nullptr) {
		PQfinish(connect_);
	}
}

void Database::init(const std::string& hostname, const std::string& port, const std::string& database, const std::string& user, const std::string& password) {
	std::string connectionString = "dbname = " + database + " user = " + user + " password = " + password + " hostaddr = " + hostname + " port = " + port;
	return init(connectionString);
}

void Database::init(const std::string& connectionString) {
	if (connect_ != nullptr) {
		PQfinish(connect_);
	}
	connect_ = PQconnectdb(connectionString.c_str());
	if (PQstatus(connect_) != CONNECTION_OK) {
		//throw std::logic_error("No connection to database with connectionString = " + connectionString);
	}
}

void Database::insertQuery(const std::string& query) {
	PQsendQuery(connect_, query.c_str());
}
