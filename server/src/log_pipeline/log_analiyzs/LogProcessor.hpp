#pragma once 
#include <memory>
#include "../../utils/ThreadSafeQueue.hpp"

class DBManager;
class SourceManager;

class LogProcessor{
    std::shared_ptr<ThreadSafeQueue<std::pair<std::string,std::string>>> syslog_queue;
    std::shared_ptr<DBManager> logs_db;
    void write_log(const std::vector<std::string>& log);
    std::shared_ptr<SourceManager> source_manager;
    public:
    LogProcessor(std::shared_ptr<SourceManager> source_manager);
    LogProcessor& set_database(  std::shared_ptr<DBManager> logs_db);
    LogProcessor& set_syslog_queue(std::shared_ptr<ThreadSafeQueue<std::pair<std::string,std::string>>> syslog_queue);
    void analyze_syslog(int id);
};