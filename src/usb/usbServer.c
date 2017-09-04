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
  
    struct udev* udev = udev_new();
    if (!udev) {
        fprintf(stderr, "udev_new() failed\n");
    }
    
    doHiloDaemon();
    while(1) {    
        //printf("%s",json);
        client_socket = accept(sockfd, NULL, NULL);
        if (client_socket < 0) {
            close(client_socket);
            printf("Erro al conectarse \n");
        }

        //Se lee solicitud
        read(client_socket, solicitud, 10*sizeof(solicitud));
        printf("Solicitud: %s",solicitud);
        //Se analiza solicitud y de acuerdo a eso se responde lo deseado
        analizarSolicitud(client_socket,solicitud);
        close(client_socket);
    }   
}

void listarDispositivos(int client_socket){
    write(client_socket,json,10*sizeof(json));    
    close(client_socket);
}

void nombrarDispositivo(int client_socket, char *JSONSolicitud){

}

void leerArchivo(int client_socket, char *JSONSolicitud){

}

void escribiArchivo(int client_socket, char *JSONSolicitud){

}

void analizarSolicitud(int client_socket, char *JSONSolicitud){

    char *tipoSolicitud = getTipoSolicitud(JSONSolicitud);

    if(strcmp(tipoSolicitud,"listar_dispositivos")==0){
        listarDispositivos(client_socket);
    }
    if(strcmp(tipoSolicitud,"nombrar_dispositivo")==0){

    }
    if(strcmp(tipoSolicitud,"leer_archivo")==0){

    }
    if(strcmp(tipoSolicitud,"escribir_archivo")==0){

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

void doHiloDaemon(){
    pthread_t hiloDaemon = 0;
    int status = 0;
    fseek(stdin,0,SEEK_END);
    status = pthread_create(&hiloDaemon, NULL, runDaemon, NULL);
    if (status < 0) {
        printf("Error al crear el hilo\n");
    }    
    //pthread_join(hiloDaemon,NULL);
}

void *runDaemon(){
    struct udev* udev = udev_new();
    if (!udev) {
        fprintf(stderr, "udev_new() failed\n");
    }
    while(1){
        enumerate_devices(udev);
        printf("%s",json);
    }
    udev_unref(udev);
}