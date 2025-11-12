#include "DataRequester.hpp"
#include <iostream>
#include "../utils/JUNK.hpp"

DataRequester &DataRequester::set_port(int port){
    this->port=port;
    return *this;
}

DataRequester &DataRequester::set_ip(std::string ip){
    this->ip=ip;
    return *this;
}

DataRequester &DataRequester::configure(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw std::runtime_error("Create socket error");
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(this->port);  // Portul serverului
    
    if (inet_pton(AF_INET,this->ip.c_str(), &server_address.sin_addr) <= 0) {
        close(sock);
        throw std::runtime_error("invalid ip");
    }
    return *this;
}

std::string DataRequester::sent_request(std::string data)
{
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        close(sock);
        throw std::runtime_error("connection faild");
    }

    std::string text = this->login_request("sau","as");
    int size = text.size();

   
    send(sock, &size, sizeof(int), 0);
    

    send(sock, text.c_str(), size, 0);
    
    std::cout << "Am trimis: " << text << " (size: " << size << ")" << std::endl;

    
    int received_size = 0;
    
    recv(sock, &received_size, sizeof(int), 0);
    char buffer[4096] = {0};
    if (received_size > 0 && received_size < 4096) {
        recv(sock, buffer, received_size, 0);
        std::cout<<"am primit "<<buffer<<std::endl; 
        JUNK::deserialize(buffer).display();
    }

    close(sock);
    return buffer;
}
