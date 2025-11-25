#include "ProtocolFormater.hpp"
#include <format>
const std::string ProtocolFormater::login_request(std::string username, std::string password)
{
    if(username.empty())
        username="caca";
    if(password.empty())
        password="caca";
    return std::format("type:{{{}}};username:{{{}}};password:{{{}}};","login",username,password);
}

const std::string ProtocolFormater::register_request(std::string username, std::string password)
{
    return std::format("type:{{{}}};username:{{{}}};password:{{{}}};","register",username,password);
}
const std::string ProtocolFormater::logs_request(int start_id)
{
    return std::format("type:{{{}}};","logs");
}
