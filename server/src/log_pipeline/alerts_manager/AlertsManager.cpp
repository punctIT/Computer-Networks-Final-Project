#include "AlertsManager.hpp"
#include <iostream>


void AlertsManager::configure_database(){
    
}


AlertsManager::AlertsManager(std::shared_ptr<DBManager> alerts_db)
{
    this->alerts_db=alerts_db;
    this->alerts_db->set_path("databases/alerts_db")
                    .create()
                    .open();
    configure_database();
    std::cout << "Alerts Manager succesful connfigured"<<std::endl;
}


