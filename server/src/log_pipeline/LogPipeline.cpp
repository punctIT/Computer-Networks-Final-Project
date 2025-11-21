#include "LogPipeline.hpp"

LogPipeline::LogPipeline(std::shared_ptr<DBManager> db)
{
    logs_db=db;
    syslog_queue=std::make_shared<ThreadSafeQueue<std::string>>();
}