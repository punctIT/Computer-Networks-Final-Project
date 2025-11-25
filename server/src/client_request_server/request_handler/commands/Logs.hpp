#pragma once
#include <expected>
#include <string>
#include <memory>
#include "../ResponseFormater.hpp"

class JUNK;
class DBManager;

class Logs:public ResponseFormater{
    std::shared_ptr<DBManager>& logs;
    public:
    Logs(std::shared_ptr<DBManager> &Logs);
    std::expected<std::string, std::string> logs_request(JUNK &request);
};