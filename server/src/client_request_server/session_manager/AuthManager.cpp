#include "AuthManager.hpp"

AuthManager::AuthManager()
{
    credentials_db = std::make_shared<DBManager>();
    try{
        credentials_db->set_path("databases/pass.db")
                        .create()
                        .open();
        const std::string cmd = R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL UNIQUE,
                password TEXT NOT NULL
            );
        )";
        auto status = credentials_db->run_command_unsafe(cmd);
        if(!status.has_value()){
            std::cerr<<status.error()<<std::endl;
        }
        else {
            std::cout<<"Password Db open succesful"<<std::endl;
        }
    }catch(std::exception &e ){
        std::cerr<<e.what()<<std::endl;   
    }
}


std::expected<bool, std::string> AuthManager::check_credentials(std::string username, std::string password)
{
    auto value = credentials_db->query("select count(*) from users where password = ? and username = ?",{username,password});
    if(value.has_value()){
        //std::cout<<"DBG:"<< value.value()[0]<<std::endl;
        if(value.value()[0]=="1")
            return true;
        return false;
    }
    else {
        std::cout<<"ERROR:"<<value.error()<<std::endl;
        return false;
    }
    
}

std::expected<void, std::string> AuthManager::_register(std::string username, std::string password)
{ 
   auto data = credentials_db->query("INSERT INTO users (username, password) VALUES (?, ?);",{username,password});\
   if(!data.has_value()){
        return std::unexpected(data.error());
   }
   return {};
}
