#include "LogPipeline.hpp"
#include "syslog_server/SyslogReceiver.hpp"
#include "log_analiyzs/LogProcessor.hpp"
#include "../utils/DBManager.hpp"
#include <thread>
LogPipeline::LogPipeline(std::shared_ptr<DBManager> db){
    syslog_queue=std::make_shared<ThreadSafeQueue<std::string>>();
    syslog_receiver= std::make_shared<SyslogReceiver>();
    log_processor = std::make_shared<LogProcessor>();
    logs_db=db; 
}

LogPipeline &LogPipeline::configure_database()
{
    // id ,pri , timestamp(NOW) , host , source , message , username_resolved NULL ,solved ,  rezolved time , by , message  
    const std::string create_alerts = R"(
        CREATE TABLE IF NOT EXISTS alerts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            pri TEXT,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
            host TEXT,
            source TEXT,
            message TEXT
        );
    )";
    auto result = this->logs_db->run_command(create_alerts);
    if(!result.has_value())
        throw std::runtime_error(result.error());
    const std::string create_resolved_alers=R"(
        CREATE TABLE IF NOT EXISTS alerts_resolution (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            alert_id INTEGER NOT NULL,
            resolved_by TEXT,
            resolved_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            resolution_message TEXT,
            FOREIGN KEY (alert_id) REFERENCES alerts(id)
        );
    )";
    result = this->logs_db->run_command(create_resolved_alers);
    if(!result.has_value())
        throw std::runtime_error(result.error());
    return *this;
}

LogPipeline &LogPipeline::start_syslog_receiver(){
    std::thread t1([this](){   
        try{
            syslog_receiver->set_port(1514).
                            set_thread_safe_queue(syslog_queue).
                            configure_server().
                            start();
        }
        catch(std::exception &e){
            std::cerr<<e.what()<<std::endl;
            exit(1);
        }
    });
    t1.detach();
    return *this;
}

LogPipeline &LogPipeline::start_process_syslogs(){
    log_processor->set_syslog_queue(syslog_queue)
                  .set_database(logs_db);
    for(int i=0;i<4;++i){
        std::thread t1([this,i](){
            log_processor->analyze_syslog(i);
        });
        t1.detach();
    }
    return *this;
}
