#pragma once
#include <memory>
#include <expected>
#include "../ResponseFormater.hpp"
#include "../../../utils/JUNK.hpp"
#include "../../../log_pipeline/source_manager/SourceManager.hpp"

class Source:ResponseFormater{
    std::shared_ptr<SourceManager>& source_manager; 
    public:
    Source(std::shared_ptr<SourceManager>& source_manager);
    std::expected<std::string, std::string> add_whitelist_request(JUNK &request);
    std::expected<std::string, std::string> add_blacklist_request(JUNK &request);
};