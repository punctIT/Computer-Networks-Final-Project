#include "Agents.hpp"


#include "../../../utils/BetterString.hpp"
#include <format>
Agents::Agents( std::shared_ptr<DBManager> &agents): agents(agents) {}

std::expected<std::string, std::string> Agents::update_dashboard(JUNK &request)
{
   
    if(request["source"].has_value()==false){
        return std::unexpected("invalid data , no source");
    }
    
    auto sources = agents->get_unsafe("select distinct(hostname) from  metrics;");
    if(sources.has_value()==false){
        return std::unexpected(sources.error());
    }
    std::string all_sourece = "";
    for(auto source : sources.value()){
        all_sourece = std::format("{}{{}}{}",all_sourece,source);
    }
    std::string source_status_data =""; 
    auto source_status = agents->get_unsafe("SELECT hostname, CASE WHEN (strftime('%s', 'now') - MAX(timestamp)) > 180 THEN 'INACTIVE' ELSE 'ACTIVE' END AS status FROM metrics GROUP BY hostname ORDER BY hostname;");
    if (source_status.has_value()!=false){
        for (auto source : source_status.value()){
            std::cout<<source<<std::endl;
            source_status_data = std::format("{}{{}}{}",source_status_data,source);
        }
    }
    if(request["source"].value()=="NONE" || request["source"].value().empty()){
        return std::format("type:{{{}}};succes:{{{}}};sources:{{{}}};agents:{{{}}};","update_agents_dashboard",true,all_sourece,source_status_data);
    }
    auto data = agents->query("select * from  metrics where id = (select max(id) from metrics) and hostname = ?;",{request["source"].value()});
    if (data.has_value()==false){
        return std::unexpected(data.error());
    }
    return std::format("type:{{{}}};succes:{{{}}};sources:{{{}}};agent_data:{{{}}};agents:{{{}}};","update_agents_dashboard",true,all_sourece,data.value()[0],source_status_data);
}
