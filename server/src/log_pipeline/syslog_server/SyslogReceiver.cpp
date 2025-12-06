#include "SyslogReceiver.hpp"



#define loop while(true)


SyslogReceiver::SyslogReceiver( std::shared_ptr<SourceManager> source_manager)
{
    this->source_manager=source_manager;
}

SyslogReceiver &SyslogReceiver::set_thread_safe_queue(std::shared_ptr<ThreadSafeQueue<std::pair<std::string,std::string>>> queue)
{
    this->log_queue=queue;
    return *this;
}

SyslogReceiver &SyslogReceiver::set_port(int port)
{
   this->port=port;
   return *this;
}

SyslogReceiver &SyslogReceiver::configure_server()
{
    sockaddr_in address;
    int opt = 1;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw std::runtime_error("[Err] Soker Error");
    }
    if (setsockopt(server_fd.value(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        throw std::runtime_error("[ERR] setsockopt error");
    }
    if (!this->port.has_value()){
        throw std::runtime_error("Error , port is none");
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port.value());

    if (bind(server_fd.value(), (struct sockaddr *)&address, sizeof(address)) < 0) {
        throw std::runtime_error("[Err] Bind Error");
    }
    return *this;
}


void SyslogReceiver::start()
{
    if(!this->port.has_value()){
        throw std::runtime_error("Error , port is none");
    }
    if(!this->server_fd.has_value()){
        throw std::runtime_error("Server fd is none");
    }
    if (listen(server_fd.value(), 10) < 0) {
        throw std::runtime_error("listen failed");
    }
    std::cout << "Syslog server started and listen on port "<<port.value()<<std::endl;
    std::vector <pollfd> fds;
    pollfd server_poll;

    server_poll.fd=server_fd.value();
    server_poll.events=POLLIN;
    fds.push_back(server_poll);
    

    loop {
        const int ret=poll(fds.data(),fds.size(),-1);
        if(ret < 0 ){
            throw std::runtime_error("Error poll");
        }
         for (size_t i = 0; i < fds.size(); i++) {
            if (!(fds[i].revents & POLLIN)) {
                continue;
            }
            if (fds[i].fd == server_fd.value()) {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd.value(), (struct sockaddr*)&client_addr, &client_len);
                if (client_fd < 0) {
                    std::cerr<<"[ERR] Accept error"<<std::endl;
                    continue;
                }

                char ip_str[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(client_addr.sin_addr), ip_str, INET_ADDRSTRLEN);
                std::string ip_source(ip_str);
                if(source_manager->check_ip_blacklist(ip_source)){
                    close(client_fd); 
                    std::cout << "[WARN] Connection denied from blacklisted IP: " << ip_source << std::endl;
                    continue;
                }
                client_ips[client_fd] = ip_source;

                pollfd client_poll;
                client_poll.fd = client_fd;
                client_poll.events = POLLIN;
                fds.push_back(client_poll);
                std::cout << "[INFO] Client connected: fd=" << client_fd << std::endl;    
                continue;        
            } 
            auto status= RW_logs(fds[i].fd);
            if (!status.has_value()) {
                std::cerr<<status.error()<<std::endl;
                close(fds[i].fd);
                fds.erase(fds.begin() + i);
                --i;
            }
                 
        }
    }

}
std::expected<void, std::string> SyslogReceiver::RW_logs(int fd)
{
    const int buffer_size=4096;
    char buffer[buffer_size];
    if(source_manager->check_ip_blacklist(client_ips[fd])){
        client_buffers.erase(fd);
        auto ip = client_ips[fd];
        client_ips.erase(fd);
        return std::unexpected(std::format("[WARN]Active connection dropped (Blacklisted IP): IP:{}" ,ip));
    }
    int n = read(fd, buffer, buffer_size - 1);
    if (n > 0) {
        buffer[n] = '\0';
        client_buffers[fd] += buffer;
        std::string& client_buffer = client_buffers[fd];
        size_t pos = 0;
        while ((pos = client_buffer.find('\n')) != std::string::npos) {
            std::string complete_message = client_buffer.substr(0, pos);
            if (!complete_message.empty()) {
                log_queue->push(std::make_pair(client_ips[fd], complete_message));
            }
            client_buffer.erase(0, pos + 1);
        }
    }
    else if (n == 0) {
        client_buffers.erase(fd);
        return std::unexpected("[INFO] Client disconnected)");
    }
    else {

        client_buffers.erase(fd);
        return std::unexpected("[ERR] Read Error");
    }
    return {};
}
