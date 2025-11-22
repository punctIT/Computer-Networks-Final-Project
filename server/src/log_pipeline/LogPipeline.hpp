#pragma once 
#include "../utils/ThreadSafeQueue.hpp"
#include <memory>
#include <string>

class DBManager;
class SyslogReceiver;
class LogProcessor;

class LogPipeline{
    std::shared_ptr<ThreadSafeQueue<std::string>> syslog_queue;
    std::shared_ptr<DBManager> logs_db;
    std::shared_ptr<SyslogReceiver> syslog_receiver;
    std::shared_ptr<LogProcessor> log_processor;
    public:
    LogPipeline(std::shared_ptr<DBManager> db);
    LogPipeline& start_syslog_receiver();
    LogPipeline& start_process_syslogs();
};