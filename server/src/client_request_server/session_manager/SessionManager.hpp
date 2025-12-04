#pragma once 
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <expected>
#include <iostream>
#include <format>
class SessionManager{
    std::shared_mutex mutex;
    std::unordered_map<std::string,std::string> sessions;
    int count;
    public:
        SessionManager();
        bool check_token(const std::string token);
        std::string create_session(std::string username);
        std::expected<bool,std::string> remove_session(const std::string token);
        std::expected<bool,std::string> clear();
        void debug();
};