#ifndef DATA_PROCESSING_SERVER_HPP
#define DATA_PROCESSING_SERVER_HPP

#include "SocketWrapper.hpp"
#include <string>
#include <set>

class DataProcessingServer {
public:
    DataProcessingServer(int client_port, const std::string& display_host, int display_port);
    void start();
    std::string processData(const std::string& input);

private:
    SocketWrapper client_socket;
    SocketWrapper display_socket;
    int client_port;
    std::string display_host;
    int display_port;
};

#endif