#include "SocketWrapper.hpp"
#include <iostream>

SocketWrapper::SocketWrapper() : sockfd(INVALID_SOCKET) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
#endif
}

SocketWrapper::SocketWrapper(SOCKET_TYPE fd) : sockfd(fd) {
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        throw std::runtime_error("WSAStartup failed");
    }
#endif
}

SocketWrapper::~SocketWrapper() {
    close();
#ifdef _WIN32
    WSACleanup();
#endif
}

void SocketWrapper::createSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        throw std::runtime_error("Failed to create socket");
    }
    
    /*
    #ifdef _WIN32
    DWORD timeout = 5000;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
    #endif
    */
}

void SocketWrapper::bind(int port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(sockfd, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind failed");
    }
}

void SocketWrapper::listen(int backlog) {
    if (::listen(sockfd, backlog) == SOCKET_ERROR) {
        throw std::runtime_error("Listen failed");
    }
}

SOCKET_TYPE SocketWrapper::accept() {
    sockaddr_in client_addr;
#ifdef _WIN32
    int addr_len = sizeof(client_addr);
#else
    socklen_t addr_len = sizeof(client_addr);
#endif
    SOCKET_TYPE client_fd = ::accept(sockfd, (sockaddr*)&client_addr, &addr_len);
    if (client_fd == INVALID_SOCKET) {
        throw std::runtime_error("Accept failed");
    }
    return client_fd;
}

void SocketWrapper::connect(const std::string& host, int port) {
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
#ifdef _WIN32
    addr.sin_addr.s_addr = inet_addr(host.c_str());
#else
    addr.sin_addr.s_addr = inet_addr(host.c_str());
#endif

    if (::connect(sockfd, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        throw std::runtime_error("Connect failed");
    }
}

void SocketWrapper::send(const std::string& data) {
    int bytes_sent = ::send(sockfd, data.c_str(), static_cast<int>(data.size()), 0);
    if (bytes_sent == SOCKET_ERROR) {
        #ifdef _WIN32
        std::cerr << "SE code: " << WSAGetLastError() << std::endl;
        #endif
        throw std::runtime_error("Send failed");
    }
    std::cout << "Sent " << bytes_sent << " bytes" << std::endl;
}

std::string SocketWrapper::receive() {
    char buffer[1024] = {0};
    int bytes_received = ::recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == SOCKET_ERROR) {
        #ifdef _WIN32
        std::cerr << "RE code: " << WSAGetLastError() << std::endl;
        #endif
        throw std::runtime_error("Receive failed");
    }
    if (bytes_received == 0) {
        std::cout << "Connection closed" << std::endl;
        return "";
    }
    std::cout << "Received " << bytes_received << " bytes" << std::endl;
    return std::string(buffer, bytes_received);
}

void SocketWrapper::close() {
    if (sockfd != INVALID_SOCKET) {
        #ifdef _WIN32
        ::closesocket(sockfd);
        #else
        ::close(sockfd);
        #endif
        sockfd = INVALID_SOCKET;
    }
}