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


#define DATAGRAM_SIZE 1472
#define PUT_TYPE 1
#define ACK_TYPE 0

/*
**				datagramHandle.cpp
*/
Datagram	getDatagram(const Socket& sock);
void			addDatagram(std::vector<File>& files,
					const Datagram& datagram);
