#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cstring>
#include "AddrInfo.h"
#include "Socket.h"
#include "LogInfo.h"
#include "Bind.h"
#include "Datagram.h"
#include "Recv.h"
#include "File.h"
#include "CRC.h"
#include "Serialize.h"
#include "Send.h"

#define DATAGRAM_SIZE 1472
#define PUT_TYPE 1
#define ACK_TYPE 0


/*
**				addDatagram.cpp
*/
File&			addDatagram(std::vector<File>& files, const Datagram& datagram);
/*
**				confirmDatagram.cpp
*/
Datagram	confirmDatagram(File& file, const Datagram& datagram);
/*
**				getDatagram.cpp
*/
Datagram	getDatagram(Socket& sock);
/*
**				sendDatagram.cpp
*/
void			sendDatagram(Socket& sock, Datagram datagram);
