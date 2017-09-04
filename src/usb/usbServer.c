#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h> // exit()
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include "usbFunctions.h"
#include <json/json.h>
#include "usbServer.h"
#include "usbJson.h"
#include <pthread.h>

#define SERV_TCP_PORT 8237 /* server's port number */
#define MAX_SIZE 5000

void *runUsbServer(){
    
  printf("servidor \n");

  int sockfd, client_socket; 
  struct sockaddr_in serv_addr;
  int port;
  char solicitud[5000];

  char *ip = "127.0.0.1";
  
  port = SERV_TCP_PORT;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
     perror("can't open stream socket");
     exit(1);
  }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        //error("ERROR en bind socket");
    }
    // FIN inicializar socket
    listen(sockfd,5);
  
    while(1) {
        client_socket = accept(sockfd, NULL, NULL);
        if (client_socket < 0) {
            close(client_socket);
            printf("Erro al conectarse \n");
        }
        write(client_socket,"sssssss",10*sizeof("sssssss"));    
        close(client_socket);
        //Se lee solicitud
        //read(client_socket, solicitud, 10*sizeof(solicitud));
        //printf("lectura%s",solicitud);
        //Se analiza solicitud
        //analizarSolicitud(client_socket,solicitud);
        //
        //string[len] = 0;
    }   
}


void analizarSolicitud(int client_socket, char *JSONSolicitud){
    //Solo de prueba porque no tengo formato Json de cano
    // int i = 0, j = 1;
    // char prueba[50001];

    // while(*(JSONSolicitud+j) != ']'){
    //     //*(prueba+i) = *(JSONSolicitud+j);
    //     prueba[i] = *(JSONSolicitud+j);
    //     i++;
    //     j++;
    // }
    // *(prueba+i) = '\0';
    //

    char *tipoSolicitud = getTipoSolicitud(JSONSolicitud);

    if(strcmp(tipoSolicitud,"")){
        listarDispositivos(client_socket);
    }
    if(strcmp(tipoSolicitud,"nombrar_dispositivo")){

    }
    if(strcmp(tipoSolicitud,"leer_archivo")){

    }
    if(strcmp(tipoSolicitud,"escribir_archivo")){

    }

}

void doHilo(){
    pthread_t hiloServerUsb = 0;
    int status = 0;
    fseek(stdin,0,SEEK_END);
    status = pthread_create(&hiloServerUsb, NULL, runUsbServer, NULL);
    if (status < 0) {
        printf("Error al crear el hilo\n");
    }    
    pthread_join(hiloServerUsb,NULL);
}
