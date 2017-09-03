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

void error(char *msg)
{
    perror(msg);
    exit(-1);
}

void getSolicitud(int client_socket, char *JSONSolicitud);

void *server(){

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
  
  //getSolicitud(GLOBALJSON);
  //getSolicitud(GLOBALJSON);
  //getSolicitud(GLOBALJSON);

  //lee la solicitud que envia el socket
  char solicitud[50000] = "";

  while(1){
    client_socket = accept(sockfd, NULL, NULL);
    if (client_socket < 0) {
      close(client_socket);
      printf("Error al conectarse \n");
    }

    int n = read(client_socket, solicitud, sizeof(solicitud));
    if (n < 0) 
      error("ERROR al leer el socket");

    //Aqui tengo que Analizar solicitud para ver que devuelvo
    getSolicitud(client_socket,GLOBALJSON);
    //
  }
  
}

void getSolicitud(int client_socket, char JSONSolicitud[]){

  write(client_socket,GLOBALJSON,10*sizeof(GLOBALJSON));    
  close(client_socket);

  FILE *fp = NULL;
  fp = fopen("./prueba.txt","a");
  //fprintf(fp,JSONSolicitud);
  
  fprintf(fp,"%s",GLOBALJSON);

  fprintf (fp,"JSON string: %sn", GLOBALJSON);
  json_object * jobj = json_tokener_parse(GLOBALJSON);

  enum json_type type;
  json_object_object_foreach(jobj, key, val) {
  type = json_object_get_type(val);
  switch (type) {
    case json_type_string: fprintf (fp,"type: json_type_string, ");
      fprintf (fp,"value: %sn", json_object_get_string(val));
      break;
    }
  }

  fclose(fp);

}
