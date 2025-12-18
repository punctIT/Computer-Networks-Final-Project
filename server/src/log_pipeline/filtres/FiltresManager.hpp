#pragma once 
#include <memory>
#include "../../utils/DBManager.hpp"
#include <expected>
#include <string>

#include <set>

class FiltresManager{
    std::shared_ptr<DBManager> db;
    std::set<std::string> custom_alerts;
    std::set<std::string> types_keywords;
    std::set<std::string> msg_keywords;
    void configure_database();
    public:
    FiltresManager(std::shared_ptr<DBManager> db);
    std::expected<void,std::string> add();
    std::expected<void,std::string> add_alert_custom_keyword(std::string keyword);
    std::expected<void,std::string> add_msg_keyword(std::string keyword);
    std::expected<void,std::string> add_type_keyword(std::string keyword);
    std::expected<void,std::string> get_update();
    std::expected<void,std::string> remove();
    std::expected<bool,std::string> check();
};