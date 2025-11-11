#include "DataRequester.hpp"
#include <iostream>
#include "../utils/JUNK.hpp"
DataRequester &DataRequester::set_port(int port){
    this->port=port;
    return *this;
}

DataRequester &DataRequester::set_ip(std::string ip){
    this->ip=ip;
    return *this;
}

DataRequester &DataRequester::configure(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Eroare la crearea socket-ului" << std::endl;
        //return 1;
    }
    
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);  // Portul serverului
    
    // Convertește adresa IP
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        std::cerr << "Adresa invalida" << std::endl;
        close(sock);
        //return 1;
    }
    return *this;
}

std::string DataRequester::sent_request(std::string data)
{
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        // cerr << "Conexiune esuata" << endl;
        close(sock);
        // return 1;
    }

    std::cout << "Conectat la server!" << std::endl;

    // Textul pe care vrei să-l trimiți
    std::string text = "Salut de la client!";
    int size = text.size();

    // Trimite size-ul (ca int binar)
    send(sock, &size, sizeof(int), 0);
    
    // Trimite textul
    send(sock, text.c_str(), size, 0);
    
    std::cout << "Am trimis: " << text << " (size: " << size << ")" << std::endl;

    // Citește răspunsul de la server
    int received_size = 0;
    
    // Primește size-ul
    recv(sock, &received_size, sizeof(int), 0);
    char buffer[4096] = {0};
    if (received_size > 0 && received_size < 4096) {
        // Primește textul
       
        recv(sock, buffer, received_size, 0);
        
        std::cout << "Am primit de la server: "  << " (size: " << received_size << ")" << std::endl;
        JUNK::deserialize(buffer).display();
    }

    close(sock);
    return buffer;
}
