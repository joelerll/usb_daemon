#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{

    int sockfd;
    //int bytesReceived = 0;
    struct sockaddr_in serv_addr;
    unsigned char recvBuff[50000];

    char *ip = "127.0.0.1";
    char *puerto = "5001";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(atoi(puerto));
  	serv_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        error("error");
    }

    //Se envía información al socket
    int n = write(sockfd,"PRUEBA DE SOCKET\n",strlen("PRUEBA DE SOCKET\n"));
    if (n < 0)
        error("ERROR writing to socket");

    read(sockfd, recvBuff, 10*sizeof(recvBuff));
    printf("--%s",recvBuff);
       
    return 0;
}