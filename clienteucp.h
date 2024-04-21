#ifndef CLIENTEUCP_H
#define CLIENTEUCP_H

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <errno.h>
#include <cstring>
#include <vector>

// PUERTOS ENVIOS
const int PUERTO_ENV_STRING = 8080;
const int PUERTO_ENV_HEXADECIMAL = 8081;
const int PUERTO_ENV_BINARIO = 8082;

// PUERTOS ESCUCHA
const int PUERTO_REC_STRING = 8083;
const int PUERTO_REC_HEXADECIMAL = 8084;
const int PUERTO_REC_BINARIO = 8085;

// INDEX PUERTOS
const int INDEX_STRING = 0;
const int INDEX_HEXADECIMAL = 1;
const int INDEX_BINARIO = 2;

class ClienteUDP {
private:
    int enviarSocket[3];
    int recibirSocket[3];
    int enviarPuertos[3];
    int recibirPuertos[3];
    sockaddr_in direccionServidor;
    sockaddr_in direccionCliente;

public:
    ClienteUDP();
    ~ClienteUDP();
    void inicializarEnvio(int puerto, int index);
    void inicializarRecepcion(int puerto, int index);
    void recibirMensajes(int index,sockaddr_in direccion);
    void enviarMensaje(std::string mensaje, int index);
    std::vector<unsigned char> vectorHexa;
    void mostarVector(std::vector<unsigned char> vector);
};

#endif
