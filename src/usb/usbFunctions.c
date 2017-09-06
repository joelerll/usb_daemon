#include <stdlib.h>
#include <unistd.h>
#include "usbFunctions.h"
#include <stdio.h>
#include <string.h>
#include "usbJson.h"
#include "usbLista.h"

struct InfoUSB *crearInfoUsb(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct){
    struct InfoUSB *info = (struct InfoUSB *)malloc(sizeof(struct InfoUSB));
    info->usbDirMount=usbDirMount;
    info->usbNodo=usbNodo;
    info->idVendor=idVendor;
    info->idProduct=idProduct;
    info->nombre="no name";
    info->estado=1;

    return info;
}

void listarDispositivos(int client_socket){
    write(client_socket,json,sizeof(json));    
    close(client_socket);
}

void nombrarDispositivo(int client_socket, char *JSONSolicitud){
    
    char *nodo = getValuePorCampo(JSONSolicitud,2);
    char *nombre = getValuePorCampo(JSONSolicitud,3);
    //Obtengo el elemento de la lista con el nodo ingresado
    ElementoLista *elem = Lista_BuscarXNodo(&listaUsb,nodo);

    if(elem==NULL){
        //Función que devuelve json
        char *respuesta = jsonNombrarDipositivosRespuesta("nombrar_dispositivo",
                                                -1,
                                                "",
                                                "",
                                                "Dispositivo no conectado");
        write(client_socket,respuesta,500*sizeof(respuesta));    
    }else{
        struct InfoUSB *info = (struct InfoUSB *)elem->objeto;
        //Modificar nombre
        info->nombre = nombre;
        // strcpy(info->nombre, nombre);
        //Función que devuelve json
        char *respuesta = (char *) jsonNombrarDipositivosRespuesta("nombrar_dispositivo",
                                                0,
                                                info->nombre,
                                                info->usbNodo,
                                                "Nombre ingresado con éxito");
        write(client_socket,respuesta,500*sizeof(respuesta));    
    }
    close(client_socket);
}

//{ ‘solicitud’: ‘leer_archivo’, ‘nombre‘: ..., ‘nombre_archivo’: ... }
void leerArchivo(int client_socket, char *JSONSolicitud){
    
    char *nombreUsb = getValuePorCampo(JSONSolicitud,2);
    char *nombreArchivo = getValuePorCampo(JSONSolicitud,3);
    ElementoLista *elem = Lista_BuscarXNombre(&listaUsb,nombreUsb);

    if(elem==NULL){
        char *respuesta = (char *)jsonLeerArchivoRespuesta("leer_archivo", 
                                                            nombreUsb, 
                                                            nombreArchivo, 
                                                            "Error",
                                                            -1, 
                                                            "No se encontró dispositivo con nombre ingresado");
        write(client_socket,respuesta,500*sizeof(respuesta));

    }else{
        int data1 =0;
        char prueba[500000];
        char direccion[50000] = "";
        struct InfoUSB *info = (struct InfoUSB *)elem->objeto;
        strcat(direccion,info->usbDirMount);
        strcat(direccion,"/");
        strcat(direccion,nombreArchivo);
        // printf("%s\n", direccion);
        FILE *archivoLeido = fopen ( direccion, "r" );
        char *respuesta = "";

        if(archivoLeido){
            int i = 0;    
            while ( (data1 = fgetc ( archivoLeido )) != EOF ) {
                prueba[i]=data1;
                i++;
            }
            // printf("%s\n", prueba);
            fclose(archivoLeido);
            respuesta = (char *)jsonLeerArchivoRespuesta("leer_archivo", 
                                                                nombreUsb, 
                                                                nombreArchivo, 
                                                                prueba, 
                                                                0,
                                                                "Lectura de archivo exitosa");
        }else{
            respuesta = (char *)jsonLeerArchivoRespuesta("leer_archivo", 
                                                                nombreUsb, 
                                                                nombreArchivo, 
                                                                "", 
                                                                -1,
                                                                "Archivo no existe");
        }
        write(client_socket,respuesta,500*sizeof(respuesta));
    }
    close(client_socket);
}


// { ‘solicitud’: ‘escribir_archivo’, ‘nombre‘: ..., ‘nombre_archivo’: ...,
// ‘tamano_contenido: ..., ‘contenido’: ....}
void escribiArchivo(int client_socket, char *JSONSolicitud){

    char *nombreUsb = getValuePorCampo(JSONSolicitud,2);
    char *nombreArchivo = getValuePorCampo(JSONSolicitud,3);
    int tamano = getIntPorCampo(JSONSolicitud,4);
    char *contenido = getValuePorCampo(JSONSolicitud,4);

    ElementoLista *elem = Lista_BuscarXNombre(&listaUsb,nombreUsb);

    if(elem==NULL){
        char *respuesta = (char *)jsonEscribirRespuesta("escribir_archivo", 
                                                        nombreUsb, 
                                                        nombreArchivo, 
                                                        -1, 
                                                        "No se encontró dispositivo con nombre ingresado");
        write(client_socket,respuesta,500*sizeof(respuesta));    
    }else{
        struct InfoUSB *info = (struct InfoUSB *)elem->objeto;
        char direccion[50000] = "";

        strcat(direccion,info->usbDirMount);
        strcat(direccion,"/");
        strcat(direccion,nombreArchivo);
        
        // printf("[DirMount: %s]\n",info->usbDirMount);
        // printf("[Direccion: %s]",direccion);

        FILE *archivoNuevo = fopen (direccion, "w" );

        int i=0;
        //printf("tam:%i",tamano);
        while(i!=(tamano)){
             fputc (*(contenido+i),archivoNuevo);
             i++;
        }   
        fclose(archivoNuevo);

        char *respuesta = (char *)jsonEscribirRespuesta("escribir_archivo", 
                                                        nombreUsb, 
                                                        nombreArchivo, 
                                                        0, 
                                                        "Copia de archivo exitosa");

        // printf("Respuesta: %s",respuesta);
        write(client_socket,respuesta,500*sizeof(respuesta));    

    }
    close(client_socket);
}


