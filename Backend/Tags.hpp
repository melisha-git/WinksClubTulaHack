#pragma once

#include "Database.hpp"

class Tags {
private:
	Database db_;
public:
	Tags(const std::string &connectionString);
	~Tags() = default;

	boost::json::value getTagByID(int tagID);
};