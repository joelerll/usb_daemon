#include <json/json.h>
#include <stdio.h>


void jsonListarDipositivosRespuesta(char *solicitudListar, char *nombreDispositivo, char * idVendor, char * montaje, char * nodo, int status, char * stErr){
  
  json_object * jobj = json_object_new_object();
  json_object * jobj2 = json_object_new_object();

  
  json_object *jarrayDispositivos = json_object_new_array();

  json_object *jsonSoli = json_object_new_string(solicitudListar);
  json_object *jNombre = json_object_new_string(nombreDispositivo);
  json_object *jIdVendor = json_object_new_string(idVendor);
  json_object *jMontaje = json_object_new_string(montaje);
  json_object *jNodo = json_object_new_string(nodo);

  json_object_object_add(jobj2,"vendor", jIdVendor);

  json_object_array_add(jarrayDispositivos,jNombre);
  json_object_array_add(jarrayDispositivos,jobj2);
  json_object_array_add(jarrayDispositivos,jMontaje);
  json_object_array_add(jarrayDispositivos,jNodo);

  json_object *jstatus = json_object_new_int(status);
  json_object *jstErr = json_object_new_string(stErr);

  json_object_object_add(jobj,"Solicitud", jsonSoli);
  json_object_object_add(jobj,"Dispositivos", jarrayDispositivos);
  json_object_object_add(jobj,"Status", jstatus);
  json_object_object_add(jobj,"Error", jstErr);

  /*Now printing the json object*/
  printf ("%s \n",json_object_to_json_string(jobj));

}

void jsonNombrarDipositivosSolicitud(char *solicitudNombrar, char *nombre, char *nodo) {

  json_object * jobj = json_object_new_object();

  json_object *jsonSoli = json_object_new_string(solicitudNombrar);
  json_object *jsonNombre = json_object_new_string(nombre);
  json_object *jsonNodo = json_object_new_string(nodo);

  json_object_object_add(jobj,"Solicitud", jsonSoli);
  json_object_object_add(jobj,"Nombre", jsonNombre);
  json_object_object_add(jobj,"Nodo", jsonNodo);

  /*Now printing the json object*/
  printf ("The json object created: %s \n",json_object_to_json_string(jobj));

}

void jsonLeerArchivoSolicitud(char *solicitudLeer, char *nombre, char * nombreArchivo) {
  
  json_object * jobj = json_object_new_object();

  json_object *jsonSoli = json_object_new_string(solicitudLeer);
  json_object *jsonNombre = json_object_new_string(nombre);
  json_object *jsonNombreArchivo = json_object_new_string(nombreArchivo);

  json_object_object_add(jobj,"solicitud", jsonSoli);
  json_object_object_add(jobj,"nombre", jsonNombre);
  json_object_object_add(jobj,"nombre_del_archivo", jsonNombreArchivo);

  /*Now printing the json object*/
  printf ("The json object created: %s \n",json_object_to_json_string(jobj));

}

void jsonLeerArchivoRespuesta(char *solicitudLeer, char *nombre, char * nombreArchivo, char * contenido, char * stErr) {
  
  json_object * jobj = json_object_new_object();

  json_object *jsonSoli = json_object_new_string(solicitudLeer);
  json_object *jsonNombre = json_object_new_string(nombre);
  json_object *jsonNombreArchivo = json_object_new_string(nombreArchivo);
  json_object *jsonContenido = json_object_new_string(contenido);
  json_object *jsonError = json_object_new_string(stErr);

  json_object_object_add(jobj,"solicitud", jsonSoli);
  json_object_object_add(jobj,"nombre", jsonNombre);
  json_object_object_add(jobj,"nombre_del_archivo", jsonNombreArchivo);
  json_object_object_add(jobj,"contenido", jsonContenido);
  json_object_object_add(jobj,"error", jsonError);

  /*Now printing the json object*/
  printf ("The json object created: %s \n",json_object_to_json_string(jobj));

}

void jsonEscribirArchivoSolicitud(char *solicitudEscribir, char *nombre, char * nombreArchivo, int tmCont, char * contenido) {
  
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
  printf ("%s \n",json_object_to_json_string(jobj));

}