#pragma once

#include "Database.hpp"
#include <vector>

class Events {
private:
	Database db_;
public:
	Events(const std::string& connectionString);
	~Events() = default;

	boost::json::value getEventFromID(int eventID);
	std::vector<int> getTagsIDFromEventID(int eventID);
};