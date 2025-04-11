#include "DisplayServer.hpp"
#include <iostream>

DisplayServer::DisplayServer(int port) : port(port) {}

void DisplayServer::start() {
    try {
        socket.createSocket();
        socket.bind(port);
        socket.listen();
        std::cout << "Display server listening on port " << port << std::endl;

        while (true) {
            SOCKET_TYPE client_fd = socket.accept();
            SocketWrapper client(client_fd);
            std::cout << "New connection to display server" << std::endl;

            while (true) {
                try {
                    std::string data = client.receive();
                    if (data.empty()) {
                        std::cout << "Display client disconnected" << std::endl;
                        break;
                    }
                    std::cout << "Received result: " << data << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "Error receiving data: " << e.what() << std::endl;
                    break;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Display server error: " << e.what() << std::endl;
    }
}