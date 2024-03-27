#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

void log(const std::initializer_list<std::string> &strings);
std::string extractBufferByte(const unsigned char *buf, uint32_t buflen);

#endif