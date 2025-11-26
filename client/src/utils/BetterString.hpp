#pragma once

#include <string>
#include <vector>
#include <optional>
class BetterString{
    public:
    static std::vector<std::string> split(std::string text,const std::string splitter);
};