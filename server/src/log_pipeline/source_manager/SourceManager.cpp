#include "SourceManager.hpp"


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
        throw std::runtime_error(std::format("SOURCE DATABASE[ERR]:{}",data.error()));
    }
    cmd = R"(
            CREATE TABLE IF NOT EXISTS blacklist(
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                ip TEXT NOT NULL UNIQUE,
                admin_username TEXT NOT NULL,
                added_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )";
    data = sources_db->run_command_unsafe(cmd);
    if(!data){
        throw std::runtime_error(std::format("SOURCE DATABASE[ERR]:{}",data.error()));
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
    auto data = sources_db->get_unsafe("select * from whitelist;");
    if(!data.has_value()){
        throw std::runtime_error(data.error());
    }
    for(auto values : data.value()){
        auto content=BetterString::split(values,"[]");
        if(content.size()<5){
            continue;
        }
        whitelist_source[content[1]]=content[2];
    }
    std::cout<<"[WHITELIST SIZE]:"<<whitelist_source.size()<<std::endl;
    data = sources_db->get_unsafe("select * from blacklist;");
    if(!data.has_value()){
        throw std::runtime_error(data.error());
    }
    for(auto values : data.value()){
        auto content=BetterString::split(values,"[]");
        if(content.size()<4){
            continue;
        }
        blacklist_source.insert(content[1]);
    }
    std::cout<<"[BLACKLIST SIZE]:"<<blacklist_source.size()<<std::endl;
    
}

std::expected<void, std::string> SourceManager::add_whitelist(std::string ip, std::string source_name, std::string admin_username)
{  
    std::unique_lock lock(_mutex);
    if(whitelist_source.contains(ip)){
        return std::unexpected("ip alerady in  whitelist");
    }
    if(blacklist_source.contains(ip)){
        return std::unexpected("invalid , ip in blacklist");
    }
    auto result = sources_db->query("INSERT INTO whitelist (ip, hostname, admin_username) VALUES (?, ?, ?)",{ip,source_name,admin_username});
    if(!result){
        return std::unexpected(result.error());
    }
    whitelist_source[ip]=source_name;
    return {};
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

std::expected<void, std::string> SourceManager::add_blacklist(std::string ip, std::string admin_username)
{
    std::unique_lock lock(_mutex);
    if(blacklist_source.contains(ip)){
        return std::unexpected("ip alerady in  blacklist");
    }
    if(whitelist_source.contains(ip)){
        return std::unexpected("invalid , ip in whitelist");
    }
    auto result = sources_db->query("INSERT INTO blacklist (ip, admin_username) VALUES (?, ?)",{ip,admin_username});
    if(!result){
        return std::unexpected(result.error());
    }
    blacklist_source.insert(ip);
    return {};
}

bool SourceManager::check_ip_whitelist(std::string ip)
{
    std::shared_lock lock(_mutex);
    return whitelist_source.contains(ip);
}

bool SourceManager::check_ip_blacklist(std::string ip)
{
    std::shared_lock lock(_mutex);
    return blacklist_source.contains(ip);
}
