#pragma once 

#include <string>
#include <memory>
#include <expected>
#include "ResponseFormater.hpp"
#include "../session_manager/SessionManager.hpp"
#include "../session_manager/AuthManager.hpp"
#include "../../utils/JUNK.hpp"

#include "commands/Logs.hpp"
#include "commands/Auth.hpp"
#include "commands/Alerts.hpp"
#include "commands/Source.hpp"
#include "commands/Filtres.hpp"
#include "commands/Agents.hpp"
#include <iostream>
#include <format>

class RequestHandler:public ResponseFormater{
    protected:
    std::shared_ptr<SessionManager>& session;
    std::shared_ptr<Auth> auth_requests;
    std::shared_ptr<Logs> logs_requests;
    std::shared_ptr<Alerts> alerts_requests;
    std::shared_ptr<Source> source_request;
    std::shared_ptr<Filtres> filtres_request;
    std::shared_ptr<Agents> agents_requests;
    public:
    RequestHandler(std::shared_ptr<SessionManager> &session,std::shared_ptr<AuthManager> &auth,
         std::shared_ptr<DBManager>& logs_db,std::shared_ptr<SourceManager>& source,
         std::shared_ptr<DBManager>& alerts , std::shared_ptr<FiltresManager> filtres,
         std::shared_ptr<DBManager>& agents
        );
    std::expected<std::string,std::string> match_type(JUNK &request);
    std::expected<std::string,std::string> match_request(int client,std::string request);
    
};