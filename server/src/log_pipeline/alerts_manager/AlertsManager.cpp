#include "AlertsManager.hpp"
#include <iostream>
#include <format>

void AlertsManager::configure_database(){
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS alerts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            alert_name TEXT NOT NULL,        
            category TEXT,                  
            severity INTEGER,            
            
            entity TEXT,                     
           
            details TEXT,                    
            status TEXT DEFAULT 'NEW', 
            comment TEXT DEFAULT NULL,         
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )";
    auto status =alerts_db->run_command_unsafe(sql);
    if(status.has_value()==false){
        throw std::runtime_error(std::format("[ERR]Alert Manager:{}",status.error()));
    }
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


