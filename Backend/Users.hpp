#pragma once

#include "Database.hpp"
#include <vector>

class Database;

class Users {
private:
	Database db_;
public:
	Users(const std::string &connectionString);
	~Users() = default;
	std::vector<int> getEventsIDFromUserID(int userID);
	std::vector<int> getEventsIDFromLogin(const std::string &login);
	void addNewUser(const std::string &login, const std::string &password);
	boost::json::value getUserIDByCreds(const std::string& login, const std::string& password);
};