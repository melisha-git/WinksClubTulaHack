#include "Events.hpp"

Events::Events(const std::string& connectionString) : db_(connectionString) {

}

boost::json::value Events::getEventFromID(int eventID) {
	auto events = db_.selectDml("SELECT * from events WHERE id = " + std::to_string(eventID));
	return events.at(0);
}

std::vector<int> Events::getTagsIDFromEventID(int eventID) {
	std::vector<int> result;
	auto selectResult = db_.selectDml("SELECT tags from events where id = " + std::to_string(eventID));
	if (selectResult.empty()) {
		return {};
	}
	auto tagIDS = selectResult.begin()->as_object()["tags"].as_array();
	for (auto tagID : tagIDS) {
		std::string stagID = tagID.as_string().c_str();
		result.push_back(std::stoi(stagID));
	}
	return result;
}

void Events::addNewEvents(const std::string& name, const std::string &description,
	const std::string &type, const std::string& image, const std::string &beginTime,
	const std::string& endTime, unsigned subscribers, unsigned maxSubscribers,
	std::vector<int> tags) {
	std::string query = "insert into events(name, description, type, image, begin_time, end_time, subscribers, max_subscribers, tags) values('" +
		name + "', '" + description + "', '" + image + "', '" + beginTime + "', '" + endTime + "', " +
		std::to_string(subscribers) + ", " + std::to_string(maxSubscribers) + ", '{";
	for (auto i : tags) {
		query += i + ", ";
	}
	db_.execDml(query);
}

