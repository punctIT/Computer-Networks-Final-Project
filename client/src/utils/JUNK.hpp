#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <optional>


//Just
//Useful
//Notation
//Kinda

//is custom , made by me
//i hope it s work , but i don t promise 
//basically a piece of JUNK
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