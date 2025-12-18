#include "Filtres.hpp"

Filtres::Filtres(std::shared_ptr<FiltresManager> &fitres_manager):filtres_manager(filtres_manager)
{
    
}

std::string Filtres::get_filtres()
{
    return std::string();
}
