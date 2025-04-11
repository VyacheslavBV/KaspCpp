#include "Client.hpp"
#include <iostream>

Client::Client(const std::string& host, int port) : host(host), port(port) {}

void Client::start() {
    try {
        socket.createSocket();
        socket.connect(host, port);
        std::cout << "Connected to server " << host << ":" << port << std::endl;

        std::string input;
        while (true) {
            std::cout << "Enter data (or Ctrl+C to exit): ";
            std::getline(std::cin, input);
            if (input.empty()) {
                continue;
            }
            try {
                socket.send(input);
                std::cout << "Sent data: " << input << std::endl;
                std::string ack = socket.receive();
                if (ack.empty()) {
                    std::cout << "Server disconnected" << std::endl;
                    break;
                }
                std::cout << "Server acknowledged: " << ack << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Communication error: " << e.what() << std::endl;
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Client error: " << e.what() << std::endl;
    }
    socket.close();
}