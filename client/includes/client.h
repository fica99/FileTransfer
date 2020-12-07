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
#include "FileClient.h"
#include "Datagram.h"
#include "File.h"
#include "Header.h"
#include "CRC.h"
#include "LogInfo.h"

#define DATAGRAM_SIZE 1472
#define PUT_TYPE 1
