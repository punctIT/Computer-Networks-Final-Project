#include "Logs.hpp"
#include "../../../utils/BetterString.hpp"
#include <format>
Logs::Logs( std::shared_ptr<DBManager> &logs): logs(logs) {}
std::expected<std::string, std::string> Logs::logs_request(JUNK &request)
{
    if(!request.contains("last_id")){
        return std::unexpected("Invalid , there is no LAST_ID ");
    }
    auto data = logs->query("SELECT * FROM (SELECT * FROM logs WHERE id >= ? ORDER BY id DESC LIMIT 40) AS subquery ORDER BY id;",{request["last_id"].value()});
    if(!data.has_value()){
        return std::unexpected(data.error());
    }
    std::string result="";
    for(auto log : data.value()){
        result=std::format("{}{{}}{}",result,log);
    }
    return response_formater(true,"logs",result);
}



/*
 CREATE TABLE IF NOT EXISTS logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            pri TEXT,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
            host TEXT,
            source TEXT,
            message TEXT,
            ip_name TEXT,
*/
std::expected<std::string, std::string> Logs::update_syslog_dashboard(JUNK &request)
{
    std::string cmd = R"(
        SELECT 
            SUM(CASE WHEN pri IN ('Error', 'Critical', 'Alert', 'Emergency') THEN 1 ELSE 0 END),
            SUM(CASE WHEN pri = 'Warning' THEN 1 ELSE 0 END),
            SUM(CASE WHEN pri IN ('Notice', 'Informational', 'Debug') THEN 1 ELSE 0 END)
        FROM logs;
    )";
    auto data = logs->get_unsafe(cmd);
    if(!data.has_value()){
        return std::unexpected(data.error());
    }
    auto values = BetterString::split(data.value()[0],"[]");
    // for(auto val :values){
    //     std::cout<<val<<std::endl;
    // }
    if(!request.contains("last_log")){
        return std::unexpected("Invalid , there is no LAST_ID ");
    }
    auto data_logs = logs->query("SELECT * FROM (SELECT * FROM logs WHERE id >= ? ORDER BY id DESC LIMIT 10) AS subquery ORDER BY id;",{request["last_log"].value()});
    if(!data_logs.has_value()){
        return std::unexpected(data_logs.error());
    }
    std::string result="";
    for(auto log : data_logs.value()){
        result=std::format("{}**{}",result,log);
    }
    auto last_log = logs->get_unsafe("select max(id) from logs;");
    if (last_log.has_value()==false){
        return std::unexpected(last_log.error());
    }
    std::string response = std::format("high:{{{}}};medium:{{{}}};low:{{{}}};logs:{{{}}};last_log:{{{}}};",values[0],values[1],values[2],result,last_log.value()[0]);


    return response_formater(true,"update_syslog_dashboard",response);
}

std::expected<std::string, std::string> Logs::update_unknown_syslog_dashboard(JUNK &request)
{
    auto data_logs = logs->get_unsafe("select * from unknown_log limit 100;");
    if(!data_logs.has_value()){
        return std::unexpected(data_logs.error());
    }
    std::string result="";
    for(auto log : data_logs.value()){
        result=std::format("{}{{}}{}",result,log);
    }
    auto sources_logs = logs->get_unsafe("select distinct(ip) from unknown_log ;");
    if(!sources_logs.has_value()){
        return std::unexpected(sources_logs.error());
    }
    std::string sources="";
    for(auto log : sources_logs.value()){
        sources=std::format("{}{{}}{}",sources,log);
    }
    return std::format("type:{{{}}};succes:{{{}}};logs:{{{}}};sources:{{{}}};","update_unknown_syslog",true,result,sources);
}
