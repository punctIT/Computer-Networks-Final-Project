#pragma once
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include "ProtocolFormater.hpp"
#include <optional>
#include <expected>
#include <QtCore/QObject>
#include <QWidget>
#include <mutex>
#include <shared_mutex>

class DataRequester: public QWidget , public ProtocolFormater {
    Q_OBJECT
    std::string ip;
    int port;
    int sock;
    struct sockaddr_in server_address;

    bool connected;
    std::optional<std::string> token;

    bool send_all(const void* data, size_t length);
    bool recv_all(void* data, size_t length);

    public:
    DataRequester();
    DataRequester& set_port(int port);
    DataRequester& set_ip(std::string ip);
    void set_token(std::string);
    DataRequester& configure();
    std::expected<void,std::string> sent(std::string data);
    std::expected<std::string,std::string> receive();
    void start_receiving();
    signals:

    void LoginData(QString mesaj);
    void LogsData(QString mesaj);
};