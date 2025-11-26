#include "BetterString.hpp"
#include <regex>

std::optional<std::vector<std::string>> BetterString::split_syslog(std::string log){
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
