#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h> // exit()
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>

char * readFile();

void error(char *msg)
{
    perror(msg);
    exit(-1);
}

int main(){

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
  
  //Lectura de archivo que se mantendrá actualizado por el daemon

  FILE *fp;
  char json[50000] = "";
  fp = fopen("src/usb/listaDispositivos.txt","r");
  fseek(fp, 0, SEEK_SET);
  /* Read and display data */
  fread(json,strlen(json)+1, 50000, fp);

  printf("JSON: %s",json);

  while(1){
    client_socket = accept(sockfd, NULL, NULL);
    if (client_socket < 0) {
      close(client_socket);
      printf("Erro al conectarse \n");
    }
    write(client_socket,json,10*sizeof(json));    
  }
    
  close(client_socket);
  return 0;
  
}
