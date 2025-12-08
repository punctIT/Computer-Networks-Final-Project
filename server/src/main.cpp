#include "client_request_server/ConnectionServer.hpp"
#include "utils/DBManager.hpp"
#include "log_pipeline/LogPipeline.hpp"
#include "log_pipeline/data_managers/SourceManager.hpp"

#include <iostream>
#include <memory>
#include <filesystem>

int main(){
    std::shared_ptr<DBManager> logs_db = std::make_shared<DBManager>();
    std::shared_ptr<DBManager> source_db = std::make_shared<DBManager>();
    ConnectionServer clients_request_server;
    std::shared_ptr<SourceManager> source_manager=nullptr;
    try{
        source_manager=std::make_shared<SourceManager>(source_db);
        if (!std::filesystem::exists("databases")){
            std::filesystem::create_directory("databases");
        }
        LogPipeline logs_pipeline(logs_db,source_manager);
        logs_pipeline.configure_database()
                     .start_syslog_receiver()
                     .start_agent_receiver()
                     .start_process_logEvents();
        clients_request_server.set_port(8080)
                                .bind_data()
                                .set_logs_db(logs_db)
                                .set_source_manager(source_manager)
                                .start();
                        
       
    }catch(std::exception &e ){
        std::cerr<<e.what()<<std::endl;   
    }

}