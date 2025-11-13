#include "RequestHandler.hpp"
#include "../session_manager/SessionManager.hpp"
#include "../session_manager/AuthManager.hpp"
#include "../../utils/JUNK.hpp"
#include <iostream>
#include <format>

std::expected<std::string,std::string> RequestHandler::match_request(int client,std::string request){
    std::cout << "Request: "<< request << std::endl;
    auto data = JUNK::deserialize(request);
    if(data){
        //(*data).display();
        if((*data).containts("type")){
            auto response = this->match_type(*data);
            if(response){
                return *response;
            }
            else {
                return RequestHandler::response_formater(false,"error",response.error());
            }
        }
        else{
            return std::unexpected("Invalid data: don t containt a type or token;");
        }
    }
    else {
        return std::unexpected(data.error());
    }
    

}

std::expected<std::string, std::string> RequestHandler::match_type(JUNK &request){
    if(request["type"].has_value()){
        if(request["type"].value()=="login"){
            request.display();
            if(request["username"].has_value()&&request["password"].has_value()){
                auto credentials_check=auth->check_credentials(request["username"].value(),request["password"].value());
                if(!credentials_check){
                    return std::unexpected("Auth Error");
                }
                if(*credentials_check){
                    std::string token = session->create_session(request["username"].value());
                    return RequestHandler::response_formater(true,"login",token);
                }
                return RequestHandler::response_formater(false,"login","Invalid username or password");
            }
            else {
                return std::unexpected("invalid format , username or password");
            } 
        }
        else{
            if(request["token"].has_value() && session->check_token(request["token"].value())){
                if(request["type"]=="ceva"){
                    return RequestHandler::response_formater(true,"ceva","nimic");
                }
            }
            else {
                return std::unexpected("Invalid Token");
            }
        }
    }
    return std::unexpected("unknown type");
}


std::string RequestHandler::response_formater(bool succes,std::string type ,std::string content)
{
    return std::format("succes:{{{}}};type:{{{}}};content:{{{}}};",succes,type,content);
}

RequestHandler::RequestHandler(std::shared_ptr<SessionManager> &session,std::shared_ptr<AuthManager> &auth)
    : session(session) ,auth(auth) {};