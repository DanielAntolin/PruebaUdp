#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(){
    int sock = socket(AF_INET,SOCK_DGRAM,0);

    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1", &server.sin_addr.s_addr);

    for (;;){
        std::string data;
        std::getline(std::cin,  data);
        sendto(sock,data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&server), sizeof(server));


    }



    for (;;){

        char buffer[1024];

        int nRecv = recv(sock, buffer, sizeof(buffer) ,0 );
        std::string data(buffer, nRecv);
        std::cout << "Muestro desde cliente" << data << std::endl;

    }
}
