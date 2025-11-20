#pragma once
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "ProtocolFormater.hpp"
#include <optional>
#include <expected>

class DataRequester:public ProtocolFormater{
    std::string ip;
    int port;
    int sock;
    struct sockaddr_in server_address;
    bool connected;

    std::optional<std::string> token;
    public:
    DataRequester();
    DataRequester& set_port(int port);
    DataRequester& set_ip(std::string ip);
    void set_token(std::string);
    DataRequester& configure();
    std::expected<std::string,std::string> sent_request(std::string data);
};