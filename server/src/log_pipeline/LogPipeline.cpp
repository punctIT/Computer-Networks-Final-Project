#include "LogPipeline.hpp"
#include "syslog_server/SyslogReceiver.hpp"
#include <thread>
LogPipeline::LogPipeline(std::shared_ptr<DBManager> db)
{
    std::thread t1([this,db](){
        logs_db=db;
        syslog_queue=std::make_shared<ThreadSafeQueue<std::string>>();
        syslog_receiver= std::make_shared<SyslogReceiver>();
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
    
    
}