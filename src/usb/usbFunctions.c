#include <stdlib.h>
#include <unistd.h>
#include "usbFunctions.h"
#include <stdio.h>
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

// char pruebaNombrarDispositivo[5000] = "{ \"solicitud\": \"nombrar_dispositivos\" ,
//                                          \"nodo\": \"\/dev\/sdb\",
//                                          \"nombre\": \"PRUEBA_DISPOSITIVO\"}";

void nombrarDispositivo(int client_socket, char *JSONSolicitud){
    char *nodo = getValuePorCampo(JSONSolicitud,2);
    char *nombre = getValuePorCampo(JSONSolicitud,3);
    //Obtengo el elemento de la lista con el nodo ingresado
    ElementoLista *elem = Lista_BuscarXNodo(&listaUsb,nodo);
    if(elem==NULL){
        write(client_socket,"Si existe",sizeof("Si existe"));    
    }else{
        write(client_socket,"No existe",sizeof("No existe"));    
    }
}

void leerArchivo(int client_socket, char *JSONSolicitud){

}

void escribiArchivo(int client_socket, char *JSONSolicitud){

}