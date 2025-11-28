#include "SourceManager.hpp"
#include <iostream>
#include "../../utils/DBManager.hpp"
void SourceManager::create_database()
{
    std::string cmd = R"(
            CREATE TABLE IF NOT EXISTS whitelist(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                ip TEXT NOT NULL UNIQUE,
                hostname TEXT NOT NULL,
                admin_username TEXT NOT NULL,
                added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )";
    auto data = sources_db->run_command_unsafe(cmd);
    if(!data){
        std::cerr<<"SOURCE DATABASE[ERR]:"<<data.error()<<std::endl;
    }
    cmd = R"(
            CREATE TABLE IF NOT EXISTS blacklist(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                ip TEXT NOT NULL UNIQUE,
                hostname TEXT NOT NULL,
                admin_username TEXT NOT NULL,
                added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )";
    data = sources_db->run_command_unsafe(cmd);
    if(!data){
        std::cerr<<"SOURCE DATABASE[ERR]:"<<data.error()<<std::endl;
    }
    std::cout<<"[INFO]"<<"Source db open/configured succesful"<<std::endl;
}

SourceManager::SourceManager(std::shared_ptr<DBManager> sources_db)
{
    this->sources_db=sources_db;
    this->sources_db->set_path("databases/source_ip")
                      .create()
                      .open();
    create_database();
}

std::expected<void, std::string> SourceManager::add_whitelist(std::string ip, std::string source_name)
{
    std::unique_lock lock(_mutex);
    return std::expected<void, std::string>();
}

std::expected<void, std::string> SourceManager::remove_whitelist(std::string ip)
{
    std::unique_lock lock(_mutex);
    return std::expected<void, std::string>();
}

std::expected<std::string, std::string> SourceManager::get_whitelist(std::string ip)
{
    std::shared_lock lock(_mutex);
    return std::expected<std::string, std::string>();
}

bool SourceManager::check_ip_whitelist(std::string ip)
{
    std::shared_lock lock(_mutex);
    return false;
}
