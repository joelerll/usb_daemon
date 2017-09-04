#include <stdlib.h>
#include <unistd.h>
#include "usbFunctions.h"
#include <stdio.h>
#include "usbJson.h"

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
    printf("%s",json);
    write(client_socket,json,10*sizeof(json));    
    close(client_socket);
}

void nombrarDispositivo(int client_socket, char *JSONSolicitud){

}

void leerArchivo(int client_socket, char *JSONSolicitud){

}

void escribiArchivo(int client_socket, char *JSONSolicitud){

}
