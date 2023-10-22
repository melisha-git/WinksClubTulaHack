#pragma once

#include "Database.hpp"
#include <string>
#include <vector>

class ML {
private:
	Database db_;
	std::string inputTable_;
	std::string outputTable_;
public:
	ML(const std::string& connectionString);

	std::vector<int> getTagsFromUserID(int userID);
	void addUserTagIDs(int userID, const std::vector<int> &tagIDs);
	void addUserTagID(int userID, int tagID);
	void createLastClick(int userID, std::vector<int> lastClicks);
	void updateLastClick(int userID, std::vector<int> lastClicks);
};