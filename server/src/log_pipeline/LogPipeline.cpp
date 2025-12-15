#include "LogPipeline.hpp"


LogPipeline::LogPipeline(std::shared_ptr<DBManager> db,std::shared_ptr<DBManager> db_agents,std::shared_ptr<SourceManager> source,std::shared_ptr<AlertsManager> alerts,std::shared_ptr<FiltresManager> filtres){
    logEvents_queue=std::make_shared<ThreadSafeQueue<LogEvent>>();
    syslog_receiver= std::make_shared<SyslogReceiver>(source);
    agent_receiver= std::make_shared<AgentsReceiver>(source);
    log_processor = std::make_shared<DataProcessor>(source,alerts,filtres);
    logs_db=db; 
    agents_db=db_agents;
    
}

LogPipeline &LogPipeline::configure_database()
{
    this->logs_db->set_path("databases/logs.db")
                  .create()
                  .open();
    std::cout<<"Logs database has open succesful"<<std::endl;  
    std::string sql = R"(
        CREATE TABLE IF NOT EXISTS logs (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            pri TEXT,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
            host TEXT,
            source TEXT,
            message TEXT,
            ip_name TEXT,

            resolved_by TEXT DEFAULT NULL,
            resolved_at DATETIME DEFAULT NULL,
            resolution_message TEXT DEFAULT NULL
        );
    )";
    auto result = this->logs_db->run_command_unsafe(sql);
    if(!result.has_value())
        throw std::runtime_error(result.error());
    sql = R"(
        CREATE TABLE IF NOT EXISTS unknown_log (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            pri TEXT,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
            host TEXT,
            source TEXT,
            message TEXT
        );
    )";
    result = this->logs_db->run_command_unsafe(sql);
    if(!result.has_value())
        throw std::runtime_error(result.error());
    this->agents_db->set_path("databases/agents.db")
                  .create()
                  .open();
    sql = R"(
        CREATE TABLE IF NOT EXISTS metrics (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        hostname TEXT,               
        cpu_load REAL,
        ram_usage REAL,
        disk_usage REAL,
        message TEXT,                
        timestamp INTEGER DEFAULT (strftime('%s','now'))       
    );
    )";
    result = this->agents_db->run_command_unsafe(sql);
    if(!result.has_value())
        throw std::runtime_error(result.error());
    sql = R"(
        CREATE TABLE IF NOT EXISTS agents (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        hostname TEXT UNIQUE,       
        ip_address TEXT,
        os_info TEXT,
        status TEXT,                
        last_seen INTEGER          
    );
    )";
    result = this->agents_db->run_command_unsafe(sql);
    if(!result.has_value())
        throw std::runtime_error(result.error());
    return *this;
}

LogPipeline &LogPipeline::start_syslog_receiver(){
    std::thread t1([this](){   
        try{
            syslog_receiver->set_port(1514).
                            set_thread_safe_queue(logEvents_queue).
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

LogPipeline &LogPipeline::start_agent_receiver()
{
    std::thread t1([this](){   
        try{
            agent_receiver->set_port(9000).
                            set_thread_safe_queue(logEvents_queue).
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
LogPipeline &LogPipeline::start_process_logEvents(){
    log_processor->set_syslog_queue(logEvents_queue)
                  .set_logs_database(logs_db)
                  .set_agents_database(agents_db);
    for(int i=0;i<4;++i){
        std::thread t1([this,i](){
            log_processor->analyze_syslog(i);
        });
        t1.detach();
    }
    return *this;
}
