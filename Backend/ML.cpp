#include "ML.hpp"

ML::ML(const std::string& connectionString) 
	: db_(connectionString), inputTable_("input_ml"), outputTable_("output_ml") {}

std::vector<int> ML::getTagsFromUserID(int userID) {
	auto selectResult = db_.selectDml("SELECT last_clicks from input_ml where user_id = " + std::to_string(userID));
	if (selectResult.empty()) {
		return {};
	}
	std::vector<int> result;
	auto last_clicks = selectResult.begin()->as_object()["last_clicks"].as_array();
	for (auto clicks : last_clicks) {
		std::string sClick = clicks.as_string().c_str();
		result.push_back(std::stoi(sClick));
	}
	return result;
}

void ML::addUserTagIDs(int userID, const std::vector<int>& tagIDs) {
	auto inputs = getTagsFromUserID(userID);
	bool isNew_ = inputs.empty();
	for (auto id : tagIDs) {
		inputs.push_back(id);
	}
	if (isNew_)
		return createLastClick(userID, inputs);
	return updateLastClick(userID, inputs);
}

void ML::addUserTagID(int userID, int tagID) {
	auto inputs = getTagsFromUserID(userID);
	bool isNew_ = inputs.empty();
	inputs.push_back(tagID);
	if (isNew_)
		return createLastClick(userID, inputs);
	return updateLastClick(userID, inputs);
}

void ML::createLastClick(int userID, std::vector<int> lastClicks) {
	std::string query = "INSERT INTO input_ml(user_id, last_clicks) values(" + std::to_string(userID) + ", '{" + std::to_string(lastClicks[0]) + "}')";
	db_.execDml(query);
}

void ML::updateLastClick(int userID, std::vector<int> lastClicks) {
	std::string query = "UPDATE " + inputTable_ + " SET last_clicks = '{";
	for (int i = 0; i < lastClicks.size(); ++i) {
		query += std::to_string(lastClicks[i]);
		if (i + 1 < lastClicks.size())
			query += ", ";
	}
	query += "}' WHERE user_id = " + std::to_string(userID);
	db_.pqExecDml(query);
}

boost::json::array ML::getNextRecomended(int userID) {
	auto nextTags = db_.selectDml("SELECT next_tags from output_ml WHERE user_id = " + std::to_string(userID));
	return nextTags.at(0).as_object()["next_tags"].as_array();
}

