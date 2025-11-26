#include "RequestHandler.hpp"
#include "../session_manager/SessionManager.hpp"
#include "../session_manager/AuthManager.hpp"
#include "../../utils/JUNK.hpp"
#include "commands/Logs.hpp"
#include "commands/Auth.hpp"
#include <iostream>
#include <format>

std::expected<std::string,std::string> RequestHandler::match_request(int client,std::string request){
    //std::cout << "Request: "<< request << std::endl;
    auto data = JUNK::deserialize(request);
    if(!data.has_value()){
        return std::unexpected(data.error());
    }
    if(!(*data).contains("type")){
        return std::unexpected("Invalid data: don t containt a type");
    }
    auto response = this->match_type(*data);
    if(response){
        return *response;
    }
    else {
        return RequestHandler::response_formater(false,"Error",response.error());
    }
    

}

std::expected<std::string, std::string> RequestHandler::match_type(JUNK &request){
    if(!request["type"].has_value()){
        return std::unexpected("unknown type");
    }
    //request.display();
    const std::string type = request["type"].value();
    if(type=="login"){
        return auth_requests->login_request(request);
    }
    if(type=="register"){
        return auth_requests->register_request(request);
    }

    if(!request["token"].has_value() || !session->check_token(request["token"].value())){
        return std::unexpected("Invalid Token");
    }
    //std::cout<<type<<" "<<type.size()<<std::endl;;
    if(type=="ceva"){
        return response_formater(true,"ceva","nimic");
    }
    if(type=="logout"){
        return auth_requests->logout_request(request);
    }
    if(type=="logs"){
        return logs_requests->logs_request(request);
    }
    
    return std::unexpected("unknown type");
}


RequestHandler::RequestHandler(std::shared_ptr<SessionManager> &session, std::shared_ptr<AuthManager> &auth, std::shared_ptr<DBManager>& logs_db)
    : session(session), auth(auth),logs_db(logs_db){
       auth_requests=std::make_shared<Auth>(session,auth);
       logs_requests=std::make_shared<Logs>(logs_db);
    };

