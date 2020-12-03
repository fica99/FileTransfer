#pragma once

#include <cerrno>
#include <cstdio>
#include <string>
#include <iostream>

class Error {
public:
	Error(const char *msg);
	Error(const std::string& msg);
};
