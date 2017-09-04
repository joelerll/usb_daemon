// #include <stdio.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>
// #include <stdlib.h> // exit()
// #include <string.h>
// #include <arpa/inet.h>
// #include <signal.h>
// #include "usbFunctions.h"
// #include <json/json.h>

// #define SERV_TCP_PORT 8236 /* server's port number */
// #define MAX_SIZE 5000


// void *runUsbServer(){

//   printf("servidor \n");

//   int sockfd, newsockfd, clilen;
//   struct sockaddr_in cli_addr, serv_addr;
//   int port;
//   char string[MAX_SIZE];
//   int len;

//   port = SERV_TCP_PORT;

//   if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//      perror("can't open stream socket");
//      exit(1);
//   }

//   bzero((char *) &serv_addr, sizeof(serv_addr));
//   serv_addr.sin_family = AF_INET;
//   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//   serv_addr.sin_port = htons(port);
  
//   if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//      perror("can't bind local address");
//      exit(1);
//   }

//   listen(sockfd, 5);

//   for(;;) {
//      clilen = sizeof(cli_addr);
//      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
//      if(newsockfd < 0) {
//         perror("can't bind local address");
//      }

//      getSolicitud(newsockfd,GLOBALJSON);
     
//      string[len] = 0;
//      close(newsockfd);
//   }  
// }
