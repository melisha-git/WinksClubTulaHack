#include "Database.hpp"
#include <stdexcept>
#include <sstream>

boost::json::array tokenize(std::string const& str, const char delim) {
	std::stringstream ss(str);
	boost::json::array out;

	std::string s;
	while (std::getline(ss, s, delim)) {
		out.push_back(boost::json::string(s));
	}
	return out;
}

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
		throw std::logic_error("No connection to database with connectionString = " + connectionString);
	}
}

void Database::execDml(const std::string& query) {
	PQsendQuery(connect_, query.c_str());
}

boost::json::array Database::selectDml(const std::string& query) {
	PQsendQuery(connect_, query.c_str());
	auto queryResult = PQgetResult(connect_);
	int turple = PQntuples(queryResult);
	int results = PQnfields(queryResult);
	boost::json::array selectResult;
	for (int i = 0; i < turple; ++i) {
		boost::json::object jsonObj;
		for (int j = 0; j < results; ++j) {
			std::string name = PQfname(queryResult, j);
			auto type = PQftype(queryResult, j);
			switch (type) {
			case 1007:
			case 600:
			case 1015: {
				std::string str = PQgetvalue(queryResult, i, j);
				boost::json::array elem = tokenize(str.substr(1, str.size() - 2), ',');
				jsonObj[name] = elem;
				break;
			}
			default:
				auto elem = PQgetvalue(queryResult, i, j);
				jsonObj[name] = elem;
				break;
			}
		}
		selectResult.push_back(jsonObj);
	}
	return selectResult;
}