#include "Filtres.hpp"
#include <iostream> 
Filtres::Filtres(std::shared_ptr<FiltresManager>& manager)
    : filtres_manager(manager){};

std::expected<std::string, std::string> Filtres::get_filtres()
{
    return std::format("type:{{update_filtres}};sucess:{{true}};{}",filtres_manager->get_data());
}

std::expected<std::string, std::string> Filtres::add_filtres(JUNK &request)
{
    std::string ok_msg = response_formater(true,"add_filtres","nimic");
    if(request.contains("type_f")==false){
        return std::unexpected("MISSING type_f");
    }
    if(request.contains("keyword")==false){
        return std::unexpected("MISSING keyword");
    }
    std::expected<void,std::string> result={};
    if(request["type_f"].value()=="type"){
        result = filtres_manager->add_type_keyword(request["keyword"].value());
        return ok_msg;
    }
    if(request["type_f"].value()=="message"){
       result = filtres_manager->add_msg_keyword(request["keyword"].value());
        return ok_msg;
    }
    if(request["type_f"].value()=="alert"){
        result = filtres_manager->add_alert_custom_keyword(request["keyword"].value());
         return ok_msg;
    }
    if (result.has_value()==false){
        return std::unexpected(result.error());
    }
    return std::unexpected("unknown type filtres");
}

std::expected<std::string, std::string> Filtres::remove_filtres(JUNK &request)
{
     std::string ok_msg = response_formater(true,"remove_filtres","nimic");
    if(request.contains("type_f")==false){
        return std::unexpected("MISSING type_f");
    }
    if(request.contains("keyword")==false){
        return std::unexpected("MISSING keyword");
    }
    std::expected<void,std::string> result={};
    if(request["type_f"].value()=="type"){
        result = filtres_manager->remove_type_keyword(request["keyword"].value());
        return ok_msg;
    }
    if(request["type_f"].value()=="message"){
       result = filtres_manager->remove_msg_keyword(request["keyword"].value());
        return ok_msg;
    }
    if(request["type_f"].value()=="alert"){
        result = filtres_manager->remove_alert_custom_keyword(request["keyword"].value());
         return ok_msg;
    }
    if (result.has_value()==false){
        return std::unexpected(result.error());
    }
    return std::unexpected("unknown type filtres");
}
