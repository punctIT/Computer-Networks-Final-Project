#include "DataRequester.hpp"
#include <iostream>
#include "../utils/JUNK.hpp"
#include <format>
DataRequester::DataRequester(){
    token=std::nullopt;
    connected=false;
}

DataRequester &DataRequester::set_port(int port){
    this->port=port;
    return *this;
}

DataRequester &DataRequester::set_ip(std::string ip){
    this->ip=ip;
    return *this;
}

void DataRequester::set_token(std::string token){
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
    connected=true;
    return *this;
}

std::expected<std::string,std::string> DataRequester::sent_request(std::string data){  
    if(!connected){
        return std::unexpected("Error , connection error");
    }
    std::string content = "";
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
        int remaining = received_size;
        while (remaining > 0) {
            int chunk = std::min(remaining, 4096);
            int bytes_read = recv(sock, buffer, chunk, 0);
            if (bytes_read <= 0) {
                break;
            }
            content.append(buffer, bytes_read);
            remaining -= bytes_read;
        }
        return content;
    }
    else {
        return std::unexpected(test_data.error());
    }
    
}
