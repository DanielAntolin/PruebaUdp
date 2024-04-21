#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

struct Persona{
    std::string nombre;
    int edad;

    //Persona (std::string pnombre, int pedad):nombre(pnombre), edad(pedad){
    //    std::cout<< "Persona creada"<< std::endl;
    // }
};

int main()
{

    Persona persona ={
                       .nombre= "Diego",
                       .edad=12
    };


    int sock = socket(AF_INET,SOCK_DGRAM,0);

    sockaddr_in server;
    server.sin_family=AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr= INADDR_ANY;

    if (bind (sock, reinterpret_cast<sockaddr*>(&server), sizeof (server))<=0){
        std::cout << "Info: "<< strerror(errno) << std::endl;
    }

    char buffer[1024];

    for (;;){
        sockaddr_in client;
        socklen_t length;

        int nRecv = recvfrom(sock, buffer, sizeof(buffer) ,0, reinterpret_cast<sockaddr*>(&client), &length );
        std::string data(buffer, nRecv);
        std::cout << "Muestro " << data << std::endl;
        if (data == "persona\n"){


            std::string data = "muestro datos persona";
            sendto(sock,data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&client), length);

        }
    }
    close(sock);





    return 0;
}
