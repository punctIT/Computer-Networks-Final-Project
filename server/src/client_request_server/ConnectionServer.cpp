#include "ConnectionServer.hpp"

ConnectionServer::ConnectionServer()
{
    std::cout << "Starting http server for client" << std::endl;
    port = std::nullopt;
}

ConnectionServer &ConnectionServer::set_port(int port)
{
    this->port = port;
    return *this;
}

ConnectionServer &ConnectionServer::bind_data()
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        throw std::runtime_error("[ERR]Sokect request server");
    }
    if (setsockopt(server_fd.value(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        throw std::runtime_error("[ERR]Socket opt request server");
    }
    if (!this->port.has_value())
    {
        throw std::runtime_error("Error , port is none");
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->port.value());

    if (bind(server_fd.value(), (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        throw std::runtime_error("[ERR] bind error");
    }
    return *this;
}

ConnectionServer &ConnectionServer::set_logs_db(std::shared_ptr<DBManager> db)
{
    logs_db = db;
    return *this;
}

ConnectionServer &ConnectionServer::set_alerts_db(std::shared_ptr<DBManager> db)
{
    alert_db = db;
    return *this;
}

ConnectionServer &ConnectionServer::set_filtres_manager(std::shared_ptr<FiltresManager> fl)
{
    this->filtres_manager=fl;
   return *this;
}

ConnectionServer &ConnectionServer::set_source_manager(std::shared_ptr<SourceManager> source)
{
    source_manager = source;
    return *this;
}

void ConnectionServer::start()
{
    this->session_manager = std::make_shared<SessionManager>();
    this->auth = std::make_shared<AuthManager>();
    this->request_handler = std::make_shared<RequestHandler>(session_manager, auth, logs_db, source_manager,alert_db,filtres_manager);

    if (!this->port.has_value())
    {
        throw std::runtime_error("Error , port is none");
    }
    if (!this->server_fd.has_value())
    {
        throw std::runtime_error("Server fd is none");
    }
    if (listen(server_fd.value(), 10) < 0)
    {
        throw std::runtime_error("listen failed");
    }

    std::cout << "Server started and listen on port 8080\n";

    while (true)
    {
        socklen_t addrlen = sizeof(address);
        int client = accept(server_fd.value(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (client < 0)
        {
            perror("accept");
            continue;
        }
        std::cout << "New Client Connected" << std::endl;

        std::thread([client, this]()
                    { new_client(client); })
            .detach();
    }
}

void ConnectionServer::new_client(int client)
{
    while (true){
        int len = 0;
        char buffer[4096] = {0};
        int bytes_read = read(client, &len, sizeof(int));
        if (bytes_read <= 0)
        {
            std::cout << "Client Disconnected" << std::endl;
            break;
        }
        read(client, buffer, len);
        auto response = request_handler->match_request(client, buffer);
        if (response)
        {
            std::string &dataStr = *response;
            int data_len = dataStr.size();
            send(client, &data_len, sizeof(data_len),MSG_NOSIGNAL);
            const char *dataPtr = dataStr.c_str();
            int total_sent = 0;
            while (total_sent < data_len)
            {
                int sent = send(client, dataPtr + total_sent, data_len - total_sent,MSG_NOSIGNAL);
                if (sent <= 0)
                    break;
                total_sent += sent;
            }
        }
        else
        {
            std::string error = std::format("succes:{};type:{{error}};content:{{{}}};", "false", response.error());
            int size = error.size();
            write(client, &size, sizeof(int));
            write(client, error.c_str(), size);
        }
    }
    close(client);
}

ConnectionServer::~ConnectionServer()
{
}
