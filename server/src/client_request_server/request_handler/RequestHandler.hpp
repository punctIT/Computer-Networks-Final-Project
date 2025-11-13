#pragma once 

#include <string>
#include <memory>
#include <expected>

class SessionManager;
class JUNK;
class AuthManager;
class RequestHandler{
    std::shared_ptr<SessionManager>& session;
    std::shared_ptr<AuthManager>& auth;
    public:
    RequestHandler(std::shared_ptr<SessionManager> &session,std::shared_ptr<AuthManager> &auth);
    std::expected<std::string,std::string> match_type(JUNK &request);
    std::expected<std::string,std::string> match_request(int client,std::string request);
    static std::string response_formater(bool succes ,std::string type, std::string content);
};