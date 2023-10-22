#include "Connector.hpp"
#include <string>

Connector::Connector(boost::asio::ip::tcp::socket socket) 
    : socket_(std::move(socket)), db_("94.103.86.64", "5432", "postgres", "postgres", "1234"),
        users_(db_.getConnectionString()), events_(db_.getConnectionString()), tags_(db_.getConnectionString()), ml_(db_.getConnectionString()) {

}

void Connector::start() {
    reading();
    checkDeadline();
}

void Connector::reading()  {
    boost::beast::http::async_read(socket_, buffer_, request_, [&](auto ec, auto bytes) {
    std::cout << "Read " << bytes << " bytes\n";
    if (!ec)
        this->parseRequest();
    });
}

void Connector::parseRequest() {
    response_.version(request_.version());
    response_.keep_alive(false);
    response_.set(boost::beast::http::field::server, "Winks Club");

    switch (request_.method()) {
    case boost::beast::http::verb::get:
        response_.result(boost::beast::http::status::ok);
        response_.set(boost::beast::http::field::content_type, "application/json");
        createGetResponse();
        break;
    case boost::beast::http::verb::post:
        response_.result(boost::beast::http::status::ok);
        response_.set(boost::beast::http::field::content_type, "application/json");
        createPostResponse();
        break;
    default:
        response_.result(boost::beast::http::status::bad_request);
        response_.set(boost::beast::http::field::content_type, "text/plain");
        break;
    }
    response_.set(boost::beast::http::field::access_control_allow_origin, "*");
    response_.set(boost::beast::http::field::access_control_allow_headers, "content-type");
    writeResponse();
}

void Connector::createGetResponse() {
    if (request_.target() == "/api/events" || (request_.target().find("/api/events") != std::string::npos && request_.target().find('?') != std::string::npos)) {
        try {
            int userId = -1;
            int eventID = -1;
            std::string login = "";
            bool isChatId = false;
            if (request_.target().find('?') != std::string::npos) {
                std::string query = request_.target();
                if (request_.target().find("id") != std::string::npos) {
                    query = query.substr(query.find('=') + 1);
                    userId = std::stoi(query);
                }
                else if (request_.target().find("eventID") != std::string::npos) {
                    query = query.substr(query.find('=') + 1);
                    eventID = stoi(query);
                }
            }
            std::vector<int> eventIds;
            boost::json::array resultEvents;
            if (eventID != -1) {
                auto result = events_.getEventFromID(eventID);
                boost::json::object& jsonObject = result.as_object();
                auto tagIDs = events_.getTagsIDFromEventID(eventID);
                boost::json::array newTags;
                for (auto tagID : tagIDs) {
                    auto tag = tags_.getTagByID(tagID);
                    newTags.push_back(tag);
                }
                jsonObject.erase("tags");
                jsonObject["tags"] = newTags;
                jsonObject["type"] = jsonObject["type"] == "t" ? "event" : "hobby";
                resultEvents.push_back(result);
                boost::beast::ostream(response_.body()) << resultEvents;
                return;
            }
            if (userId != -1)
                eventIds = users_.getEventsIDFromUserID(userId);
            else
                eventIds = users_.getEventsIDFromLogin(login);
            for (auto eventId : eventIds) {
                auto event = events_.getEventFromID(eventId);
                boost::json::object& jsonObject = event.as_object();
                auto tagIDs = events_.getTagsIDFromEventID(eventId);
                boost::json::array newTags;
                for (auto tagID : tagIDs) {
                    auto tag = tags_.getTagByID(tagID);
                    newTags.push_back(tag);
                }
                jsonObject.erase("tags");
                jsonObject["tags"] = newTags;
                jsonObject["type"] = jsonObject["type"] == "t" ? "event" : "hobby";
                resultEvents.push_back(event);
            }
            boost::beast::ostream(response_.body()) << resultEvents;
        }
        catch (...) {}
    }
    else if (request_.target() == "/alltags") {
        auto tags = tags_.getAllTags();
        boost::beast::ostream(response_.body()) << tags;
    }
    else if (request_.target() == "/allevents") {
        boost::json::array resultEvents;
        auto events = events_.getAllEvents();
        for (auto &event : events) {
            boost::json::object& jsonObject = event.as_object();
            auto tagIDs = events_.getTagsIDFromEventID(std::stoi(jsonObject["id"].as_string().c_str()));
            boost::json::array newTags;
            for (auto tagID : tagIDs) {
                auto tag = tags_.getTagByID(tagID);
                newTags.push_back(tag);
            }
            jsonObject.erase("tags");
            jsonObject["tags"] = newTags;
            jsonObject["type"] = jsonObject["type"] == "t" ? "event" : "hobby";
            resultEvents.push_back(event);
        }
        boost::beast::ostream(response_.body()) << resultEvents;
    }
    else if (request_.target().find("chat/") != std::string::npos) {
        try {
            std::string numberString = request_.target();
            numberString = numberString.substr(numberString.find("chat/") + 5);
            int eventID = std::stoi(numberString);
            auto messages = events_.getChat(eventID);
            boost::beast::ostream(response_.body()) << messages;
        }
        catch (std::exception ex) {
            boost::beast::ostream(response_.body()) << ex.what();
        }
    }
    else if (request_.target() == "/api/recomendation" || ((request_.target().find("/api/recomendation") != std::string::npos && request_.target().find('?') != std::string::npos))) {
        int userId = -1;
        if (request_.target().find('?') != std::string::npos) {
            std::string query = request_.target();
            query = query.substr(query.find('=') + 1);
            userId = std::stoi(query);
        }
        boost::json::array mlRecomend;
        if (userId != -1)
            mlRecomend = ml_.getNextRecomended(userId);
        boost::beast::ostream(response_.body()) << mlRecomend;
    }
    else {
        response_.result(boost::beast::http::status::bad_request);
    }
    if (response_.body().size() == 0) {
        response_.result(boost::beast::http::status::bad_request);
        boost::beast::ostream(response_.body()) << boost::json::array();
    }
}

