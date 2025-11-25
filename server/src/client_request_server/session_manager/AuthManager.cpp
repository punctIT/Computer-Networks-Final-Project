#include "AuthManager.hpp"
#include "../../utils/DBManager.hpp"
#include <iostream>
#include <format>
AuthManager::AuthManager()
{
    credentials_db = std::make_shared<DBManager>();
    try{
        credentials_db->set_path("pass.db")
                        .create()
                        .open();
        const std::string cmd = R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL UNIQUE,
                password TEXT NOT NULL
            );
        )";
        auto status = credentials_db->run_command(cmd);
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
    const std::string sql =
        std::format("select count(*) from users where password='{}' and username = '{}';",
            password,
            username
    );
    auto value = credentials_db->get(sql);
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
    return credentials_db->run_command(std::format("INSERT INTO users (username, password) VALUES ('{}', '{}');",username,password));
}
