#include "AuthManager.hpp"

std::expected<bool, std::string> AuthManager::check_credentials(std::string username, std::string password){
    if(username=="1" && password=="1"){
        return true;
    }
    return false;
}