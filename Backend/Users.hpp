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
	int getUserIDByCreds(const std::string& login, const std::string& password);
	int getUserIDByLogin(const std::string& login);
	std::string getUserLoginByID(int id);

	bool setNewEventFromUser(int eventID, const std::string& login);
	bool setNewEventFromUser(int eventID, int id);
};