void Connector::createPostResponse() {
    if (request_.target() == "/register") {
        boost::json::object value = boost::json::parse(request_.body()).as_object();
        if (value.find("login") == value.end() || value.find("password") == value.end() || value.find("code") == value.end()) {
            response_.result(boost::beast::http::status::bad_request);
            return;
        }

        std::string login = value.at("login").as_string().c_str();
        std::string password = value.at("password").as_string().c_str();
        std::string inputCode = value.at("code").as_string().c_str();
        auto code = db_.selectDml("SELECT code FROM codes WHERE nickname = '" + login + "'");
        if (code.empty() || (code[0].as_object()["code"].as_string().c_str()) != inputCode) {
            response_.result(boost::beast::http::status::bad_request);
            return;
        }
        else {
            if (users_.getUserIDByLogin(login) != -1) {
                response_.result(boost::beast::http::status::bad_request);
                return;
            }
            users_.addNewUser(login, password);
            auto userID = users_.getUserIDByCreds(login, password);
            if (userID == -1)
                response_.result(boost::beast::http::status::bad_request);
            else {
                boost::json::object resultObject;
                resultObject["id"] = userID;
                boost::beast::ostream(response_.body()) << resultObject;
            }
        }
    }
    else if (request_.target() == "/login") {
        boost::json::object value = boost::json::parse(request_.body()).as_object();
        if (value.find("login") == value.end() || value.find("password") == value.end()) {
            response_.result(boost::beast::http::status::bad_request);
            return;
        }
        std::string login = value.at("login").as_string().c_str();
        std::string password = value.at("password").as_string().c_str();
        auto userID = users_.getUserIDByCreds(login, password);
        if (userID == -1)
            response_.result(boost::beast::http::status::bad_request);
        else {
            boost::json::object resultObject;
            resultObject["id"] = userID;
            boost::beast::ostream(response_.body()) << resultObject;
        }
    }
    else if (request_.target() == "/api/newevent") {
        boost::json::object value = boost::json::parse(request_.body()).as_object();
        if ((value.find("login") == value.end() && value.find("id") == value.end()) || value.find("name") == value.end() ||
            value.find("description") == value.end() || value.find("type") == value.end() || 
            value.find("image") == value.end() || value.find("begin_time") == value.end() || 
            value.find("end_time") == value.end() || value.find("subscribers") == value.end() ||
            value.find("max_subscribers") == value.end() || value.find("tags") == value.end()) {
            response_.result(boost::beast::http::status::bad_request);
            return;
        }
        try {
            int id = -1;
            std::string login = "";
            if (value.find("login") != value.end()) {
                login = value.at("login").as_string().c_str();
                id = users_.getUserIDByLogin(login);
            }
            else {
                id = value.at("id").as_int64();
                login = users_.getUserLoginByID(id);
            }
            std::string name = value.at("name").as_string().c_str();
            std::string description = value.at("description").as_string().c_str();
            std::string type = value.at("type").as_string().c_str();
            std::string image = value.at("image").as_string().c_str();
            std::string begin_time = value.at("begin_time").as_string().c_str();
            std::string end_time = value.at("end_time").as_string().c_str();
            unsigned subscribers = value.at("subscribers").as_int64();
            unsigned max_subscribers = value.at("max_subscribers").as_int64();
            auto tags = value.at("tags").as_array();
            std::vector<int> tagsVc;
            for (auto tag : tags) {
                boost::json::object jsObj = tag.as_object();
                if (jsObj.find("link") == jsObj.end()) {
                    std::cout << "END\n";
                }
                int tagID = tags_.getTagIDByLink(jsObj["link"].as_string().c_str());
                if (tagID != -1)
                    tagsVc.push_back(tagID);
            }
            events_.addNewEvents(name, description, type, image, begin_time, end_time, subscribers, max_subscribers, tagsVc);
            int eventId = events_.getEventIDbyTime(begin_time, end_time);
            if (users_.setNewEventFromUser(eventId, login))
                events_.updateEventSubscribers(subscribers + 1, eventId);
            boost::json::object resObj;
            resObj["eventID"] = eventId;
            ml_.addUserTagIDs(id, tagsVc);
            boost::beast::ostream(response_.body()) << resObj;
        }
        catch (std::exception ex) {
            std::string logMsg = ex.what();
            logMsg = "Error :" + logMsg;
            std::cout << logMsg << std::endl;
        }
    }
    else if (request_.target() == "/api/joinevent") {
        boost::json::object value = boost::json::parse(request_.body()).as_object();
        if (value.find("id") == value.end() || value.find("eventID") == value.end()) {
            response_.result(boost::beast::http::status::bad_request);
            return;
        }
        int eventID = value.at("eventID").as_int64();
        int id = value.at("id").as_int64();
        int sub = events_.getSubscribersByEventID(eventID);
        if (users_.setNewEventFromUser(eventID, id))
            events_.updateEventSubscribers(sub + 1, eventID);
        auto tags = events_.getTagsIDFromEventID(eventID);
        ml_.addUserTagIDs(id, tags);
        boost::json::object resultObject;
        resultObject["id"] = id;
        resultObject["eventID"] = eventID;
        boost::beast::ostream(response_.body()) << resultObject;
    }
    else if (request_.target() == "/api/sendmessage") {
        boost::json::object value = boost::json::parse(request_.body()).as_object();
        if (value.find("eventID") == value.end() || value.find("userID") == value.end() 
            || value.find("message") == value.end()) {
            response_.result(boost::beast::http::status::bad_request);
            return;
        }
        int eventID = value.at("eventID").as_int64();
        int userID = value.at("userID").as_int64();
        std::string message = value.at("message").as_string().c_str();
        events_.sendMessage(userID, eventID, message);
        boost::beast::ostream(response_.body()) << message;
    }
    else {
        response_.result(boost::beast::http::status::bad_request);
    }
    if (response_.body().size() == 0) {
        response_.result(boost::beast::http::status::bad_request);
        boost::beast::ostream(response_.body()) << boost::json::array();
    }
}

void Connector::writeResponse() {
    auto self = shared_from_this();

    response_.content_length(response_.body().size());

    boost::beast::http::async_write(socket_, response_, [self](boost::beast::error_code ec, std::size_t) {
        self->socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
        self->deadline_.cancel();
    });
}

void Connector::checkDeadline() {
    auto self = shared_from_this();

    deadline_.async_wait([self](boost::beast::error_code ec) {
        if (!ec) {
            self->socket_.close(ec);
        }
    });
}
