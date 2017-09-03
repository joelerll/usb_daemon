// Una funcion validara los json de entrada
#include <stdio.h>
// Una funcion enviara a la salida los json
#include "utils.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>

#define SERV_TCP_PORT 8236

void error(char *msg)
{
    perror(msg);
    exit(0);
}

char *prueba() {
  char *retorno;
  int sockfd;
  struct sockaddr_in serv_addr;
  char *serv_host = "localhost";
  struct hostent *host_ptr;
  int port;
  int buff_size = 0;
  char recvBuff[5000];
  memset(recvBuff, 0, sizeof recvBuff);
  port = SERV_TCP_PORT;

  if((host_ptr = gethostbyname(serv_host)) == NULL) {
     perror("gethostbyname error");
     exit(1);
  }
  
  if(host_ptr->h_addrtype !=  AF_INET) {
     perror("unknown address type");
     exit(1);
  }
  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = 
     ((struct in_addr *)host_ptr->h_addr_list[0])->s_addr;
  serv_addr.sin_port = htons(port);
  
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
     perror("can't open stream socket");
     exit(1);
  }
 
  if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
     perror("can't connect to server");
     exit(1);
  }

  read(sockfd, recvBuff, 10*sizeof(recvBuff));
  close(sockfd);
  printf("%s", recvBuff);
  // retorno = &recvBuff;
  return retorno;
}
