#include "clienteucp.h"
ClienteUDP::ClienteUDP() {
    // Configuración de la dirección del servidor
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1", &direccionServidor.sin_addr.s_addr);// Cambiar a la dirección IP del servidor
    // configuracion de la direccion del servidor
    direccionCliente.sin_family = AF_INET;
    direccionCliente.sin_addr.s_addr = INADDR_ANY;
    direccionCliente.sin_port = htons(8083);
}

ClienteUDP::~ClienteUDP() {
    // Cerrar todos los sockets
    for (int i = 0; i < 3; ++i) {
        close(enviarSocket[i]);
        close(recibirSocket[i]);
    }
}

void ClienteUDP::inicializarEnvio(int puerto, int index) {
    // Crear socket para enviar
    enviarSocket[index] = socket(AF_INET, SOCK_DGRAM, 0);
    enviarPuertos[index] = puerto;
}

void ClienteUDP::inicializarRecepcion(int puerto, int index) {
    // Crear socket para recibir
    recibirSocket[index] = socket(AF_INET, SOCK_DGRAM, 0);

    // Enlazar el socket a un puerto específico
    sockaddr_in direccionEscucha = direccionCliente;

    switch (index) {
    case INDEX_STRING:
        direccionEscucha.sin_port = htons(PUERTO_REC_STRING);
        break;
    case INDEX_HEXADECIMAL:
        direccionEscucha.sin_port = htons(PUERTO_REC_HEXADECIMAL);
        break;
    case INDEX_BINARIO:
        direccionEscucha.sin_port = htons(PUERTO_REC_BINARIO);
        break;
    default:
        break;
    }
    if(bind(recibirSocket[index], reinterpret_cast<sockaddr*>(&direccionCliente), sizeof(direccionCliente))<=0){
     std::cout << "Info: "<< strerror(errno) << std::endl;
   }

    recibirPuertos[index] = puerto;

    // Iniciar un hilo para la recepción de mensajes en este puerto
    std::thread receptor(&ClienteUDP::recibirMensajes, this, index,direccionEscucha);
    receptor.detach(); // Liberar el hilo principal del control del hilo de recepción
}

void ClienteUDP::recibirMensajes(int index,sockaddr_in direccion) {
    while (true) {
        char buffer[1024];

        socklen_t len = sizeof(direccion);
        recvfrom(recibirSocket[index], buffer, sizeof(buffer), 0, reinterpret_cast<sockaddr*>(&direccion), &len);
        std::string mensaje(buffer);
        std::cout << "Puerto " << recibirPuertos[index] << " - Mensaje recibido: " << mensaje << std::endl;

    }
}
void ClienteUDP:: mostarVector(std::vector<unsigned char> vector){
    for (int i = 0; i < vector.size(); i++) {
        int d = vector[i];
        std::cout << std::hex << d;
    }
}

void ClienteUDP::enviarMensaje(std::string mensaje, int index) {
    // Enviar el mensaje al servidor
    sockaddr_in direccionDestino = direccionServidor;
    switch (index) {
    case INDEX_STRING:
        direccionDestino.sin_port = htons(PUERTO_ENV_STRING);
        break;
    case INDEX_HEXADECIMAL:
        direccionDestino.sin_port = htons(PUERTO_ENV_HEXADECIMAL);
        break;
    case INDEX_BINARIO:
        direccionDestino.sin_port = htons(PUERTO_ENV_BINARIO);
        break;
    default:
        break;
    }

    sendto(enviarSocket[index], mensaje.data(), mensaje.size(), 0, reinterpret_cast<sockaddr*>(&direccionDestino), sizeof(direccionDestino));

}
