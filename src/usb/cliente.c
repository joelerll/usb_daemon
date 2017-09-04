#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>

#define SERV_TCP_PORT 8237

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){

    int sockfd;
    struct sockaddr_in serv_addr;
    char recvBuff[5000];
    int port;
    char *ip = "127.0.0.1";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    port = SERV_TCP_PORT;

    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(port);
  	serv_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    /* se escribe la solicitud en el socket */
    char solicitudEjemplo[5000] = "{ \"solicitud\": \"\" }";
    
    // int n = write(sockfd,solicitudEjemplo,sizeof(solicitudEjemplo));
    // if (n < 0)
    //     error("ERROR writing to socket");

     read(sockfd, recvBuff, sizeof(recvBuff));
    
    printf("Respuesta: %s",recvBuff);
       
    return 0;
}