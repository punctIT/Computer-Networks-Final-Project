#include "DataRequester.h"
#include <iostream>
#include "../utils/JUNK.hpp"
#include <format>
DataRequester::DataRequester(){
    token=std::nullopt;
    connected=false;
}

DataRequester &DataRequester::set_port(int port){
    this->port=port;
    return *this;
}

DataRequester &DataRequester::set_ip(std::string ip){
    this->ip=ip;
    return *this;
}

void DataRequester::set_token(std::string token){
    this->token=token;
}

DataRequester &DataRequester::configure(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        throw std::runtime_error("Create socket error");
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(this->port);  
    
    if (inet_pton(AF_INET,this->ip.c_str(), &server_address.sin_addr) <= 0) {
        ::close(sock);
        throw std::runtime_error("invalid ip");
    }
    if (::connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        ::close(sock);
        throw std::runtime_error("connection failed");
    }
    connected=true;
    return *this;
}

bool DataRequester::send_all(const void* data, size_t length) {
    const char* ptr = static_cast<const char*>(data);
    size_t remaining = length;
    while (remaining > 0) {
        ssize_t written = ::send(sock, ptr, remaining, 0);
        if (written <= 0) 
            return false;
        ptr += written;
        remaining -= written;
    }
    return true;
}

bool DataRequester::recv_all(void* data, size_t length) {
    char* ptr = static_cast<char*>(data);
    size_t remaining = length;
    while (remaining > 0) {
        ssize_t read = ::recv(sock, ptr, remaining, 0);
        if (read <= 0)
            return false;
        ptr += read;
        remaining -= read;
    }
    return true;
}


std::expected<void, std::string> DataRequester::sent(std::string data) {
    if (!connected){
        emit lost_connection();
        return std::unexpected("Error: Not connected");
    }
        
    std::string content = "";
    auto test_data = JUNK::deserialize(data);
    if(!test_data){
        return std::unexpected(test_data.error());
    }
    if(this->token.has_value()){
        data = std::format("token:{{{}}};{}",this->token.value(),data);
    }
    int size = data.size();
    if (!send_all(&size, sizeof(int))) {
        return std::unexpected("Failed to send size header");
    }

    if (!send_all(data.c_str(), data.size())) {
        return std::unexpected("Failed to send data body");
    }

    return {};
}

std::expected<std::string, std::string> DataRequester::receive() {
    if (!connected) return std::unexpected("Error: Not connected");
    int size = 0;
    if (!recv_all(&size, sizeof(int))) {
        connected = false;
        return std::unexpected("Connection closed or header read error");
    }
    std::string content;
    try {
        content.resize(size);
    } catch (...) {
        return std::unexpected("Memory allocation failed");
    }
    if (!recv_all(&content[0], size)) {
        connected = false;
        return std::unexpected("Connection closed during body read");
    }
    return content;
}

void DataRequester::start_receiving()
{
    while(true){
        auto data = receive();
    
        if(!data.has_value()){
            continue;
        }
        qDebug()<<data.value().c_str();
        std::string rawData = data.value();
        auto junk_data = JUNK::deserialize(data.value());
        if(!junk_data.has_value()){
            continue;
        }
        if(!junk_data.value()["type"].has_value()){
            continue;
        }
        auto type = junk_data.value()["type"].value();
        auto qstr = QString::fromStdString(data.value());

        if(type=="login"){
            emit LoginData(qstr);
        }
        if(type=="logs"){
            emit LogsData(qstr);
        }
        if(type=="update_whitelist"){
            emit UpdateWhitelist(qstr);
        }
        if(type=="update_blacklist"){
            emit UpdateBlacklist(qstr);
        }
        if(type == "update_alerts"){
            emit UpdateAlersPopup(qstr);
        }
        if(type == "update_syslog_dashboard"){
            
            emit UpdateSyslogDashboard(qstr);
        }
        if(type == "update_agents_dashboard"){
            
            emit UpdateAgentsDashboard(qstr);
        }
        if(type == "update_unknown_syslog"){
            emit UpdateUnknownSyslig(qstr);
        }
        if(type == "update_unknown_agents"){
            emit UpdateUnknownAgent(qstr);
        }
        if(type == "alerts_dashboard"){
            emit UpdateAlertsDashboard(qstr);
        }
    }
    
}
