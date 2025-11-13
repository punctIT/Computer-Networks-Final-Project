#include "DataRequester.hpp"
#include <iostream>
#include "../utils/JUNK.hpp"
#include <format>
DataRequester::DataRequester()
{
    token=std::nullopt;
}

DataRequester &DataRequester::set_port(int port)
{
    this->port=port;
    return *this;
}

DataRequester &DataRequester::set_ip(std::string ip){
    this->ip=ip;
    return *this;
}

void DataRequester::set_token(std::string token)
{
    this->token=token;
}

DataRequester &DataRequester::configure(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw std::runtime_error("Create socket error");
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(this->port);  
    
    if (inet_pton(AF_INET,this->ip.c_str(), &server_address.sin_addr) <= 0) {
        close(sock);
        throw std::runtime_error("invalid ip");
    }
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        close(sock);
        throw std::runtime_error("connection failed");
    }
    int size =0;
    std::string data = "type:{con};";
    size =data.size();
    send(sock, &size, sizeof(int), 0);
    send(sock, data.c_str(), size, 0);
    char buffer[100];
    recv(sock, &size, sizeof(int), 0);
    recv(sock, buffer,size, 0);
    return *this;
}

std::expected<std::string,std::string> DataRequester::sent_request(std::string data){  
    auto test_data = JUNK::deserialize(data);
    if (test_data){
        if(this->token.has_value()){
            data = std::format("token:{{{}}};{}",this->token.value(),data);
        }
        
        int size = data.size();
        send(sock, &size, sizeof(int), 0);
        send(sock, data.c_str(), size, 0);
    
        
        int received_size = 0;
        
        recv(sock, &received_size, sizeof(int), 0);
        char buffer[4096] = {0};
        if (received_size > 0 && received_size < 4096) {
            recv(sock, buffer, received_size, 0);
        }
        return buffer;
    }
    else {
        return std::unexpected(test_data.error());
    }
    
}
