#pragma once 
#include <memory>
#include "../../utils/ThreadSafeQueue.hpp"
#include <iostream>
#include "LogParser.hpp"
#include <format>
#include "../../utils/DBManager.hpp"
#include "../../log_pipeline/data_managers/SourceManager.hpp"

class LogProcessor{
    std::shared_ptr<ThreadSafeQueue<LogEvent>> logEvents_queue;
    std::shared_ptr<DBManager> logs_db;
    void write_log(const std::vector<std::string>& log);
    std::shared_ptr<SourceManager> source_manager;
    public:
    LogProcessor(std::shared_ptr<SourceManager> source_manager);
    LogProcessor& set_database(  std::shared_ptr<DBManager> logs_db);
    LogProcessor& set_syslog_queue(std::shared_ptr<ThreadSafeQueue<LogEvent>> logEvents_queue);
    void analyze_syslog(int id);
};