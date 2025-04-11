#ifndef DISPLAY_SERVER_HPP
#define DISPLAY_SERVER_HPP

#include "SocketWrapper.hpp"

class DisplayServer {
public:
    DisplayServer(int port);
    void start();

private:
    SocketWrapper socket;
    int port;
};

#endif