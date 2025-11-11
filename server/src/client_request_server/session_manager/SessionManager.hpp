#pragma once 
#include <mutex>
#include <shared_mutex>
#include <string>
#include <vector>

class SessionManager{
    std::shared_mutex mutex;
    std::vector<std::string> sessions;  
    public:
        bool check_token(const std::string token);
        std::string create_session();
        SessionManager();
};