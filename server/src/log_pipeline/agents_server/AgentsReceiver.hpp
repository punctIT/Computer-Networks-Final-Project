#pragma once


#include "../../utils/ThreadSafeQueue.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <optional>
#include <expected>
#include <utility>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <format>
#include "../source_manager/SourceManager.hpp"


class AgentsReceiver{
    std::shared_ptr<ThreadSafeQueue<LogEvent>> log_queue;

    std::optional<int> port,server_fd;
    std::unordered_map<int,std::string> client_buffers;
    std::unordered_map<int, std::string> client_ips;
    std::expected<void,std::string> RW_logs(int fd);
    std::shared_ptr<SourceManager> source_manager;
    public:
    AgentsReceiver( std::shared_ptr<SourceManager> source_manager);
    AgentsReceiver& set_thread_safe_queue(std::shared_ptr<ThreadSafeQueue<LogEvent>>);
    AgentsReceiver& set_port(int port);
    AgentsReceiver& configure_server();
    void start();
};