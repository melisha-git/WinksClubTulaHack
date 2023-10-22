#include "ML.hpp"

ML::ML(const std::string& connectionString) 
	: db_(connectionString), inputTable_("input_ml"), outputTable_("output_ml") {}

boost::json::array ML::getTagsFromUserID(int userID) {
	auto inputs = db_.selectDml("SELECT last_clicks from " + inputTable_ + " WHERE user_id = " + std::to_string(userID));
	return inputs.at(0).as_object()["last_clicks"].as_array();
}

void ML::addUserTagIDs(int userID, const std::vector<int>& tagIDs) {
	for (auto id : tagIDs) {
		addUserTagID(userID, id);
	}
}

void ML::addUserTagID(int userID, int tagID) {
	auto inputs = getTagsFromUserID(userID);
	boost::json::value v(tagID);
	inputs.push_back(v);
	return updateLastClick(userID, inputs);
}

void ML::updateLastClick(int userID, boost::json::array lastClicks) {
	std::string query = "UPDATE " + inputTable_ + " SET last_clicks = '{";
	for (auto valID : lastClicks) {
		int id = valID.as_int64();
		if (valID != *(lastClicks.begin()))
			query += ", ";
		query += std::to_string(id);
	}
	query += "}' WHERE user_id = " + std::to_string(userID);
	db_.pqExecDml(query);
}
