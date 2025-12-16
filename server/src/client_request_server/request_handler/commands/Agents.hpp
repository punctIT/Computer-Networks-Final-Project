#pragma once
#include <expected>
#include <string>
#include <memory>
#include "../ResponseFormater.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../session_manager/SessionManager.hpp"
#include "../../../utils/DBManager.hpp"
#include <iostream>

class Agents:public ResponseFormater{
    std::shared_ptr<DBManager>& agents;
    public:
    Agents(std::shared_ptr<DBManager> &agents);
    std::expected<std::string, std::string> update_dashboard(JUNK &request);
};