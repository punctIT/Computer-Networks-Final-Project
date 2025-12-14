#pragma once 
#include <memory>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <shared_mutex>
#include <string>
#include <expected>
#include <iostream>
#include <format>
#include <optional>
#include "../../utils/DBManager.hpp"
#include "../../utils/BetterString.hpp"

class SourceManager{
    std::shared_mutex _mutex; 
    std::unordered_map<std::string,std::string> whitelist_source;
    std::unordered_set<std::string> blacklist_source;
    std::shared_ptr<DBManager> sources_db;
    void create_database();
    public:
    SourceManager(std::shared_ptr<DBManager> sources_db);
    std::expected<void,std::string> add_whitelist(std::string ip,std::string source_name, std::string admin_username);
    std::expected<void,std::string> remove_whitelist(std::string ip);
    std::expected<std::vector<std::string>,std::string> get_whitelist();
    std::expected<void,std::string> add_blacklist(std::string ip, std::string admin_username);
    std::expected<void,std::string> remove_blacklist(std::string ip);
    std::expected<std::vector<std::string>,std::string> get_blacklist();

    std::optional<std::string> check_ip_whitelist(std::string ip);
    bool check_ip_blacklist(std::string ip);
};