#pragma once
#include <memory>
#include <expected>
#include <format>
#include "../ResponseFormater.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../../log_pipeline/filtres/FiltresManager.hpp"

class Filtres:ResponseFormater{
    std::shared_ptr<FiltresManager>& filtres_manager; 
    public:
    Filtres(std::shared_ptr<FiltresManager>& fitres_manager);
    std::string get_filtres();
};