#include "ConnectionServer.hpp"


#include <iostream>

ConnectionServer::ConnectionServer(){
    std::cout<<"Starting http server for client"<<std::endl;
    port=std::nullopt;

}

ConnectionServer &ConnectionServer::set_port(int port){
   this->port=port;
   return *this;
}

ConnectionServer &ConnectionServer::bind_data(){
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw std::runtime_error("");
    }
    if (setsockopt(server_fd.value(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        throw std::runtime_error("");
    }
    if (!this->port.has_value()){
        throw std::runtime_error("Error , port is none");
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port.value());

    if (bind(server_fd.value(), (struct sockaddr *)&address, sizeof(address)) < 0) {
        throw std::runtime_error("");
    }
    return *this;
}

ConnectionServer &ConnectionServer::start()
{
    if(!this->port.has_value()){
        throw std::runtime_error("Error , port is none");
    }
    if(!this->server_fd.has_value()){
        throw std::runtime_error("Server fd is none");
    }
    if (listen(server_fd.value(), 10) < 0) {
        throw std::runtime_error("listen failed");
    }
    
    std::cout << "Server started and listen on port 8080\n";

    while (true) {
        socklen_t addrlen = sizeof(address); 
        int client = accept(server_fd.value(), (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (client < 0) {
            perror("accept");
            continue;
        }
        std::string response= "salut";
        std::thread([client,response](){
            char buffer[4096] = {0};
            read(client, buffer, sizeof(buffer) - 1);
            std::cout << "Cerere primită:\n" << buffer << "\n";
            
            int len = response.size();
            write(client, response.c_str(), response.size());
            write(client, response.c_str(), response.size());

            close(client);
        }).detach(); 
        
       
    }
    return *this;

}

ConnectionServer::~ConnectionServer()
{
}
