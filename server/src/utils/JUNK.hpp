#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>

class JUNK{
    std::unordered_map<std::string, std::string> data;
    
    public:
    std::optional<std::string> operator[](const std::string);
    void display();
    static std::string serialize(JUNK data);
    static JUNK deserialize(std::string);
    void add(std::string,std::string);
    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};