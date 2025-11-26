#include "BetterString.hpp"
#include <regex>

std::vector<std::string> BetterString::split(std::string text, const std::string splitter)
{
    std::vector<std::string> content;
    size_t pos = 0;
    while ((pos = text.find(splitter)) != std::string::npos) {
        content.push_back(text.substr(0, pos));
        text.erase(0, pos + splitter.length());
    }
    content.push_back(text);
    return content;
}
