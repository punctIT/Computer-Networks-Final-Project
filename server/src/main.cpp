#include "client_request_server/ConnectionServer.hpp"
#include "utils/DBManager.hpp"
#include "log_pipeline/LogPipeline.hpp"
#include <iostream>
#include <memory>
#include <filesystem>

int main(){
    std::shared_ptr<DBManager> logs_db = std::make_shared<DBManager>();
    std::shared_ptr<DBManager> source_db = std::make_shared<DBManager>();
    ConnectionServer http_server;
    
    try{
        if (!std::filesystem::exists("databases")){
            std::filesystem::create_directory("databases");
        }
        logs_db->set_path("databases/logs.db")
                        .create()
                        .open();
        std::cout<<"Logs database has open succesful"<<std::endl;

        LogPipeline logs_pipeline(logs_db,source_db);
        logs_pipeline.configure_database()
                     .start_syslog_receiver()
                     .start_process_syslogs();
        http_server.set_port(8080)
                   .bind_data()
                   .set_logs_db(logs_db)
                   .start();
        
       
    }catch(std::exception &e ){
        std::cerr<<e.what()<<std::endl;   
    }

}