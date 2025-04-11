#include "DataProcessingServer.hpp"
#include <sstream>
#include <iostream>

DataProcessingServer::DataProcessingServer(int client_port, const std::string& display_host, int display_port)
    : client_port(client_port), display_host(display_host), display_port(display_port) {}

std::string DataProcessingServer::processData(const std::string& input) {
    std::istringstream iss(input);
    std::set<std::string> unique_words;
    std::string word;

    while (iss >> word) {
        unique_words.insert(word);
    }

    std::ostringstream oss;
    for (const auto& w : unique_words) {
        oss << w << " ";
    }
    return oss.str();
}

void DataProcessingServer::start() {
    try {
        client_socket.createSocket();
        client_socket.bind(client_port);
        client_socket.listen();
        std::cout << "Processing server listen port " << client_port << std::endl;

        display_socket.createSocket();
        display_socket.connect(display_host, display_port);
        std::cout << "Connected display server " << display_host << ":" << display_port << std::endl;

        while (true) {
            SOCKET_TYPE client_fd = client_socket.accept();
            SocketWrapper client(client_fd);
            std::cout << "New client connected" << std::endl;

            while (true) {
                try {
                    std::string data = client.receive();
                    if (data.empty()) {
                        std::cout << "Client disconnected" << std::endl;
                        break;
                    }
                    std::cout << "Received from client: " << data << std::endl;

                    try {
                        client.send("ACK");
                        std::cout << "Sent ACK to client" << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Failed to send ACK: " << e.what() << std::endl;
                        break;
                    }

                    std::string processed = processData(data);
                    std::cout << "Processed data: " << processed << std::endl;

                    try {
                        display_socket.send(processed);
                        std::cout << "Sent result to display server" << std::endl;
                    } catch (const std::exception& e) {
                        std::cerr << "Failed to send to display server: " << e.what() << std::endl;
                        display_socket.close();
                        display_socket.createSocket();
                        display_socket.connect(display_host, display_port);
                        std::cout << "Reconnected to display server" << std::endl;
                        display_socket.send(processed);
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error handling client: " << e.what() << std::endl;
                    break;
                }
            }
            std::cout << "Client connection closed" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}