#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <string>

class Server {
private:
	boost::asio::ip::address address_;
	unsigned short port_;
	boost::asio::io_context context_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
public:
	Server();
	Server(const std::string &ip, unsigned short port);
	Server(const boost::asio::ip::address& address, unsigned short port);
	void init(const std::string& ip, unsigned short port);
	void init(const boost::asio::ip::address &address, unsigned short port);
	void start();

private:
	void accept();
};