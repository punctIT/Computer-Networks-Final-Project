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
    std::string sql = "select id,keyword from filtres where filter_type='alert';";
    sql = "select id,keyword from filtres where filter_type='type';";
    sql = "select id,keyword from filtres where filter_type='msg';";
    std::cout << "Filtres Manager succesful connfigured"<<std::endl;
}

std::expected<void, std::string> FiltresManager::add_alert_custom_keyword(std::string keyword)
{
    return std::expected<void, std::string>();
}

std::expected<void, std::string> FiltresManager::add_msg_keyword(std::string keyword)
{
    return std::expected<void, std::string>();
}

std::expected<void, std::string> FiltresManager::add_type_keyword(std::string keyword)
{
    return std::expected<void, std::string>();
}

std::expected<void, std::string> FiltresManager::get_update()
{
    return std::expected<void, std::string>();
}
