#include "SyslogReceiver.hpp"


#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>

#define loop while(true)


SyslogReceiver::SyslogReceiver()
{
}

SyslogReceiver &SyslogReceiver::set_thread_safe_queue(std::shared_ptr<ThreadSafeQueue<std::string>> queue)
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
        throw std::runtime_error("");
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

    loop{
        const int ret=poll(fds.data(),fds.size(),-1);
        if(ret < 0 ){
            throw std::runtime_error("Error poll");
        }
         for (size_t i = 0; i < fds.size(); i++) {
            if (!(fds[i].revents & POLLIN)) {
                continue;
            }
            if (fds[i].fd == server_fd.value()) {
                int client_fd = accept(server_fd.value(), nullptr, nullptr);
                if (client_fd < 0) {
                    std::cerr<<"[ERR] Accept error"<<std::endl;
                    continue;
                }
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

    int n = read(fd, buffer, buffer_size - 1);
    if (n > 0) {
        buffer[n] = '\0';
        client_buffers[fd] += buffer;
        std::string& client_buffer = client_buffers[fd];
        size_t pos = 0;
        while ((pos = client_buffer.find('\n')) != std::string::npos) {
            std::string complete_message = client_buffer.substr(0, pos);
            if (!complete_message.empty()) {
                log_queue->push(complete_message);
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
