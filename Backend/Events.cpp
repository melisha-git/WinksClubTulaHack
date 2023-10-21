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
		name + "', '" + description + "', " + (type == "event" ? "true, '" : "false, '") + image + "', '" + beginTime + "', '" + endTime + "', " +
		std::to_string(subscribers) + ", " + std::to_string(maxSubscribers) + ", '{";
	for (int i = 0; i < tags.size(); ++i) {
		query += std::to_string(tags[i]);
		if (i + 1 < tags.size())
			query += ", ";
	}
	query += "}')";
	db_.execDml(query);
}

void Events::updateEventSubscribers(unsigned subscribers, int id) {
	std::string query = "UPDATE events SET subscribers = " + std::to_string(subscribers) + " WHERE id = " + std::to_string(id);
	db_.pqExecDml(query);
}

int Events::getEventIDbyTime(const std::string& begin_time, const std::string& end_time) {
	auto event = db_.selectDml("SELECT id FROM events WHERE begin_time = '" + begin_time + "' AND end_time = '" + end_time + "'");
	if (event.empty())
		return -1;
	return std::stoi(event.at(0).as_object()["id"].as_string().c_str());
}

boost::json::array Events::getAllEvents() {
	auto events = db_.selectDml("SELECT * FROM events");
	return events;
}

int Events::getSubscribersByEventID(int id) {
	auto subscribers = db_.selectDml("SELECT subscribers FROM events WHERE id = " + std::to_string(id));
	if (subscribers.empty())
		return -1;
	return std::stoi(subscribers.at(0).as_object()["id"].as_string().c_str());
}

