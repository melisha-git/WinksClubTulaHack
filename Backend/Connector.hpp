#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/json.hpp>
#include <iostream>

class Connector : public std::enable_shared_from_this<Connector> {
private:
    boost::asio::ip::tcp::socket socket_;

    boost::beast::flat_buffer buffer_{8192};
    boost::beast::http::request<boost::beast::http::string_body> request_;
    boost::beast::http::response<boost::beast::http::dynamic_body> response_;

    boost::asio::steady_timer deadline_{socket_.get_executor(), std::chrono::seconds(60)};
public:
    Connector(boost::asio::ip::tcp::socket socket);
    void start();

private:

    void reading();
    void parseRequest();
    void createResponse();
    void writeResponse();

    void checkDeadline();
};