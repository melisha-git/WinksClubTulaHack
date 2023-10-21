#include "Users.hpp"

Users::Users(const std::string& connectionString) : db_(connectionString) {

}

std::vector<int> Users::getEventsIDFromUserID(int userID) {
    auto selectResult = db_.selectDml("SELECT events from users where id = " + std::to_string(userID));
    if (selectResult.empty()) {
        return {};
    }
    std::vector<int> result;
    auto eventIds = selectResult.begin()->as_object()["events"].as_array();
    for (auto eventId : eventIds) {
        std::string sEventId = eventId.as_string().c_str();
        result.push_back(std::stoi(sEventId));
    }
    return result;
}
