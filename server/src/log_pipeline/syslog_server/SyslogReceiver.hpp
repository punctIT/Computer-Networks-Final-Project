#pragma once


#include "../../utils/ThreadSafeQueue.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <optional>
#include <expected>
#include <utility>
class SyslogReceiver{
    std::shared_ptr<ThreadSafeQueue<std::pair<std::string,std::string>>> log_queue;

    std::optional<int> port,server_fd;
    std::unordered_map<int,std::string> client_buffers;
    std::unordered_map<int, std::string> client_ips;
    std::expected<void,std::string> RW_logs(int fd);
    public:
    SyslogReceiver();
    SyslogReceiver& set_thread_safe_queue(std::shared_ptr<ThreadSafeQueue<std::pair<std::string,std::string>>>);
    SyslogReceiver& set_port(int port);
    SyslogReceiver& configure_server();
    void start();
};