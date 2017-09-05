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
#include <json/json.h>

#define SERV_TCP_PORT 8227

void error(char *msg)
{
    perror(msg);
}

char *jsonNombrarDipositivosSolicitud(char *solicitudNombrar, char *nodo, char *nombre) {

  json_object * jobj = json_object_new_object();

  json_object *jsonSoli = json_object_new_string(solicitudNombrar);
  json_object *jsonNombre = json_object_new_string(nombre);
  json_object *jsonNodo = json_object_new_string(nodo);

  json_object_object_add(jobj,"solicitud", jsonSoli);
  json_object_object_add(jobj,"nodo", jsonNodo);
  json_object_object_add(jobj,"nombre", jsonNombre);

  return (char *)json_object_to_json_string(jobj);
}

char *solicitudes_daemon() {
  int sockfd;
    struct sockaddr_in serv_addr;
    int port;
    char *retorno = NULL;
    char *ip = "127.0.0.1";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char *error_mensaje = malloc(sizeof(char *) * 5000);
    port = SERV_TCP_PORT;

    if (sockfd < 0) {
      error("ERROR opening socket");
      error_mensaje = "{\"solicitud\": \"listar_dispositivos\", \"dispositivos\": [], \"status\": -1,\"str_error\":  \"Error en crear socket\"}";
      return error_mensaje;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
      error("ERROR connecting");
      error_mensaje = "{\"solicitud\": \"listar_dispositivos\", \"dispositivos\": [], \"status\": -1,\"str_error\":  \"Error en conectar socket, el daemon puede no estar corriendo\"}";
      return error_mensaje;
    }
    char solicitudEjemplo[50000] = "{ \"solicitud\": \"listar_dispositivos\" }";
    int n = write(sockfd,solicitudEjemplo,strlen(solicitudEjemplo));
    if (n < 0) {
      error("ERROR writing to socket");
      error_mensaje = "{\"solicitud\": \"listar_dispositivos\", \"dispositivos\": [], \"status\": -1,\"str_error\":  \"Error en hacer peticion al socket\"}";
      return error_mensaje;
    }  
    char recvBuff[50000];
    n = read(sockfd, recvBuff, 500*sizeof(recvBuff));
    if (n < 0) {
      error("ERROR red to socket");
      error_mensaje = "{\"solicitud\": \"listar_dispositivos\", \"dispositivos\": [], \"status\": -1,\"str_error\":  \"Error leer al socket\"}";
      return error_mensaje;
    }
    // printf("%s\n", recvBuff);
    retorno = (char *)recvBuff;
  return retorno;
}


char *nombrar_dispositivo(const char *nombre) {
  int sockfd;
    struct sockaddr_in serv_addr;
    int port;
    char *retorno = NULL;
    char *ip = "127.0.0.1";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char *error_mensaje = malloc(sizeof(char *) * 5000);

    port = SERV_TCP_PORT;
    // char *error_mensaje = "\"\"";
    if (sockfd < 0) {
      error("ERROR opening socket");
      error_mensaje = "{\"solicitud\": \"nombrar_dispositivo\", \"nombre\": \"\", \"nodo\": \"\", \"status\": -1,\"str_error\":  \"Error en crear socket\"}";
      return error_mensaje;
    }
      
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
      error("ERROR connecting");
      error_mensaje = "{\"solicitud\": \"nombrar_dispositivo\", \"nombre\": \"\", \"nodo\": \"\", \"status\": -1,\"str_error\":  \"Error en conectar socket, el daemon puede no estar corriendo\"}";
      return error_mensaje;
    }
    // char *aa = malloc(sizeof(char *) * strlen(nombre));
    // strcpy(aa, nombre);
    // char solicitudEjemplo[50000] = "";
    // printf("%s\n", aa );
    // printf("asdsadadsadas\n");
    // strcpy(solicitudEjemplo,jsonNombrarDipositivosSolicitud("nombrar_dispositivo",
    //                                                              "/dev/sdc",
    //                                                              "NUEEEVO"));
    // printf("===%s\n", solicitudEjemplo);
    int n = write(sockfd,nombre,strlen(nombre));
    if (n < 0) {
      error("ERROR writing to socket");
      error_mensaje = "{\"solicitud\": \"escribir_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\",\"status\": -1,\"str_error\":  \"Error en hacer peticion al socket\"}";
      return error_mensaje;
    }  
    char recvBuff[50000];
    n = read(sockfd, recvBuff, 500*sizeof(recvBuff));
    if (n < 0) {
      error("ERROR red to socket");
      error_mensaje = "{\"solicitud\": \"escribir_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\",\"status\": -1,\"str_error\":  \"Error leer al socket\"}";
      return error_mensaje;
    }
    retorno = (char *)recvBuff;
  return retorno;
}

