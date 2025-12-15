#pragma once 
#include <memory>
#include "../../utils/DBManager.hpp"
#include <expected>
#include <string>


class AlertsManager{
    std::shared_ptr<DBManager> alerts_db;

    void configure_database();
    public:
    AlertsManager(std::shared_ptr<DBManager> alerts_db);
    std::expected<void,std::string> add();
};