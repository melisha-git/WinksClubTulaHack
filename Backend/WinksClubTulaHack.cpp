#include "Server.hpp"

int main() {
	std::setlocale(LC_ALL, "Russia");
	Server s("127.0.0.1", 8080);
	s.start();
}
