#include "DataParser.hpp"
#include <regex>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


std::optional<std::vector<std::string>> DataParser::split_syslog(std::string log){
    auto get_pri = [](int x){
        int value = x%8;
        std::vector<std::string> pri = {
            "Emergency", "Alert", "Critical", "Error",
            "Warning", "Notice", "Informational", "Debug"
        };
        return pri[value];
    };
    static const std::regex syslog_regex(
        R"(^<(\d+)>([A-Z][a-z]{2}\s+\d{1,2}\s+\d{2}:\d{2}:\d{2})\s+(\S+)\s+(\S+):\s+(.*)$)"
    );

    std::smatch m;
    if(!std::regex_match(log, m, syslog_regex))
        return std::nullopt;

    std::vector<std::string> logs;
    logs.push_back(get_pri(std::stoi(m[1].str())));
    for(int i=2;i<=5;++i){
        std::string field = m[i].str();
        size_t pos = 0;
        while ((pos = field.find('\'', pos)) != std::string::npos) {
            field.insert(pos, "'");
            pos += 2; 
        }
        logs.push_back(field);
    }
   
    return logs;
}

std::expected<std::vector<std::string>,std::string> DataParser::get_agent_data(std::string agent_log)
{
    //std::cout <<agent_log<< std::endl;
    try {
        json j = json::parse(agent_log);
        for (auto& [key, val] : j.items()) {
        std::cout << "Cheia: " << key << " | Valoarea: " << val << std::endl;
    
        if (val.is_string()) {
            std::cout << "   -> (Asta este un string)" << std::endl;
        }
        if (val.is_object()) {
            std::cout << "   -> (Asta este un alt obiect JSON imbricat)" << std::endl;
        }
    }
    }
    catch (std::exception &e){
        return std::unexpected(e.what());
    }
    return std::unexpected("ceva");
}
