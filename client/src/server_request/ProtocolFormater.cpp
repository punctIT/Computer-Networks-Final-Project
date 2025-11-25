#include "ProtocolFormater.hpp"
#include <format>
const std::string ProtocolFormater::login_request(const std::string username,const std::string password)
{
    return std::format("type:{{{}}};username:{{{}}};password:{{{}}};","login",username,password);
}

const std::string ProtocolFormater::register_request(const std::string username,const  std::string password)
{
    return std::format("type:{{{}}};username:{{{}}};password:{{{}}};","register",username,password);
}
const std::string ProtocolFormater::logs_request(const int start_id)
{
    return std::format("type:{{{}}};","logs");
}
