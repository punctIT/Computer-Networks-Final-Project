#pragma once

#include <expected>
#include <string>
#include <memory>
#include "../../utils/DBManager.hpp"
#include <iostream>
#include <format>
class DBManager;



class AuthManager{
    std::shared_ptr<DBManager> credentials_db;
    public:
    AuthManager();
    std::expected<bool,std::string> check_credentials(std::string username,std::string password);
    std::expected<void,std::string> _register(std::string username,std::string password);
};