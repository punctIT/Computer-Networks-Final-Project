#include "RequestHandler.hpp"
#include "../session_manager/SessionManager.hpp"

#include <iostream>

std::string RequestHandler::match_request(int client,std::string request,const std::shared_ptr<SessionManager>& session){
    std::cout << "Cerere primită:\n"
              << request << "\n";
    std::string response = "salut din server";
    session->create_session();
    return response;

}