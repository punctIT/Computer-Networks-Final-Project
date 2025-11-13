#include "ConnectionServer.hpp"
#include "request_handler/RequestHandler.hpp"
#include "session_manager/SessionManager.hpp"
#include "session_manager/AuthManager.hpp"
#include <iostream>
#include <format>

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
    this->session_manager = std::make_shared<SessionManager>();
    this->auth = std::make_shared<AuthManager>();
    this->request_handler=std::make_shared<RequestHandler>(session_manager,auth);

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
        std::cout<<"New Client Connected"<<std::endl;
        std::thread([client,this](){
            while(true){
                int len = 0;
                char buffer[4096] = {0};
                ssize_t bytes_read = read(client, &len, sizeof(int));
                if (bytes_read <= 0) {
                    std::cout<<"Client Disconedted"<<std::endl;
                    break;
                }
                read(client, buffer, len);
                auto response =request_handler->match_request(client,buffer);
                if(response){
                    len = (*response).size();
                    write(client, &len, sizeof(int));
                    write(client, (*response).c_str(), len);
                }
                else {
                    std::string error = std::format("succes:{};type:{{error}};content:{{{}}};","false",response.error());
                    len = error.size();
                    write(client, &len, sizeof(int));
                    write(client, error.c_str(), len);
                }
            }
           

            close(client);
        }).detach(); 
        
       
    }
    return *this;

}

ConnectionServer::~ConnectionServer()
{
}
