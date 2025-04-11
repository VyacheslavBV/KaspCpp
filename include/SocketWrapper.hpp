#ifndef SOCKET_WRAPPER_HPP
#define SOCKET_WRAPPER_HPP

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "Ws2_32.lib")
    #define SOCKET_TYPE SOCKET
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define SOCKET_TYPE int
#endif

#include <string>
#include <stdexcept>

class SocketWrapper {
public:
    SocketWrapper();
    explicit SocketWrapper(SOCKET_TYPE fd);
    ~SocketWrapper();

    void createSocket();
    void bind(int port);
    void listen(int backlog = 10);
    SOCKET_TYPE accept();
    void connect(const std::string& host, int port);
    void send(const std::string& data);
    std::string receive();
    void close();

private:
    SOCKET_TYPE sockfd;
#ifdef _WIN32
    WSADATA wsaData;
#endif
};

#endif