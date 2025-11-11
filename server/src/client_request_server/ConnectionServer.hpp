#pragma once 
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <optional>

class ConnectionServer
{
private:
    std::optional<int> server_fd, client;
    sockaddr_in address;
    int opt = 1;
    std::optional<int> port;
    
public:
    ConnectionServer();
    ConnectionServer& set_port(int port);
    ConnectionServer& bind_data();
    ConnectionServer& start();
    ~ConnectionServer();
};

