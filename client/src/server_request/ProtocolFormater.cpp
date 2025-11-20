#include "ProtocolFormater.hpp"
#include <format>
std::string ProtocolFormater::login_request(std::string username, std::string password)
{
    if(username.empty())
        username="caca";
    if(password.empty())
        password="caca";
    return std::format("type:{{{}}};username:{{{}}};password:{{{}}};","login",username,password);
}