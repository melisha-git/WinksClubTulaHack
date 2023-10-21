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
};