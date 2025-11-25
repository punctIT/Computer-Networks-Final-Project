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
    const std::string login_request(const std::string username,const std::string password);
    const std::string register_request(const std::string username,const std::string password);
    const std::string logs_request(const int start_id);
};

