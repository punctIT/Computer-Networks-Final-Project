#include "RequestHandler.hpp"
#include <format>

std::expected<std::string,std::string> RequestHandler::match_request(int client,std::string request){
    std::cout << "Request: "<< request << std::endl;
    auto data = JUNK::deserialize(request);
    if(!data.has_value()){
        return std::unexpected(data.error());
    }
    if(!(*data).contains("type")){
        return std::unexpected("Invalid data: don t containt a type");
    }
    auto response = this->match_type(*data);
    if(response){
        return *response;
    }
    else {
        return RequestHandler::response_formater(false,"Error",response.error());
    }
    

}



std::expected<std::string, std::string> RequestHandler::match_type(JUNK &request){
    if(!request["type"].has_value()){
        return std::unexpected("unknown type");
    }
    //request.display();
    const std::string type = request["type"].value();
    if(type=="login"){
        return auth_requests->login_request(request);
    }
    if(type=="register"){
        return auth_requests->register_request(request);
    }

    if(!request["token"].has_value() || !session->check_token(request["token"].value())){
        return std::unexpected("Invalid Token");
    }
    //std::cout<<type<<" "<<type.size()<<std::endl;;
    if(type=="ceva"){
        return response_formater(true,"ceva","nimic");
    }
    if(type=="logout"){
        return auth_requests->logout_request(request);
    }
    if(type=="logs"){
        return home_request(request);
    }
    if(type=="update_syslog_dashboard"){
        return logs_requests->update_syslog_dashboard(request);
    }
    if(type=="update_unknown_syslog"){
        return logs_requests->update_unknown_syslog_dashboard(request);
    }
    if(type=="add_whitelist_ip"){
        return source_request->add_whitelist_request(request);
    }
    if(type=="add_blacklist_ip"){
        return source_request->add_blacklist_request(request);
    }
    if(type=="remove_whitelist_ip"){
        return source_request->remove_whitelist_request(request);
    }
    if(type=="remove_blacklist_ip"){
        return source_request->remove_blacklist_request(request);
    }
    if(type=="update_whitelist"){
        return source_request->get_updated_whitelist(request);
    }
    if(type=="update_blacklist"){
        return source_request->get_updated_blacklist(request);
    }
    if(type=="update_alerts"){
        return alerts_requests->last_alert(request);
    }
    if(type=="alerts_dashboard"){
        return alerts_requests->update_alerts_dashboard(request);
    }
    if(type == "update_agents_dashboard"){
        return agents_requests->update_dashboard(request);
    }
    if(type == "update_unknown_agents"){
        return agents_requests->update_unknown_agents(request);
    }
    if(type == "remove_alert"){
        return alerts_requests->remove_alert(request);
    }
    if(type == "update_filtres"){
        return filtres_request->get_filtres();
    }
    if(type== "add_filtres"){
        std::cout<<"ASASDASDASD"<<std::endl;
        return filtres_request->add_filtres(request);
    }
    if(type== "remove_filtres"){
        return filtres_request->remove_filtres(request);
    }
    return std::unexpected("unknown type");
}


RequestHandler::RequestHandler(std::shared_ptr<SessionManager> &session, 
    std::shared_ptr<AuthManager> &auth, std::shared_ptr<DBManager>& logs_db,std::shared_ptr<SourceManager>&source,
    std::shared_ptr<DBManager>& alerts, std::shared_ptr<FiltresManager> filtres ,std::shared_ptr<DBManager>& agents
)
    : session(session){
       auth_requests=std::make_shared<Auth>(session,auth);
       logs_requests=std::make_shared<Logs>(logs_db);
       alerts_requests=std::make_shared<Alerts>(alerts);
       source_request=std::make_shared<Source>(source);
       filtres_request= std::make_shared<Filtres>(filtres);
       agents_requests=std::make_shared<Agents>(agents);
    }

std::expected<std::string, std::string> RequestHandler::home_request(JUNK &request)
{
    auto source_data = source_request->get_count();
    return std::format("type:{{{}}};succes:{{{}}};whitelist:{{{}}};blacklist:{{{}}};",
        "logs",true,source_data.first,source_data.second);
}