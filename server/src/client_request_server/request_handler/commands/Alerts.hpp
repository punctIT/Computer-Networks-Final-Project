#pragma once
#include <expected>
#include <string>
#include <memory>
#include "../ResponseFormater.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../session_manager/SessionManager.hpp"
#include "../../../utils/DBManager.hpp"
#include <iostream>

class Alerts:public ResponseFormater{
    std::shared_ptr<DBManager>& alerts;
    public:
    Alerts(std::shared_ptr<DBManager> &alerts);
    std::expected<std::string, std::string> last_alert(JUNK &request);
};