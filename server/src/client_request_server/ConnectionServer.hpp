#pragma once 
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <optional>
#include <memory>


class SessionManager;
class RequestHandler;
class AuthManager;
class DBManager;
class SourceManager;

class ConnectionServer
{
private:
    std::optional<int> server_fd, client;
    std::shared_ptr<SessionManager> session_manager;
    std::shared_ptr<AuthManager> auth;
    std::shared_ptr<RequestHandler> request_handler;
    std::shared_ptr<DBManager> logs_db;
    std::shared_ptr<SourceManager> source_manager;
    sockaddr_in address;
    int opt = 1;
    std::optional<int> port;
    
public:
    ConnectionServer();
    ConnectionServer& set_port(int port);
    ConnectionServer& bind_data();
    ConnectionServer& set_logs_db(std::shared_ptr<DBManager> db);
    ConnectionServer& set_source_manager(std::shared_ptr<SourceManager> source);
    void start();
    ~ConnectionServer();
};

