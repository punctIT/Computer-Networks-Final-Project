#include "Logs.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../session_manager/SessionManager.hpp"
#include "../../../utils/DBManager.hpp"
#include <iostream>
Logs::Logs( std::shared_ptr<DBManager> &logs): logs(logs) {}
std::expected<std::string, std::string> Logs::logs_request(JUNK &request)
{
    std::string cmd = "select * from alerts;";
    auto data = logs->get(cmd);
    if(!data.has_value()){
        return std::unexpected(data.error());
    }
    return response_formater(true,"logs","salut");
}