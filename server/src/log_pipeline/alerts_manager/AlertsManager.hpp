#pragma once 
#include <memory>
#include "../../utils/DBManager.hpp"



class AlertsManager{
    std::shared_ptr<DBManager> alerts_db;

    void configure_database();
    public:
    AlertsManager(std::shared_ptr<DBManager> alerts_db);
};