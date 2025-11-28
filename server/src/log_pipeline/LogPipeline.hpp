#pragma once 
#include "../utils/ThreadSafeQueue.hpp"
#include <memory>
#include <string>
#include <utility>
class DBManager;
class SyslogReceiver;
class LogProcessor;
class SourceManager;
class LogPipeline{
    std::shared_ptr<ThreadSafeQueue<std::pair<std::string,std::string>>> syslog_queue;
    std::shared_ptr<DBManager> logs_db;
    std::shared_ptr<SyslogReceiver> syslog_receiver;
    std::shared_ptr<LogProcessor> log_processor;
    std::shared_ptr<SourceManager> source_manager;
    public:
    LogPipeline(std::shared_ptr<DBManager> db,std::shared_ptr<DBManager> source_db);
    LogPipeline& configure_database();
    LogPipeline& start_syslog_receiver();
    LogPipeline& start_process_syslogs();
};