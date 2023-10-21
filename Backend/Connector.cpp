#include "Connector.hpp"
#include "Users.hpp"
#include "Events.hpp"
#include "Tags.hpp"

Connector::Connector(boost::asio::ip::tcp::socket socket) 
    : socket_(std::move(socket)), db_("94.103.86.64", "5432", "postgres", "postgres", "1234") {

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
        createGetResponse();
        break;
    case boost::beast::http::verb::post:
        response_.result(boost::beast::http::status::ok);
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
    if (request_.target() == "/api") {
        response_.set(boost::beast::http::field::content_type, "application/json");
    }
    else if (request_.target() == "/api/events") {
        try {
            response_.set(boost::beast::http::field::content_type, "application/json");
            boost::json::object value = boost::json::parse(request_.body()).as_object();
            int userId = value["id"].as_int64();
            Users users(db_.getConnectionString());
            Events events(db_.getConnectionString());
            Tags tags(db_.getConnectionString());
            auto eventIds = users.getEventsIDFromUserID(userId);
            for (auto eventId : eventIds) {
                auto event = events.getEventFromID(eventId);
                boost::json::object& jsonObject = event.as_object();
                auto tagIDs = events.getTagsIDFromEventID(eventId);
                boost::json::array newTags;
                for (auto tagID : tagIDs) {
                    auto tag = tags.getTagByID(tagID);
                    newTags.push_back(tag);
                }
                jsonObject.erase("tags");
                jsonObject["tags"] = newTags;
                jsonObject["type"] = jsonObject["type"] == "t" ? "event" : "hobby";
                boost::beast::ostream(response_.body()) << event;
            }
        }
        catch (...) {}
    }
    else {
        response_.result(boost::beast::http::status::not_found);
    }
    if (response_.body().size() == 0) {
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
            db_.execDml("INSERT INTO users(login, password) VALUES('" + login + "', '" + password + "')");
        }
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
