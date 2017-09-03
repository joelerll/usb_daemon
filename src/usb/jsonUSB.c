#include <json/json.h>
#include <stdio.h>
#include "usbFunctions.h"

void parseToJson(listaDispConectados *listaDisp){
    
    FILE *fp= NULL;
    char json[50000] = "[";
    
    for(int i=0; i<listaDisp->n_Dispositivos; i++){
    
        struct InfoUSB *info = *((listaDisp->lista)+i);
        /*Creating a json object*/
        json_object * jobj = json_object_new_object();    
        
        /*Creating json strings*/
        json_object *nombre = json_object_new_string("");
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
        if(i!=(listaDisp->n_Dispositivos-1)) strcat(json,",");
    }   
    strcat(json,"]");
    //printf("%s",json);
    strcpy(GLOBALJSON,json);
    
    //printf("--ACT: %s\n",i);

}
