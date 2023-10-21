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

std::vector<int> Users::getEventsIDFromLogin(const std::string& login) {
    auto selectResult = db_.selectDml("SELECT events from users where login = " + login);
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

void Users::addNewUser(const std::string& login, const std::string& password) {
    db_.execDml("INSERT INTO users(login, password) VALUES('" + login + "', '" + password + "')");
}

boost::json::value Users::getUserIDByCreds(const std::string& login, const std::string& password) {
    auto users = db_.selectDml("SELECT id FROM users WHERE login = '" + login + "' AND password = '" + password + "'");
    boost::json::value value;
    if (users.empty())
        return value;
    return users.at(0);
}
