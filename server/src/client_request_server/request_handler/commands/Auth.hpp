#pragma once
#include <expected>
#include <string>
#include <memory>
#include "../ResponseFormater.hpp"
class SessionManager;
class JUNK;
class AuthManager;

class Auth:public ResponseFormater{
    std::shared_ptr<SessionManager>& session;
    std::shared_ptr<AuthManager>& auth;
    public:
    Auth(std::shared_ptr<SessionManager> &session,std::shared_ptr<AuthManager> &auth);
    std::expected<std::string, std::string> login_request(JUNK &request);
    std::expected<std::string, std::string> register_request(JUNK &request);
    std::expected<std::string, std::string> logout_request(JUNK &request);
};