#pragma once
#include <memory>
#include <expected>
#include "../ResponseFormater.hpp"


class SourceManager;
class JUNK;
class Source:ResponseFormater{
    std::shared_ptr<SourceManager>& source_manager; 
    public:
    Source(std::shared_ptr<SourceManager>& source_manager);
    std::expected<std::string, std::string> add_whitelist_request(JUNK &request);
};