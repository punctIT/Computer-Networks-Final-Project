#include "LogProcessor.hpp"


#define loop while(true)

void LogProcessor::write_log(const std::vector<std::string>& log)
{
    if(log.size()!=5){
        return;
    }
    auto result= logs_db->query("INSERT INTO alerts (pri, timestamp, host, source, message) VALUES (?, ?, ?, ?, ?);",log);
    if(!result.has_value()){
        std::cerr<<"[ERR]"<<result.error()<<std::endl;
    }
}


LogProcessor::LogProcessor(std::shared_ptr<SourceManager> source_manager)
{
    this->source_manager= source_manager;

}

LogProcessor &LogProcessor::set_database(std::shared_ptr<DBManager> logs_db)
{
    this->logs_db=logs_db;
    return *this;
}

LogProcessor &LogProcessor::set_syslog_queue(std::shared_ptr<ThreadSafeQueue<std::pair<std::string,std::string>>> syslog_queue)
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
        if(source_manager->check_ip_whitelist(data.value().first)){
            std::cout<<"["<<id<<']'<<data.value().first<<" "<<data.value().second<<std::endl;      
        }   
        else {
            std::cout<<"["<<id<<']'<<"UNKNOWN"<<" "<<data.value().second<<std::endl; 
        }  
        auto log = LogParser::split_syslog(data.value().second);
        if (!log.has_value()){
            continue;
        }   
        write_log(log.value());
         
    }

}
