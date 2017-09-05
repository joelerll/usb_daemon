#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <json/json.h>

#define SERV_TCP_PORT 8225

char *jsonNombrarDipositivosSolicitud(char *solicitudNombrar, char *nodo, char *nombre);
char *enviarArchivo();
char *jsonEscribirArchivoSolicitud(char *solicitudEscribir, char *nombre, char * nombreArchivo, int tmCont, char * contenido);

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){

    int sockfd;
    struct sockaddr_in serv_addr;
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

    //Codio util para realizar pruebas de listar_dispositivos y nombrar_dispositivos
    // Prueba listarDispositivos
    // char solicitudEjemplo[50000] = "{ \"solicitud\": \"listar_dispositivos\" }";
    // Prueba nombrarDispositivos
    // char solicitudEjemplo[50000] = "";
    // strcpy(solicitudEjemplo,jsonNombrarDipositivosSolicitud("nombrar_dispositivo",
    //                                                              "/dev/sdc",
    //                                                              "NUEEEVO"));
    
    char solicitudEjemplo[50000] = "";
    strcpy(solicitudEjemplo,enviarArchivo());

    int n = write(sockfd,solicitudEjemplo,strlen(solicitudEjemplo));
    if (n < 0)
         error("ERROR writing to socket");
    
    char recvBuff[50000];
    n = read(sockfd, recvBuff, 500*sizeof(recvBuff));
    
    printf("Respuesta: %s",recvBuff);
    


    // char * respuesta = enviarArchivo("/home/boscoand/Documentos/prueba.txt",
    //               "/home/boscoand/Documentos/proyectoNuevoo1.txt",317);

    //Codigo util para realizar pruebas de escribir archivo

    // printf("%s\n\n\n\n",respuesta);
    //
    //char *prueba;

    // int i=1;
    // json_object * jobj = json_tokener_parse(respuesta);
    // enum json_type type;
    // json_object_object_foreach(jobj, key, val) {
    //     type = json_object_get_type(val);
    //     switch (type) {
    //     case json_type_string: 
    //         //Devuelve el primer valor que por defecto siempre será 
    //         //la función de la solicitud
    //         if(i==5){
    //             prueba = (char *)json_object_get_string((json_object *)val);
    //         }
    //         i++;
    //         //printf ("\n%s-%s\n",json_object_get_string((json_object *)key),
    //         //                    json_object_get_string((json_object *)val));
    //         break;
        
    //     default:
    //         // printf("no es string");
    //         // printf("%s",key);
    //         i++;
    //         break;
    //     }
    // }

    // //printf("FINAAAL :%s",prueba);

    // FILE *file2 = fopen ("/home/boscoand/Documentos/NUEEEVO.txt", "w" );
    
    // i=0;
    // while(i!=(317)){
    //     printf("%c",*(prueba+i));
    //     fputc (*(prueba+i),file2);
    //     i++;
    // }   
    // fclose(file2);
    // //printf("\n\nSolo: %s",prueba);

    return 0;
}

// { ‘solicitud’: ‘escribir_archivo’, ‘nombre‘: ..., ‘nombre_archivo’: ...,
// ‘tamano_contenido: ..., ‘contenido’: ....}

char *enviarArchivo(){

    char *archivo = "/home/boscoand/Documentos/prueba.txt";
    char *destino = "/home/boscoand/Documentos/proyectoNuevoo1.txt";
    int tam = 317;
 
    FILE *file1 , *file2;
    int data1 =0;
    char prueba[tam];
    
    file1 = fopen ( archivo, "r" );
    file2 = fopen ( destino, "w" );

    int i = 0;    
    while ( (data1 = fgetc ( file1 )) != EOF ) {
        prueba[i]=data1;
        i++;
    }
    
    i=0;
    while(i!=tam){
        fputc (prueba[i],file2);
        //printf("%c",prueba[i]);
        i++;
    }

    fclose ( file1 );
    fclose ( file2 );
    
    //printf("FUNCION:%s",prueba);
    //printf("%i",strlen(prueba));

    return jsonEscribirArchivoSolicitud("escribir_archivo",
                                        "no name",
                                        "Copia.txt",
                                        317,
                                        prueba);
}


char *jsonEscribirArchivoSolicitud(char *solicitudEscribir, char *nombre, char * nombreArchivo, int tmCont, char * contenido) {
    
    json_object * jobj = json_object_new_object();

    json_object *jsonSoli = json_object_new_string(solicitudEscribir);
    json_object *jsonNombre = json_object_new_string(nombre);
    json_object *jsonNombreArchivo = json_object_new_string(nombreArchivo);
    json_object *jsonTamanoContenido = json_object_new_int(tmCont);
    json_object *jsonContenido = json_object_new_string(contenido);

    json_object_object_add(jobj,"Solicitud", jsonSoli);
    json_object_object_add(jobj,"Nombre", jsonNombre);
    json_object_object_add(jobj,"Nombre del Archivo", jsonNombreArchivo);
    json_object_object_add(jobj,"Tamano Contenido", jsonTamanoContenido);
    json_object_object_add(jobj,"Contenido", jsonContenido);

    /*Now printing the json object*/
    return (char *)json_object_to_json_string(jobj);

}

//
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