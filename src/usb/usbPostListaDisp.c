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

char * readFile();

void error(char *msg)
{
    perror(msg);
    exit(-1);
}

void server(){

  // definicion de las variables
  int sockfd, client_socket;
  struct sockaddr_in serv_addr;
  
  char *ip = "127.0.0.1";
  char *puerto = "5001";
  
  // inicializacion del socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  
  if (sockfd < 0) {
    error("ERROR al iniciar el socket");
  }

  // set el puerto y los datos necesarios para inicializar el server
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(ip);
  serv_addr.sin_port = htons(atoi(puerto));

  //Enlace 
  if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
    error("ERROR en bind socket");
  }

  listen(sockfd,100000);
  
  while(1){
    client_socket = accept(sockfd, NULL, NULL);
    if (client_socket < 0) {
      close(client_socket);
      printf("Error al conectarse \n");
    }
    //pthread_mutex_lock(&candado);
    write(client_socket,GLOBALJSON,10*sizeof(GLOBALJSON));    
    //pthread_mutex_unlock(&candado);
  }
    
  //close(client_socket);
  return 0;
  
}
