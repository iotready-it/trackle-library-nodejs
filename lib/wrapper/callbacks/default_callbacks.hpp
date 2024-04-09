#ifndef CALLBACKS_H_
#define CALLBACKS_H_

#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
typedef unsigned int uint32_t;

int default_send_udp_cb(const unsigned char *buf, uint32_t buflen, void *tmp);
int default_receive_udp_cb(unsigned char *buf, uint32_t buflen, void *tmp);
int default_connect_udp_cb(const char *address, int port);
void Callbacks_setConnectionOverride(bool override, char *address, int port);
int default_disconnect_udp_cb();

#endif