#include "client_request_server/ConnectionServer.hpp"
#include <iostream>

int main(){
    ConnectionServer http_server;
    try{
        http_server.set_port(8080)
                   .bind_data()
                   .start();
    }catch(std::exception &e){
        std::cerr<<e.what()<<std::endl;
    }
}