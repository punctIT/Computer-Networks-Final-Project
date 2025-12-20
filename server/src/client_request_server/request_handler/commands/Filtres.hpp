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
    std::expected<std::string, std::string> get_filtres();
    std::expected<std::string, std::string> add_filtres(JUNK &request);
    std::expected<std::string, std::string> remove_filtres(JUNK &request);
};