char *escribir_archivo(const char *json) {
  int sockfd;
    struct sockaddr_in serv_addr;
    int port;
    char *retorno = NULL;
    char *ip = "127.0.0.1";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char *error_mensaje = malloc(sizeof(char *) * 5000);

    port = SERV_TCP_PORT;

    if (sockfd < 0) {
      error("ERROR opening socket");
      error_mensaje = "{\"solicitud\": \"escribir_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error en crear socket\"}";
      return error_mensaje;
    }
      
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
      error("ERROR connecting");
      error_mensaje = "{\"solicitud\": \"escribir_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error en conectar socket, el daemon puede no estar corriendo\"}";
      return error_mensaje;
    }
    // char *aa = malloc(sizeof(char *) * strlen(nombre));
    // strcpy(aa, nombre);
    // char solicitudEjemplo[50000] = "";
    // printf("%s\n", aa );
    // printf("asdsadadsadas\n");
    // strcpy(solicitudEjemplo,jsonNombrarDipositivosSolicitud("nombrar_dispositivo",
    //                                                              "/dev/sdc",
    //                                                              "NUEEEVO"));
    // printf("===%s\n", solicitudEjemplo);
    int n = write(sockfd,json,strlen(json));
    if (n < 0) {
      error("ERROR writing to socket");
      error_mensaje = "{\"solicitud\": \"escribir_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\",\"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error en hacer peticion al socket\"}";
      return error_mensaje;
    }  
    char recvBuff[50000];
    n = read(sockfd, recvBuff, 500*sizeof(recvBuff));
    if (n < 0) {
      error("ERROR red to socket");
      error_mensaje = "{\"solicitud\": \"escribir_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"tamano_contenido\": -1,,\"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error leer al socket\"}";
      return error_mensaje;
    }
    retorno = (char *)recvBuff;
    // printf("%s\n", recvBuff);
  return retorno;
}

char *leer_archivo(const char *json) {
  int sockfd;
    struct sockaddr_in serv_addr;
    int port;
    char *retorno = NULL;
    char *ip = "127.0.0.1";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    char *error_mensaje = malloc(sizeof(char *) * 5000);

    port = SERV_TCP_PORT;

    if (sockfd < 0) {
      error("ERROR opening socket");
      error_mensaje = "{\"solicitud\": \"leer_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error en crear socket\"}";
      return error_mensaje;
    }
      
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
      error("ERROR connecting");
      error_mensaje = "{\"solicitud\": \"leer_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error en conectar socket, el daemon puede no estar corriendo\"}";
      return error_mensaje;
    }
    // char *aa = malloc(sizeof(char *) * strlen(nombre));
    // strcpy(aa, nombre);
    // char solicitudEjemplo[50000] = "";
    // printf("%s\n", aa );
    // printf("asdsadadsadas\n");
    // strcpy(solicitudEjemplo,jsonNombrarDipositivosSolicitud("nombrar_dispositivo",
    //                                                              "/dev/sdc",
    //                                                              "NUEEEVO"));
    // printf("===%s\n", solicitudEjemplo);
    int n = write(sockfd,json,strlen(json));
    if (n < 0) {
      error("ERROR writing to socket");
      error_mensaje = "{\"solicitud\": \"leer_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error en hacer peticion al socket\"}";
      return error_mensaje;
    }  
    char recvBuff[50000];
    n = read(sockfd, recvBuff, 500*sizeof(recvBuff));
    if (n < 0) {
      error("ERROR red to socket");
      error_mensaje = "{\"solicitud\": \"leer_archivo\", \"nombre\": \"\", \"nombre_archivo\": \"\", \"contenido\": \"\", \"status\": -1,\"str_error\":  \"Error leer al socket\"}";
      return error_mensaje;
    }
    retorno = (char *)recvBuff;
    // printf("%s\n", recvBuff);
  return retorno;
}