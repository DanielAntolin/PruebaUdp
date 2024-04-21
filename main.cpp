#include <iostream>
#include "clienteucp.h"



int main()
{
    ClienteUDP cliente;

    // Inicializar clientes para enviar en puertos 8081, 8082, 8083
    cliente.inicializarEnvio(PUERTO_ENV_STRING, INDEX_STRING);

    // Inicializar escucha

    cliente.inicializarRecepcion(PUERTO_REC_STRING,INDEX_STRING);


    cliente.enviarMensaje("Mensaje 1",INDEX_STRING);

    for(;;){

    }

}
