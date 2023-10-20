#include "Server.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

int main() {
	Server s("127.0.0.1", 8080);
	s.start();
}
