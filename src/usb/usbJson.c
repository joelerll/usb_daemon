#include <json/json.h>
#include <stdio.h>
#include <string.h>
#include "usbLista.h"
#include "usbJson.h"
#include "usbFunctions.h"

void toJson(){

    strcpy(json,"[");

    ElementoLista *elem = NULL;
    for (elem = Lista_Primero(&listaUsb); elem != NULL; elem = Lista_Siguiente(&listaUsb, elem)){
        struct InfoUSB *info = (struct InfoUSB *)elem->objeto;

        /*Creating a json object*/
        json_object * jobj = json_object_new_object();    
        
        /*Creating json strings*/
        json_object *nombre = json_object_new_string(info->nombre);
        json_object *idVendor = json_object_new_string(info->idVendor);
        json_object *idProduct = json_object_new_string(info->idProduct);
        json_object *montaje = json_object_new_string(info->usbDirMount);
        json_object *nodo = json_object_new_string(info->usbNodo);
        /*Form the json object*/
        /*Each of these is like a key value pair*/
        json_object_object_add(jobj,"nombre", nombre);
        json_object_object_add(jobj,"idVendor", idVendor);
        json_object_object_add(jobj,"idProduct", idProduct);
        json_object_object_add(jobj,"montaje", montaje);
        json_object_object_add(jobj,"nodo", nodo);
         /*Now printing the json object*/
        //printf("\n%s",json_object_to_json_string(jobj));
        strcat(json,json_object_to_json_string(jobj));
        if(Lista_Siguiente(&listaUsb, elem)!=NULL) strcat(json,",");
    }   
    strcat(json,"]");
    printf("--ACT: %s",json);
}
