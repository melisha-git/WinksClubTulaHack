#include "Tags.hpp"

Tags::Tags(const std::string& connectionString) : db_(connectionString) {

}

boost::json::value Tags::getTagByID(int tagID) {
	auto tag = db_.selectDml("SELECT * from tags where id = " + std::to_string(tagID));
	boost::json::value value;
	if (tag.empty())
		return value;
	return tag.at(0);
}

boost::json::value Tags::getTagByLink(const std::string& link) {
	auto tag = db_.selectDml("SELECT * from tags where link = '" + link + "'");
	boost::json::value value;
	if (tag.empty())
		return value;
	return tag.at(0);
}

int Tags::getTagIDByLink(const std::string& link) {
	auto tag = db_.selectDml("SELECT id from tags where link = '" + link + "'");
	if (tag.empty())
		return -1;
	return std::stoi(tag.at(0).as_object()["id"].as_string().c_str());
}
