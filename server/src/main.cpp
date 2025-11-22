#include "client_request_server/ConnectionServer.hpp"
#include "utils/DBManager.hpp"
#include "log_pipeline/LogPipeline.hpp"
#include <iostream>
#include <memory>


int main(){
    std::shared_ptr<DBManager> logs_db = std::make_shared<DBManager>();
    ConnectionServer http_server;
    
    try{
        logs_db->set_path("logs.db")
                        .create()
                        .open();
        LogPipeline logs_pipeline(logs_db);
        logs_pipeline.start_syslog_receiver()
                     .start_process_syslogs();
        http_server.set_port(8080)
                   .bind_data()
                   .set_logs_db(logs_db)
                   .start();
        
       
    }catch(std::exception &e ){
        std::cerr<<e.what()<<std::endl;   
    }

}