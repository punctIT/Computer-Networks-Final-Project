#include "Logs.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../session_manager/SessionManager.hpp"
#include "../../../utils/DBManager.hpp"
#include <iostream>
Logs::Logs( std::shared_ptr<DBManager> &logs): logs(logs) {}
std::expected<std::string, std::string> Logs::logs_request(JUNK &request)
{
    std::string cmd = "select * from alerts;";
    auto data = logs->get_unsafe(cmd);
    if(!data.has_value()){
        return std::unexpected(data.error());
    }
    std::string result="";
    for(auto log : data.value()){
        result=std::format("{}{{}}{}",result,log);
    }
    return response_formater(true,"logs",result);
}