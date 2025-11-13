#include "server_request/DataRequester.hpp"
#include <iostream>
#include "utils/JUNK.hpp"
int  main(){
    DataRequester data;
    try{
        data.set_ip("127.0.0.1").set_port(8080).configure();
    }
    catch (std::exception &e ){
        std::cerr<<e.what()<<std::endl;
    }
    while(true){
        std::cout<<"introudcei comanda \n";
        std::string cmd ;
        getline(std::cin, cmd);
        auto response = data.sent_request(cmd);
        if(response){
            std::string resp = response.value();
            auto data_junk = JUNK::deserialize(resp);
            if(data_junk){
                (*data_junk).display();
                if((*data_junk)["type"].has_value()&&(*data_junk)["type"].value()=="login"){
                    data.set_token((*data_junk)["content"].value());
                }
            }
            //std::cout<<*response<<std::endl;
        }
        else {
            std::cerr<<response.error()<<std::endl;
        }
    }
    
}