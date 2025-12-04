#pragma once
#include <expected>
#include <string>
#include <memory>
#include "../ResponseFormater.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../session_manager/SessionManager.hpp"
#include "../../../utils/DBManager.hpp"
#include <iostream>

class Logs:public ResponseFormater{
    std::shared_ptr<DBManager>& logs;
    public:
    Logs(std::shared_ptr<DBManager> &Logs);
    std::expected<std::string, std::string> logs_request(JUNK &request);
};