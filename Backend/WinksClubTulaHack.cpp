#include "Server.hpp"

int main() {
	std::setlocale(LC_ALL, "Russia");
	//94.103.86.64
	Server s("94.103.86.64", 8080);
	s.start();
}
