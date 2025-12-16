#include "Source.hpp"

Source::Source(std::shared_ptr<SourceManager> &source_manager):source_manager(source_manager)
{
    
}

std::expected<std::string, std::string> Source::add_whitelist_request(JUNK &request)
{
    if(!request.contains("ip"))
        return std::unexpected("invalid format");
    if(!request.contains("admin_username"))
        return std::unexpected("invalid format");
    if(!request.contains("source_name"))
        return std::unexpected("invalid format");
    auto data = source_manager->add_whitelist(request["ip"].value(),request["source_name"].value(),request["admin_username"].value());
    if(!data)
        return std::unexpected(data.error());
    return ResponseFormater::response_formater(true,"add_whitelist_ip","NONE");
}

std::expected<std::string, std::string> Source::add_blacklist_request(JUNK &request)
{
    if(!request.contains("ip"))
        return std::unexpected("invalid format");
    if(!request.contains("admin_username"))
        return std::unexpected("invalid format");
    auto data = source_manager->add_blacklist(request["ip"].value(),request["admin_username"].value());
    if(!data)
        return std::unexpected(data.error());
    return ResponseFormater::response_formater(true,"add_blacklist_ip","NONE");
}

std::expected<std::string, std::string> Source::remove_blacklist_request(JUNK &request)
{
    if(!request.contains("ip"))
        return std::unexpected("invalid format");
    auto data = source_manager->remove_blacklist(request["ip"].value());
    if(!data)
        return std::unexpected(data.error());
    return ResponseFormater::response_formater(true,"remove_blacklist_ip","NONE");
}

std::expected<std::string, std::string> Source::remove_whitelist_request(JUNK &request)
{
   if(!request.contains("ip"))
        return std::unexpected("invalid format");
    auto data = source_manager->remove_whitelist(request["ip"].value());
    if(!data)
        return std::unexpected(data.error());
    return ResponseFormater::response_formater(true,"remove_whitelist_ip","NONE");
}

std::expected<std::string, std::string> Source::get_updated_whitelist(JUNK &request)
{
    auto data = source_manager->get_whitelist();
    if (!data){
        return std::unexpected(data.error());
    }
    std::string result = "";
    for (auto d :data.value()){
        result=std::format("{}{{}}{}",result,d);
    }
    return ResponseFormater::response_formater(true,"update_whitelist",result);
}

std::expected<std::string, std::string> Source::get_updated_blacklist(JUNK &request)
{
    auto data = source_manager->get_blacklist();
    if (!data){
        return std::unexpected(data.error());
    }
    std::string result = "";
    for (auto d :data.value()){
        result=std::format("{}{{}}{}",result,d);
    }
    return ResponseFormater::response_formater(true,"update_blacklist",result);
}

std::pair<int, int> Source::get_count()
{
    return source_manager->get_count();
}
