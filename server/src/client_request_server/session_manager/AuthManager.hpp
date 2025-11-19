#pragma once

#include <expected>
#include <string>
#include <memory>
class DBManager;



class AuthManager{
    std::shared_ptr<DBManager> credentials_db;
    public:
    AuthManager();
    std::expected<bool,std::string> check_credentials(std::string username,std::string password);
};