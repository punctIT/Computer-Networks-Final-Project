#pragma once

#include <string>
#include <vector>
#include <optional>
class LogParser{
    public:
    static std::optional<std::vector<std::string>> split_syslog(std::string log);
};