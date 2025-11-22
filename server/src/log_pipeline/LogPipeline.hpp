#pragma once 
#include "../utils/ThreadSafeQueue.hpp"
#include <memory>
#include <string>

class DBManager;
class SyslogReceiver;
class LogPipeline{
    std::shared_ptr<ThreadSafeQueue<std::string>> syslog_queue;
    std::shared_ptr<DBManager> logs_db;
    std::shared_ptr<SyslogReceiver> syslog_receiver;
    public:
    LogPipeline(std::shared_ptr<DBManager> db);

};