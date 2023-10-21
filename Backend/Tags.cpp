#include "Tags.hpp"

Tags::Tags(const std::string& connectionString) : db_(connectionString) {

}

boost::json::value Tags::getTagByID(int tagID) {
	auto tag = db_.selectDml("SELECT * from tags where id = " + std::to_string(tagID));
	return tag.at(0);
}
