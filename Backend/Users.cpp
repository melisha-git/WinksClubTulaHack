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
    auto selectResult = db_.selectDml("SELECT events from users where login = '" + login + "'");
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

int Users::getUserIDByCreds(const std::string& login, const std::string& password) {
    auto users = db_.selectDml("SELECT id FROM users WHERE login = '" + login + "' AND password = '" + password + "'");
    if (users.empty())
        return -1;
    return std::stoi(users.at(0).as_object()["id"].as_string().c_str());
}

int Users::getUserIDByLogin(const std::string& login) {
    auto users = db_.selectDml("SELECT id FROM users WHERE login = '" + login + "'");
    if (users.empty())
        return -1;
    return std::stoi(users.at(0).as_object()["id"].as_string().c_str());
}

std::string Users::getUserLoginByID(int id) {
    auto users = db_.selectDml("SELECT login FROM users WHERE id = " + std::to_string(id));
    if (users.empty())
        return "";
    return users.at(0).as_object()["login"].as_string().c_str();
}

bool Users::setNewEventFromUser(int eventID, const std::string& login) {
    auto userEvents = getEventsIDFromLogin(login);
    if (std::find(userEvents.begin(), userEvents.end(), eventID) != userEvents.end())
        return false;
    userEvents.push_back(eventID);
    std::string query = "UPDATE users SET events = '{";
    for (int i = 0; i < userEvents.size(); ++i) {
        query += std::to_string(userEvents[i]);
        if (i + 1 < userEvents.size())
            query += ", ";
    }
    query += "}' WHERE login = '" + login + "'";
    db_.pqExecDml(query);
    return true;
}

bool Users::setNewEventFromUser(int eventID, int id) {
    auto userEvents = getEventsIDFromUserID(id);
    if (std::find(userEvents.begin(), userEvents.end(), eventID) != userEvents.end())
        return false;
    userEvents.push_back(eventID);
    std::string query = "UPDATE users SET events = '{";
    for (int i = 0; i < userEvents.size(); ++i) {
        query += std::to_string(userEvents[i]);
        if (i + 1 < userEvents.size())
            query += ", ";
    }
    query += "}' WHERE id = " + std::to_string(id);
    db_.pqExecDml(query);
    return true;
}
