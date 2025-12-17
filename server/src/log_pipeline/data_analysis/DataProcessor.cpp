#include "DataProcessor.hpp"

#include <expected>
#include <iostream>
#include <optional>
#define loop while(true)

void DataProcessor::write_log(std::vector<std::string>& log,std::string source)
{
    if(log.size()!=5){
        return;
    }
    std::expected<std::vector<std::string>, std::string> result;
    auto source_name = this->source_manager->check_ip_whitelist(source);
    if(source_name.has_value()){
        log.push_back(source_name.value());
        result = logs_db->query("INSERT INTO logs (pri, timestamp, host, source, message,ip_name) VALUES (?, ?, ?, ?, ? ,?);",log);
    }
    else {
        log.push_back(source);
        result = logs_db->query("INSERT INTO unknown_log (pri, timestamp, host, source, message,ip) VALUES (?, ?,?, ?, ?, ? );",log);
    }
    if (log[4].contains("ceva")){
        alerts_manager->add();
    }

    if(!result.has_value()){
        std::cerr<<"[ERR]"<<result.error()<<std::endl;
    }
}

void DataProcessor::write_agent(std::vector<std::string> &agent_metrics,std::string source)
{
    std::expected<std::vector<std::string>, std::string> status;
    auto source_name = this->source_manager->check_ip_whitelist(source);
    if(source_name.has_value()){
        const char* sql =
            "INSERT INTO metrics (hostname, cpu_load, ram_usage, disk_usage, message) "
            "VALUES (?, ?, ?, ?, ?);";
        status = this->agents_db->query(sql,agent_metrics);
    }
    else {
         agent_metrics.push_back(source);
         const char* sql =
            "INSERT INTO unknown_metrics (hostname, cpu_load, ram_usage, disk_usage, message,ip) "
            "VALUES (?, ?, ?, ?, ?, ?);";
        status = this->agents_db->query(sql,agent_metrics);
    }
    if(status.has_value()==false){
        std::cerr<<status.error()<<std::endl;
    }
}

DataProcessor::DataProcessor(std::shared_ptr<SourceManager> source_manager,std::shared_ptr<AlertsManager> alerts, std::shared_ptr<FiltresManager> filtres_manager)
{
    this->source_manager= source_manager;
    this->alerts_manager=alerts;
    this->filtres_manager= filtres_manager;
}

DataProcessor &DataProcessor::set_logs_database(std::shared_ptr<DBManager> logs_db)
{
    this->logs_db=logs_db;
    return *this;
}


DataProcessor & DataProcessor::set_agents_database(std::shared_ptr<DBManager> agents_db)
{
    this->agents_db=agents_db;
    return *this;
}

DataProcessor &DataProcessor::set_syslog_queue(std::shared_ptr<ThreadSafeQueue<LogEvent>> logEvents_queue)
{
    this->logEvents_queue=logEvents_queue;
    return *this;

}

void DataProcessor::analyze_syslog(int id){
    loop{
        auto data = logEvents_queue->pop();
        if(!data.has_value()){
            continue;
        }
        if(data.value().type==EventType::SYSLOG){
            auto log = DataParser::split_syslog(data.value().payload);
            if (!log.has_value()){
                continue;
            }   
            write_log(log.value(),data.value().source_ip);
            continue;
        }
        if(data.value().type= EventType::AGENT_METRIC){
            auto agent_metric = DataParser::get_agent_data(data.value().payload);
            if(agent_metric.has_value()==false){
                std::cout<<agent_metric.error()<<std::endl;
                continue;
            }
            write_agent(agent_metric.value(),data.value().source_ip);
            continue;
        } 
    }

}
