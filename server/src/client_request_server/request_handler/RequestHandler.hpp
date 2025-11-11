#pragma once 

#include <string>
#include <memory>

class SessionManager;

class RequestHandler{
    public:
    static std::string match_request(int client,std::string request,const std::shared_ptr<SessionManager>& session);
};