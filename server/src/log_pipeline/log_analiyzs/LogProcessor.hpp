#pragma once 
#include <memory>
#include "../../utils/ThreadSafeQueue.hpp"


class DBManager;

class LogProcessor{
    std::shared_ptr<ThreadSafeQueue<std::string>> syslog_queue;
    std::shared_ptr<DBManager> logs_db;
    public:
    LogProcessor();
    LogProcessor& set_database(  std::shared_ptr<DBManager> logs_db);
    LogProcessor& set_syslog_queue(std::shared_ptr<ThreadSafeQueue<std::string>> syslog_queue);
    void analyze_syslog();
};