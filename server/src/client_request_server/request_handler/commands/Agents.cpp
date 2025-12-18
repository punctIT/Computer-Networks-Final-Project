#include "Agents.hpp"


#include "../../../utils/BetterString.hpp"
#include <format>
Agents::Agents( std::shared_ptr<DBManager> &agents): agents(agents) {}
std::expected<std:: string, std::string> Agents::update_dashboard(JUNK &request)
{
   
    if(request["source"]. has_value()==false){
        return std::unexpected("invalid data , no source");
    }
    
    auto sources = agents->get_unsafe("select distinct(hostname) from  metrics;");
    if(sources.has_value()==false){
        return std:: unexpected(sources.error());
    }
    std::string all_sourece = "";
    for(auto source : sources.value()){
        all_sourece = std::format("{}{{}}{}",all_sourece,source);
    }
    std::string source_status_data =""; 
    auto source_status = agents->get_unsafe("SELECT hostname, CASE WHEN (strftime('%s', 'now') - MAX(timestamp)) > 180 THEN 'INACTIVE' ELSE 'ACTIVE' END AS status FROM metrics GROUP BY hostname ORDER BY hostname;");
    if (source_status.has_value()!=false){
        for (auto source : source_status.value()){
            source_status_data = std::format("{}{{}}{}",source_status_data,source);
        }
    }
    
    std::string metric="";
    if(request["source"].value()!="NONE" && ! request["source"].value().empty()){
         std::cout <<request["source"].value()<<std:: endl;
        auto data = agents->query("select * from  metrics where id = (select max(id) from metrics where hostname = ?) and hostname = ?;",{request["source"].value(),request["source"].value()});
        if (data.has_value() && !data.value().empty()) {
            metric = data.value()[0];
        }
        else {
            std::cerr<<data.error()<<std::endl;
        }
    }
    
    return std::format("type:{{{}}};succes:{{{}}};sources:{{{}}};agent_data:{{{}}};agents:{{{}}};","update_agents_dashboard",true,all_sourece,metric,source_status_data);
}

std::expected<std::string, std::string> Agents::update_unknown_agents(JUNK &request)
{
    auto data_logs = agents->get_unsafe("select * from unknown_metrics limit 100;");
    if(!data_logs.has_value()){
        return std::unexpected(data_logs.error());
    }
    std::string result="";
    for(auto log : data_logs.value()){
        result=std::format("{}{{}}{}",result,log);
    }
    auto sources_logs = agents->get_unsafe("select distinct(ip) from unknown_metrics ;");
    if(!sources_logs.has_value()){
        return std::unexpected(sources_logs.error());
    }
    std::string sources="";
    for(auto log : sources_logs.value()){
        sources=std::format("{}{{}}{}",sources,log);
    }
    return std::format("type:{{{}}};succes:{{{}}};agents:{{{}}};sources:{{{}}};","update_unknown_agents",true,result,sources);

}
