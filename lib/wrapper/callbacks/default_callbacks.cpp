#include "default_callbacks.hpp"
#include "../utils/utils.hpp"

static int cloud_socket = -1;
static struct sockaddr_in cloud_addr;

#define MAX_CONN_ADDRESS_LEN 64
static char overriddenAddress[MAX_CONN_ADDRESS_LEN + 1] = {0};
static int overriddenPort = 0;

void Callbacks_setConnectionOverride(bool override, char *address, int port)
{
    if (override)
    {
        strncpy(overriddenAddress, address, MAX_CONN_ADDRESS_LEN + 1);
        overriddenAddress[MAX_CONN_ADDRESS_LEN] = '\0';
        overriddenPort = port;
    }
    else
    {
        overriddenAddress[0] = '\0';
        overriddenPort = 0;
    }
}

int default_connect_udp_cb(const char *address, int port)
{

    int addr_family;
    int ip_protocol;
    char addr_str[128];

    struct hostent *res;

    // If address is overridden, it's an IP, don't resolve it with DNS
    if (strcmp(overriddenAddress, "") != 0)
    {
        address = overriddenAddress;
        port = overriddenPort;

        struct in_addr addr = {.s_addr = inet_addr(address)};
        res = gethostbyaddr(&addr, sizeof(struct in_addr), AF_INET);
    }
    // else it's a domain, resolve it with DNS.
    else
    {
        res = gethostbyname(address);
    }

    if (res)
    {
        log({"Dns address resolved: ", address});
        // EXAMPLE_LOG("Dns address %s resolved\n", address);
    }
    else
    {
        log({"error resolving gethostbyname: ", address});
        // EXAMPLE_LOG("error resolving gethostbyname %s\n", address);
        return -1;
    }

    // cloud_addr.sin_addr.s_addr = inet_addr(address);
    memcpy(&cloud_addr.sin_addr.s_addr, res->h_addr, sizeof(cloud_addr.sin_addr.s_addr));

    cloud_addr.sin_family = AF_INET;
    cloud_addr.sin_port = htons(port);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    memcpy(addr_str, inet_ntoa(cloud_addr.sin_addr), sizeof(addr_str) - 1);
    addr_str[sizeof(addr_str) - 1] = '\0';

    cloud_socket = socket(addr_family, SOCK_DGRAM, ip_protocol);
    if (cloud_socket < 0)
    {
        log({"Unable to create socket: errno: ", std::to_string(errno)});
        // EXAMPLE_LOG("Unable to create socket: errno %d\n", errno);
        return -3;
    }
    log({"Socket created, sending to: ", address, " : ", std::to_string(port)});
    // EXAMPLE_LOG("Socket created, sending to %s:%d\n", address, port);

    // setto i timeout di lettura/scrittura del socket
    struct timeval socket_timeout;
    socket_timeout.tv_sec = 0;
    socket_timeout.tv_usec = 1000; // 1ms
    setsockopt(cloud_socket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&socket_timeout, sizeof(struct timeval));

    return 1;
}

int default_disconnect_udp_cb()
{
    if (cloud_socket)
    {
        close(cloud_socket);
        cloud_socket = -1;
    }
    return 1;
}

int default_send_udp_cb(const unsigned char *buf, uint32_t buflen, void *tmp)
{
    log({"Called send_cb_udp "});
    size_t sent = sendto(cloud_socket, (const char *)buf, buflen, 0, (struct sockaddr *)&cloud_addr, sizeof(cloud_addr));
    if ((int)sent > 0)
    {
        log({"send_cb_udp sent: ", std::to_string(sent)});
        // EXAMPLE_LOG("send_cb_udp sent %d\n", sent);
    }

    return (int)sent;
}

int default_receive_udp_cb(unsigned char *buf, uint32_t buflen, void *tmp)
{
    size_t res = recvfrom(cloud_socket, (char *)buf, buflen, 0, (struct sockaddr *)NULL, NULL);
    if ((int)res > 0)
    {
        log({"receive_cb_udp received: ", std::to_string(res)});
    }

    // on timeout error, set bytes received to 0
    if ((int)res < 0 && errno == EAGAIN)
    {
        res = 0;
    }

    return (int)res;
}