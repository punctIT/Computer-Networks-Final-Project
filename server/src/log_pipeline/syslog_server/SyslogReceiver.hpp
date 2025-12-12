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
#include "../source_managers/SourceManager.hpp"


class SyslogReceiver{
    std::shared_ptr<ThreadSafeQueue<LogEvent>> log_queue;

    std::optional<int> port,server_fd;
    std::unordered_map<int,std::string> client_buffers;
    std::unordered_map<int, std::string> client_ips;
    std::expected<void,std::string> RW_logs(int fd);
    std::shared_ptr<SourceManager> source_manager;
    public:
    SyslogReceiver( std::shared_ptr<SourceManager> source_manager);
    SyslogReceiver& set_thread_safe_queue(std::shared_ptr<ThreadSafeQueue<LogEvent>>);
    SyslogReceiver& set_port(int port);
    SyslogReceiver& configure_server();
    void start();
};