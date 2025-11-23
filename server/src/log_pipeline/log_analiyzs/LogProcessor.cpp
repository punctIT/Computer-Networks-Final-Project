#include "LogProcessor.hpp"
#include <iostream>

#define loop while(true)

LogProcessor::LogProcessor()
{
}

LogProcessor &LogProcessor::set_database(  std::shared_ptr<DBManager> logs_db)
{
    this->logs_db=logs_db;
    return *this;
}

LogProcessor &LogProcessor::set_syslog_queue(std::shared_ptr<ThreadSafeQueue<std::string>> syslog_queue)
{
    this->syslog_queue=syslog_queue;
    return *this;

}

void LogProcessor::analyze_syslog(int id){
    loop{
        auto data = syslog_queue->pop();
        if(data.has_value()){
            std::cout<<"["<<id<<']'<<data.value()<<std::endl;
        }
    }

}
