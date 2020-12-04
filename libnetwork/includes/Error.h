#pragma once

#include <cerrno>
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>

class Error {
public:
	static void error(const char *msg);
	static void error(const std::string& msg);
};


#ifndef FILE_NAME
#define FILE_NAME __FILE__
#endif

#define ERROR(msg) { \
	ostringstream	ss;\
	ss << FILE_NAME << ":" \
	<< __LINE__ << " error\n" << msg;\
	Error::error(ss.str());\
}

