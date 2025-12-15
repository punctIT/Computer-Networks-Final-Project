#include "Alerts.hpp"

Alerts::Alerts(std::shared_ptr<DBManager> &alerts):alerts(alerts)
{
    this->last_id=-1;
}

std::expected<std::string, std::string> Alerts::last_alert(JUNK &request)
{
    if(!request.contains("last_id")){
        return std::unexpected("Invalid , there is no LAST_ID ");
    }
    auto data = this->alerts->get_unsafe("select max(id) from alerts;");
    if(data.has_value()==false ){
        return std::unexpected(data.error());
    }
    if(data.value().empty()||data.value()[0]=="NULL"||data.value()[0]==request["last_id"].value()){
        return response_formater(false,"update_alerts","NIMIC");
    }
    return std::format("succes:{{{}}};type:{{{}}};content:{{{}}};last_id:{{{}}};",true,"update_alerts","",last_id);
}

std::expected<std::string, std::string> Alerts::update_alerts_dashboard(JUNK &request){
    return response_formater(false,"alerts_dashboard","nimic");
}