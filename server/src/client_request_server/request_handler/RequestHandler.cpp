#include "RequestHandler.hpp"
#include "../session_manager/SessionManager.hpp"
#include "../../utils/JUNK.hpp"
#include <iostream>

std::string RequestHandler::match_request(int client,std::string request,const std::shared_ptr<SessionManager>& session){
    std::cout << "Cerere primită:\n"
              << request << "\n";
    JUNK data = JUNK::deserialize(request);
    data.display();
    std::string dat2 = JUNK::serialize(data);
    session->create_session();
    return dat2;

}
