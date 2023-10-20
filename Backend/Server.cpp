#include "Server.hpp"
#include "Connector.hpp"

Server::Server() 
	: address_(boost::asio::ip::make_address("0.0.0.0")), port_(0000),
	context_(1), acceptor_(context_, { address_, port_ }), socket_(context_) {}

Server::Server(const std::string& ip, unsigned short port) 
	: address_(boost::asio::ip::make_address(ip)), port_(port),
	context_(1), acceptor_(context_, { address_, port_ }), socket_(context_) {}

Server::Server(const boost::asio::ip::address& address, unsigned short port) 
	: address_(address), port_(port), 
	context_(1), acceptor_(context_, {address_, port_}), socket_(context_) {
}

void Server::init(const std::string& ip, unsigned short port) {
	address_ = boost::asio::ip::make_address(ip);
	port_ = port;
	acceptor_.bind({ address_, port_ });
}

void Server::init(const boost::asio::ip::address& address, unsigned short port) {
	address_ = address;
	port_ = port;
	acceptor_.bind({ address_, port_ });
}

void Server::start() {
    accept();
    context_.run();
}

void Server::accept() {
    acceptor_.async_accept(socket_, [&](boost::beast::error_code ec) {
		if (!ec) {
			std::shared_ptr<Connector> connector;
			connector = std::make_shared<Connector>(std::move(socket_));
			connector->start();
		}
        accept();
    });
}