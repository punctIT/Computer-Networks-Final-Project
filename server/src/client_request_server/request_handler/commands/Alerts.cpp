#include "Alerts.hpp"

Alerts::Alerts(std::shared_ptr<DBManager> &alerts):alerts(alerts){
    this->last_id=-1;
}

std::expected<std::string, std::string> Alerts::last_alert(JUNK &request)
{
    if(!request.contains("last_id")){
        return std::unexpected("Invalid , there is no LAST_ID ");
    }
    auto data = this->alerts->get_unsafe("select max(id) from alerts WHERE comment IS NULL OR comment = '';");
    if(data.has_value()==false ){
        return std::unexpected(data.error());
    }
    //std::cout<<data.value()[0]<<" "<<request["last_id"].value()<<std::endl;
    if(data.value().empty()||data.value()[0]=="NULL"||data.value()[0]<request["last_id"].value()){
        return response_formater(false,"update_alerts","NIMIC");
    }
    auto data_log = this->alerts->get_unsafe(std::format("select * from alerts where id = {};",data.value()[0]));
    if(data_log.has_value()==false){
        return std::unexpected(data_log.error());
    }
    if(data_log.value().empty()){
        return response_formater(false,"update_alerts","NIMIC");
    }
    return std::format("succes:{{{}}};type:{{{}}};content:{{{}}};last_id:{{{}}};",true,"update_alerts",data_log.value()[0],data.value()[0]);
}

std::expected<std::string, std::string> Alerts::update_alerts_dashboard(JUNK &request){
    auto data = alerts->get_unsafe("SELECT * FROM alerts WHERE comment IS NULL OR comment = '';");
    if(data.has_value()==false){
        return std::unexpected(data.error());
    }
    std::string result="";
    for(auto line : data.value()){
        result= std::format("{}{{}}{}",result,line);
    }
    return response_formater(false,"alerts_dashboard",result);
}
std::expected<std::string, std::string> Alerts::remove_alert(JUNK &request){
    //std::cout<<"MERGE CACAT";
    if(!request.contains("alert_id")){
        return std::unexpected("Invalid , there is no ID ");
    }
    //std::cout<<'['<<request["alert_id"].value()<<']'<<std::endl;
    auto data = alerts->query(
        "UPDATE alerts SET status = 'RESOLVED', comment = 'Fixed' WHERE id = ?", 
        {request["alert_id"].value()}
    );
    if(data.has_value()==false){
        return std::unexpected(data.error());
    }
    return response_formater(true,"remove_alert","nimic");

}