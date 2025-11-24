#include "LogProcessor.hpp"
#include <iostream>
#include "../../utils/BetterString.hpp"
#include <format>
#include "../../utils/DBManager.hpp"
#define loop while(true)

void LogProcessor::write_log(const std::vector<std::string>& log)
{
    if(log.size()<5){
        return;
    }
    const std::string sql = std::format(R"(
        INSERT INTO alerts (pri, timestamp, host, source, message)
           VALUES ('{}', '{}', '{}', '{}', '{}');
        )",log[0],log[1],log[2],log[3],log[4]);
    auto result= logs_db->run_command(sql);
    if(!result.has_value()){
        std::cerr<<"[ERR]"<<result.error()<<std::endl;
    }
}

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
        if(!data.has_value()){
            continue;
        }
        //std::cout<<"["<<id<<']'<<data.value()<<std::endl;
        auto log = BetterString::split_syslog(data.value());
        if (!log.has_value()){
            continue;
        }   
        write_log(log.value());
         
    }

}
