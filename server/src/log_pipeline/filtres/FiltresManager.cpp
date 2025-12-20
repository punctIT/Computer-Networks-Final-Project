#include "FiltresManager.hpp"
#include <iostream>
#include <format>
#include "../../utils/BetterString.hpp"

void FiltresManager::configure_database() {
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS filtres (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            filter_type TEXT,
            keyword TEXT
        );
    )";
    auto status = db->run_command_unsafe(sql);
    if (!status.has_value()) {
        throw std::runtime_error(std::format("[ERR]Filtres Manager:{}", status.error()));
    }
    if (get_update().has_value()==false){
         throw std::runtime_error(std::format("[ERR]Filtres Manager:{}", "LOAD FILTRES"));
    }
}

FiltresManager::FiltresManager(std::shared_ptr<DBManager> alerts_db) {
    this->db = alerts_db;
    configure_database();
    std::cout << "Filtres Manager succesful connfigured" << std::endl;
}

std::expected<void, std::string> FiltresManager::add_alert_custom_keyword(std::string keyword) {
    std::unique_lock lock(_mutex);
    std::string sql = std::format("INSERT INTO filtres (filter_type, keyword) VALUES ('alert', '{}');", keyword);
    auto status = db->run_command_unsafe(sql);
    if (!status.has_value()) 
        return std::unexpected(status.error());
    return get_update();
}

std::expected<void, std::string> FiltresManager::add_msg_keyword(std::string keyword) {
    std::unique_lock lock(_mutex);
    std::string sql = std::format("INSERT INTO filtres (filter_type, keyword) VALUES ('msg', '{}');", keyword);
    auto status = db->run_command_unsafe(sql);
    if (!status.has_value())
        return std::unexpected(status.error());
    return get_update();
}

std::expected<void, std::string> FiltresManager::add_type_keyword(std::string keyword) {
    std::unique_lock lock(_mutex);
    std::string sql = std::format("INSERT INTO filtres (filter_type, keyword) VALUES ('type', '{}');", keyword);
    auto status = db->run_command_unsafe(sql);
    if (!status.has_value()) 
        return std::unexpected(status.error());
    return get_update();
}

std::expected<void, std::string> FiltresManager::get_update() {
    std::string sql = "SELECT filter_type, keyword FROM filtres;";
    auto results = db->get_unsafe(sql);

    if (!results.has_value()) {
        return std::unexpected(results.error());
    }

    custom_alerts.clear();
    msg_keywords.clear();
    types_keywords.clear();

    for (const auto& row : results.value()) {
        auto data = BetterString::split(row,"[]");
        auto type =data[0];
        auto word = data[1];
        //std::cout<<type<<" "<<word<<" ";
        if (type == "alert") custom_alerts.insert(word);
        else if (type == "msg") msg_keywords.insert(word);
        else if (type == "type") types_keywords.insert(word);
    }

    return {};
}

std::string FiltresManager::get_data()
{
    std::shared_lock lock(_mutex);
    std::string type="";
    for (auto data : types_keywords){
        type=std::format("{}:;:""{}",type,data);
    }
    std::string msg="";
    for (auto data : msg_keywords){
        msg=std::format("{}:;:{}",msg,data);
    }
    std::string alerts="";
    for (auto data :custom_alerts){
        alerts=std::format("{}:;:{}",alerts,data);
    }
    return std::format("alerts:{{{}}};types:{{{}}};msg:{{{}}};",alerts,type,msg);
}

bool FiltresManager::check_type(std::string text){
    std::shared_lock lock(_mutex);
    for(auto type : this->types_keywords){
        if(text.contains(type)){
            return true;
        }
    }
    return false;
}

bool FiltresManager::check_msg(std::string text){
    std::shared_lock lock(_mutex);
     for(auto type : this->msg_keywords){
        if(text.contains(type)){
            return true;
        }
    }
    return false;
}
bool FiltresManager::check_alert(std::string text){
    std::shared_lock lock(_mutex);
     for(auto type : this->custom_alerts){
        if(text.contains(type)){
            return true;
        }
    }
    return false;
}

std::expected<void, std::string> FiltresManager::remove_alert_custom_keyword(std::string keyword) {
    std::unique_lock lock(_mutex);
    std::string sql = std::format("DELETE FROM filtres WHERE filter_type = 'alert' AND keyword = '{}';", keyword);
    auto status = db->run_command_unsafe(sql);
    if (!status.has_value())
        return std::unexpected(status.error());
    return get_update();
}

std::expected<void, std::string> FiltresManager::remove_msg_keyword(std::string keyword) {
    std::unique_lock lock(_mutex);
    std::string sql = std::format("DELETE FROM filtres WHERE filter_type = 'msg' AND keyword = '{}';", keyword);
    auto status = db->run_command_unsafe(sql);
    if (!status.has_value())
        return std::unexpected(status.error());
    return get_update();
}

std::expected<void, std::string> FiltresManager::remove_type_keyword(std::string keyword) {
    std::unique_lock lock(_mutex);
    std::string sql = std::format("DELETE FROM filtres WHERE filter_type = 'type' AND keyword = '{}';", keyword);
    auto status = db->run_command_unsafe(sql);
    if (!status.has_value())
        return std::unexpected(status.error());
    return get_update();
}
