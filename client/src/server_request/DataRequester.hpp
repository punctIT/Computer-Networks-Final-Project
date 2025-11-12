#pragma once
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "ProtocolFormater.hpp"

class DataRequester:public ProtocolFormater{
    std::string ip;
    int port;
    int sock;
    struct sockaddr_in server_address;
    public:
    DataRequester& set_port(int port);
    DataRequester& set_ip(std::string ip);
    DataRequester& configure();
    std::string sent_request(std::string data);
};