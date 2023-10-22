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

	boost::json::array getTagsFromUserID(int userID);
	void addUserTagIDs(int userID, const std::vector<int> &tagIDs);
	void addUserTagID(int userID, int tagID);
	void updateLastClick(int userID, boost::json::array lastClicks);
};