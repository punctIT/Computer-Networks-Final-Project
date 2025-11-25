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
    std::string login_request(std::string username,std::string password);
    std::string logs_request(int start_id);
};

