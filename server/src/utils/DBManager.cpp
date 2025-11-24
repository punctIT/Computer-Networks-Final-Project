#include "DBManager.hpp"

DBManager::DBManager(){
    db = nullptr;
}

DBManager::~DBManager(){
    std::unique_lock lock(db_RDLOCK);
    if (db){
        sqlite3_close(db);
    }
}

DBManager &DBManager::set_path(const std::string &db_path){
    this->path = db_path;
    return *this;
}

DBManager &DBManager::create(){
    if (!path.has_value()){
        throw std::runtime_error("Database path not set, USE set_path(PATH) method");
    }
    if (!std::filesystem::exists(path.value())){
        std::ofstream file(path.value());
        if (file.is_open()){
            file.close();
        }
        else{
            throw std::runtime_error("Faild to create database");
        }
    }
    return *this;
}

void DBManager::open(){
    if (!path.has_value()){
        throw std::runtime_error("Database path not set, USE set_path(PATH) method");
    }
    std::unique_lock lock(db_RDLOCK);
    if (!std::filesystem::exists(path.value())){
        throw std::runtime_error("Database path is invalid");
    }
    if (db){
        sqlite3_close(db);
        db = nullptr;
    }
    if (!std::filesystem::exists(path.value())){
        throw std::runtime_error("Database path is invalid, use create method to create a new db");
    }
    if (sqlite3_open(path.value().c_str(), &db) != SQLITE_OK){
        throw std::runtime_error("Can't open Database");
    }
    char *errMsg = nullptr;
    sqlite3_exec(db, "PRAGMA journal_mode=WAL;", nullptr, nullptr, &errMsg);
    if (errMsg){
        sqlite3_free(errMsg);
    }
    sqlite3_busy_timeout(db, 5000);
}

int DBManager::callback(void *data, int argc, char **argv, char **colName){
    auto *results = reinterpret_cast<std::vector<std::string> *>(data);
    std::string row;
    for (int i = 0; i < argc; i++){
        row += (argv[i] ? argv[i] : "NULL");
        if (i < argc - 1)
            row += "[]";
    }
    results->push_back(row);
    return 0;
}

std::expected<std::vector<std::string>, std::string> DBManager::get(const std::string cmd){
    std::shared_lock lock(db_RDLOCK);
    if (!db){
        return std::unexpected("Database not connected");
    }

    std::vector<std::string> rows;
    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, cmd.c_str(), callback, &rows, &errMsg);

    if (rc != SQLITE_OK){
        std::string error = "SQL error: ";
        if (errMsg)
        {
            error += errMsg;
            sqlite3_free(errMsg);
        }
        return std::unexpected(error);
    }

    return rows;
}

std::expected<void, std::string> DBManager::run_command(const std::string cmd){
    std::unique_lock lock(db_RDLOCK);

    if (!db){
        return std::unexpected("Database not connected");
    }

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, cmd.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK){
        std::string error = "SQL error: ";
        if (errMsg){
            error += errMsg;
            sqlite3_free(errMsg);
        }
        return std::unexpected(error);
    }
    return {};
}