#pragma once

#include <expected>
#include <string>
class AuthManager{
    public:
    std::expected<bool,std::string> check_credentials(std::string username,std::string password);
};