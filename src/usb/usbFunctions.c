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

void leerArchivo(int client_socket, char *JSONSolicitud){

}

void escribiArchivo(int client_socket, char *JSONSolicitud){

}