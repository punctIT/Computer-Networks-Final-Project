#pragma once

#include <string>
#include <vector>
#include <optional>
#include <expected>
class DataParser{
    public:
    static std::optional<std::vector<std::string>> split_syslog(std::string log);
    static std::expected<std::vector<std::string>,std::string> get_agent_data(std::string agent_log);
};