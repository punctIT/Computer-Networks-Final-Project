#include "SessionManager.hpp"
#include <iostream>
#include <format>
bool SessionManager::check_token(const std::string token){
    std::shared_lock lock(mutex);
    if(sessions.contains(token)){
        return true;
    }
    return false;
}

std::string SessionManager::create_session(std::string username){
    //std::cout<<"ceva";
    std::unique_lock lock(mutex);
    std::string token =std::format("ceva{}",count);
    sessions[token]=username;
    ++count;
    return token;
}
std::expected<bool, std::string> SessionManager::remove_session(const std::string token){
    std::unique_lock lock(mutex);
    if(sessions.contains(token)){
        return sessions.erase(token);
    }
    return std::unexpected("Error , token not found in manager");
}
void SessionManager::debug(){
    std::shared_lock lock(mutex);
     for(auto i : sessions){
        std::cout<<i.first<<" "<<i.second<<" \n";
    }
}
SessionManager::SessionManager(){
    count=0;
}