#pragma once 
#include <memory>
#include "../../utils/DBManager.hpp"
#include <expected>
#include <string>
#include <mutex>
#include <shared_mutex>

#include <set>

class FiltresManager{
    std::shared_ptr<DBManager> db;
    std::set<std::string> custom_alerts;
    std::set<std::string> types_keywords;
    std::set<std::string> msg_keywords;
    std::shared_mutex _mutex;
    void configure_database();
    public:
    FiltresManager(std::shared_ptr<DBManager> db);
    std::expected<void,std::string> add();
    std::expected<void,std::string> add_alert_custom_keyword(std::string keyword);
    std::expected<void,std::string> add_msg_keyword(std::string keyword);
    std::expected<void,std::string> add_type_keyword(std::string keyword);
    std::expected<void,std::string> remove_alert_custom_keyword(std::string keyword);
    std::expected<void,std::string> remove_msg_keyword(std::string keyword);
    std::expected<void,std::string> remove_type_keyword(std::string keyword);
    std::expected<void,std::string> get_update();
    std::string get_data();
    bool check_type(std::string text);
    bool check_msg(std::string text);
    bool check_alert(std::string text);
};