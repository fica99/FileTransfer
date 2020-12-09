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
#include <algorithm>
#include <random>
#include "Socket.h"
#include "AddrInfo.h"
#include "Datagram.h"
#include "File.h"
#include "Header.h"
#include "CRC.h"
#include "LogInfo.h"
#include "Send.h"
#include "Recv.h"
#include "Deserialize.h"

#define DATAGRAM_SIZE 1472
#define RECV_TIMEOUT_SEC 0
#define RECV_TIMEOUT_MICROSEC 500000
#define PUT_TYPE 1
#define ACK_TYPE 0


/*
**									createFile.cpp
*/
File								createFile(const std::string& filename);
/*
**									sendDatagram.cpp
*/
void								sendDatagram(Socket& sock,
													const Datagram& datagram);
/*
**									sendFiles.cpp
*/
void								sendFiles(const char *ip, const char *serv_port,
										std::vector<std::string> filenames);

