#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "SocketWrapper.hpp"
#include <string>

class Client {
public:
    Client(const std::string& host, int port);
    void start();

private:
    SocketWrapper socket;
    std::string host;
    int port;
};

#endif