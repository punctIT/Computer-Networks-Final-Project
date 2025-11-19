#pragma once 
#include <sqlite3.h>
#include <string>
#include <vector>
#include <filesystem>
#include <shared_mutex>
#include <expected>
#include <optional>
#include <fstream>
#include <mutex>
#include <string>
class DBManager{
    private:
        sqlite3* db;
        std::optional<std::string> path;
        std::shared_mutex db_RDLOCK;
        
    public:
        DBManager();
        ~DBManager();
        DBManager& set_path(const std::string& db_path);
        DBManager& create();
        void open();
        static int callback(void* data, int argc, char** argv, char** colName) ;
        std::expected<std::vector<std::string>,std::string> get(const std::string cmd) ;
        std::expected<void,std::string> run_command(const std::string cmd);
};