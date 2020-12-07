#pragma once

#include <stdio.h>

#define FILE_LINE() { printf("(%s:%d) ", __FILE__, __LINE__);}
#define LOG_INFO(x, s, ...) { if (x) {printf("[INFO] ");\
					FILE_LINE();\
					printf(s, __VA_ARGS__);} }
