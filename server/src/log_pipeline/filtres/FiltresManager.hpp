#pragma once 
#include <memory>
#include "../../utils/DBManager.hpp"
#include <expected>
#include <string>


class FiltresManager{
    std::shared_ptr<DBManager> db;

    void configure_database();
    public:
    FiltresManager(std::shared_ptr<DBManager> db);
    std::expected<void,std::string> add();
    std::expected<void,std::string> remove();
    std::expected<bool,std::string> check();
};