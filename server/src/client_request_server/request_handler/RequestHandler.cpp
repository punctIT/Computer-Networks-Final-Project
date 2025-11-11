#include "RequestHandler.hpp"
#include "../session_manager/SessionManager.hpp"
#include "../../utils/JUNK.hpp"
#include <iostream>

std::string RequestHandler::match_request(int client,std::string request,const std::shared_ptr<SessionManager>& session){
    std::cout << "Cerere primită:\n"
              << request << "\n";
    std::string response = "salut din server";
    JUNK data = JUNK::deserialize("ana:{are:{mere};};ana2:{are:{mere};};");
    data.display();
    std::string dat2 = JUNK::serialize(data);
    std::cout<<dat2<<" \n";
    std::cout<<data["ana"].value();
    session->create_session();
    return response;

}
