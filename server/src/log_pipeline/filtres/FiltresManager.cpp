#include "FiltresManager.hpp"
#include <iostream>
#include <format>

void FiltresManager::configure_database(){
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS filtres (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            filter_type TEXT,
            keyword TEXT
        );
    )";
    auto status =db->run_command_unsafe(sql);
    if(status.has_value()==false){
        throw std::runtime_error(std::format("[ERR]Filtres Manager:{}",status.error()));
    }
}


FiltresManager::FiltresManager(std::shared_ptr<DBManager> alerts_db)
{
    this->db = alerts_db;
    configure_database();
    std::cout << "Filtres Manager succesful connfigured"<<std::endl;
}


