#include "LogPipeline.hpp"
#include "syslog_server/SyslogReceiver.hpp"
#include "log_analiyzs/LogProcessor.hpp"

#include <thread>
LogPipeline::LogPipeline(std::shared_ptr<DBManager> db){
    syslog_queue=std::make_shared<ThreadSafeQueue<std::string>>();
    syslog_receiver= std::make_shared<SyslogReceiver>();
    log_processor = std::make_shared<LogProcessor>();
    logs_db=db; 
}

LogPipeline &LogPipeline::start_syslog_receiver()
{
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

LogPipeline &LogPipeline::start_process_syslogs()
{
    std::thread t1([this](){
        log_processor->set_syslog_queue(syslog_queue)
                      .analyze_syslog();
    });
    t1.detach();
    return *this;
}
