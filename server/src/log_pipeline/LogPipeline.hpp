#pragma once 
#include "../utils/ThreadSafeQueue.hpp"
#include <memory>
#include <string>
#include <utility>
#include "syslog_server/SyslogReceiver.hpp"
#include "agents_server/AgentsReceiver.hpp"
#include "log_analiyzs/LogProcessor.hpp"
#include "../utils/DBManager.hpp"
#include <thread>

class LogPipeline{
    std::shared_ptr<ThreadSafeQueue<LogEvent>> logEvents_queue;
    std::shared_ptr<DBManager> logs_db;
    std::shared_ptr<DBManager> agents_db;
    std::shared_ptr<SyslogReceiver> syslog_receiver;
    std::shared_ptr<AgentsReceiver> agent_receiver;
    std::shared_ptr<LogProcessor> log_processor;
    public:
    LogPipeline(std::shared_ptr<DBManager> db,std::shared_ptr<DBManager> db_agents,std::shared_ptr<SourceManager> source);
    LogPipeline& configure_database();
    LogPipeline& start_syslog_receiver();
    LogPipeline& start_agent_receiver();
    LogPipeline& start_process_logEvents();
};