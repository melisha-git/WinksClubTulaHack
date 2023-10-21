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
	void addNewEvents(const std::string& name, const std::string& description,
		const std::string& type, const std::string& image,
		const std::string& beginTime, const std::string& endTime,
		unsigned subscribers, unsigned maxSubscribers, std::vector<int> tags);
	void updateEventSubscribers(unsigned subscribers, int id);
	int getEventIDbyTime(const std::string &begin_time, const std::string& end_time);
};