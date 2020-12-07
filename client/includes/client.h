#pragma once

#include <unistd.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstddef>
#include <limits>
#include <future>
#include "Socket.h"
#include "AddrInfo.h"
#include "Datagram.h"
#include "File.h"
#include "Header.h"
#include "CRC.h"
#include "LogInfo.h"
#include "Send.h"

#define DATAGRAM_SIZE 1472
#define PUT_TYPE 1


/*
**									createFiles.cpp
*/
std::vector<File>		createFiles(std::vector<std::string> filenames);
/*
**									sendFiles.cpp
*/
void								sendFiles(const char *ip, const char *serv_port,
										std::vector<File> files);
