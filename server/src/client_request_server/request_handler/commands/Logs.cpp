#include "Logs.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../session_manager/SessionManager.hpp"
#include "../../../utils/DBManager.hpp"
#include <iostream>
Logs::Logs( std::shared_ptr<DBManager> &logs): logs(logs) {}
std::expected<std::string, std::string> Logs::logs_request(JUNK &request)
{
    std::string cmd = "select * from alerts;";
    if(!request.contains("last_id")){
        return std::unexpected("Invalid , there is no LAST_ID ");
    }
    auto data = logs->query("select * from alerts where id >= ?",{request["last_id"].value()});
    if(!data.has_value()){
        return std::unexpected(data.error());
    }
    std::string result="";
    for(auto log : data.value()){
        result=std::format("{}{{}}{}",result,log);
    }
    return response_formater(true,"logs",result);
}