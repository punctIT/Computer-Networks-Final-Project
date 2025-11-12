#include "ProtocolFormater.hpp"
#include <format>
std::string ProtocolFormater::login_request(std::string username, std::string password)
{
    return std::format("type:{{{}}};content:{{{}}};token:{{{}}};","ana","are","mere");
}