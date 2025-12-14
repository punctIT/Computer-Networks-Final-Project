#include "JUNK.hpp"
#include <iostream>
#include <string.h>
#include <format>

std::optional<std::string> JUNK::operator[](const std::string key)
{
    if(data.contains(key))
        return data[key];
    return std::nullopt;
}

void JUNK::display()
{
    std::string JUNK = "";
    for (const auto& [key, value] : data) {
        std::cout << key << " = " << value << "\n";
    }

}
std::expected<std::string,std::string> JUNK::serialize(JUNK data)
{
    std::string JUNK = "";
    for (const auto& [key, value] : data) {
        JUNK = std::format("{}:{{{}}};{}", key, value,JUNK);
    }
    if(JUNK.empty()){
        return std::unexpected("Invalid JUNK object");
    }
    return JUNK;
}

// 'NUME':{nume:nume};

std::expected<JUNK,std::string> JUNK::deserialize(std::string data)
{
    JUNK new_data;
    int left_count=0;
    int format_count =0;
    int poz=0;
    std::string key_val[2];
    for(auto ch : data){
        if (ch == '\n'||ch =='\r'){
            continue;
        }
        if(ch==':'&&left_count==0){
            poz+=1;
            format_count+=1;
            continue;
        }
        if(ch =='{'){
            left_count+=1;
            if (left_count==1){
                continue;
            }
        }
        if(ch=='}'){
            left_count-=1;
             if (left_count==0){
                continue;
            }
        }
        if(ch==';'&&left_count==0){
            new_data.add(key_val[0],key_val[1]);
            poz=0;
            key_val[0].clear();key_val[1].clear();
        }
        else {
            key_val[poz].push_back(ch);
        }
        
    }
    if(format_count == 0 || left_count!=0 || new_data.empty()){
        return std::unexpected(std::format("Invalid data , not a valid JUNK format \n {}",data));
    }
    return new_data;
}
bool JUNK::empty()
{
    return data.empty();
}
bool JUNK::contains(std::string key)
{
    return data.contains(key);
}
void JUNK::add(std::string key, std::string value)
{
    data[key]=value;
}

