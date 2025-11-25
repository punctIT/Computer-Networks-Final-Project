#pragma once 

#include <string>
#include <memory>
#include <expected>
#include "ResponseFormater.hpp"
class SessionManager;
class JUNK;
class AuthManager;
class Auth;

class RequestHandler:public ResponseFormater{
    protected:
    std::shared_ptr<SessionManager>& session;
    std::shared_ptr<AuthManager>& auth;
    std::shared_ptr<Auth> auth_functions;
    public:
    RequestHandler(std::shared_ptr<SessionManager> &session,std::shared_ptr<AuthManager> &auth);
    std::expected<std::string,std::string> match_type(JUNK &request);
    std::expected<std::string,std::string> match_request(int client,std::string request);
    
};