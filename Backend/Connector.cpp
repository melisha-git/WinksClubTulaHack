#include "Connector.hpp"

Connector::Connector(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {

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

    switch (request_.method()) {
    case boost::beast::http::verb::get:
        response_.result(boost::beast::http::status::ok);
        response_.set(boost::beast::http::field::server, "Winks Club");
        createResponse();
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

void Connector::createResponse() {
    boost::json::array obj;
    obj.push_back(boost::json::string("Если Вы это читаете - Вы лучший!"));
    if (request_.target() == "/api") {
        response_.set(boost::beast::http::field::content_type, "application/json");
        boost::beast::ostream(response_.body()) << obj;
    }
    else {
        response_.result(boost::beast::http::status::not_found);
        response_.set(boost::beast::http::field::content_type, "text/plain");
        boost::beast::ostream(response_.body()) << "File not found\r\n";
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
