#pragma once 

/*
    type:{};
    content:{};
    token:{};
*/

#include <string>

class ProtocolFormater
{
public:
    const std::string login_request(std::string username,std::string password);
    const std::string register_request(std::string username,std::string password);
    const std::string logs_request(int start_id);
};

