#pragma once 
#include <memory>
#include "../../utils/ThreadSafeQueue.hpp"
#include <iostream>
#include "DataParser.hpp"
#include <format>
#include "../../utils/DBManager.hpp"
#include "../../log_pipeline/source_managers/SourceManager.hpp"
#include "../alerts_manager/AlertsManager.hpp"
class DataProcessor{
    std::shared_ptr<ThreadSafeQueue<LogEvent>> logEvents_queue;
    std::shared_ptr<DBManager> logs_db;
    std::shared_ptr<DBManager> agents_db;
    std::shared_ptr<AlertsManager> alerts_manager;
    void write_log(std::vector<std::string>& log,std::string source);
    std::shared_ptr<SourceManager> source_manager;
    public:
    DataProcessor(std::shared_ptr<SourceManager> source_manager,std::shared_ptr<AlertsManager> alerts);
    DataProcessor& set_logs_database(  std::shared_ptr<DBManager> logs_db);
    DataProcessor& set_agents_database(  std::shared_ptr<DBManager> agents_db);
    DataProcessor& set_syslog_queue(std::shared_ptr<ThreadSafeQueue<LogEvent>> logEvents_queue);
    void analyze_syslog(int id);
};