#include "DataProcessingServer.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <client_port> <display_host> <display_port>" << std::endl;
        return 1;
    }

    int client_port = std::atoi(argv[1]);
    std::string display_host = argv[2];
    int display_port = std::atoi(argv[3]);
    DataProcessingServer server(client_port, display_host, display_port);
    server.start();
    return 0;
}