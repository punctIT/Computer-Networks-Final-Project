#include "SessionManager.hpp"
#include <iostream>
bool SessionManager::check_token(const std::string token)
{
    return false;
}

std::string SessionManager::create_session()
{
    std::unique_lock lock(mutex);
    sessions.push_back("salut");
    for(auto i : sessions){
        std::cout<<i<<" \n";
    }
    return std::string();
}

SessionManager::SessionManager()
{
}