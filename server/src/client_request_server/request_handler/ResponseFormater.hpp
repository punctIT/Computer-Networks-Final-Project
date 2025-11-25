#pragma once 
#include <string>
#include <format>
class ResponseFormater{
    public:
    std::string response_formater(bool succes,std::string type ,std::string content){
        return std::format("succes:{{{}}};type:{{{}}};content:{{{}}};",succes,type,content);
    }

};