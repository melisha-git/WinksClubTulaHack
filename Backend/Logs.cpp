#include "Logs.hpp"
#include <filesystem>
#include <iostream>

Log::Log(const std::string& filepath, const std::string& fileName) 
	: filepath_(filepath), fileName_(fileName) {
	logFile_.open(filepath + fileName, std::ios::binary | std::ios::app);
	isOpen_ = true;
	if (!logFile_.is_open()) {
		std::cout << "Log File Not Open\n";
		isOpen_ = false;
	}
}

void Log::addLog(const std::string& msg) {
	std::cout << msg << std::endl;
	if (isOpen_)
		logFile_ << msg << std::endl;
}

Log::~Log() {
	if (isOpen_)
		logFile_.close();
}
