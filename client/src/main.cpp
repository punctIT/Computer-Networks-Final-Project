#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main(){
    // Creează socket-ul
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Eroare la crearea socket-ului" << endl;
        return 1;
    }

    // Configurează adresa serverului
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);  // Portul serverului
    
    // Convertește adresa IP
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        cerr << "Adresa invalida" << endl;
        close(sock);
        return 1;
    }

    // Conectează-te la server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        cerr << "Conexiune esuata" << endl;
        close(sock);
        return 1;
    }

    cout << "Conectat la server!" << endl;

    // Textul pe care vrei să-l trimiți
    string text = "Salut de la client!";
    int size = text.size();

    // Trimite size-ul (ca int binar)
    send(sock, &size, sizeof(int), 0);
    
    // Trimite textul
    send(sock, text.c_str(), size, 0);
    
    cout << "Am trimis: " << text << " (size: " << size << ")" << endl;

    // Citește răspunsul de la server
    int received_size = 0;
    
    // Primește size-ul
    recv(sock, &received_size, sizeof(int), 0);
    
    if (received_size > 0 && received_size < 4096) {
        // Primește textul
        char buffer[4096] = {0};
        recv(sock, buffer, received_size, 0);
        
        cout << "Am primit de la server: " << buffer << " (size: " << received_size << ")" << endl;
    }

    // Închide conexiunea
    close(sock);
    
    return 0;
}