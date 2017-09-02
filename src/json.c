// Una funcion validara los json de entrada
#include <stdio.h>
// Una funcion enviara a la salida los json
#include "utils.h"
char *prueba(char * nombrar_dispositivo_json) {
  printf("pruebaaaa %s\n", nombrar_dispositivo_json);
  char * respuesta = "{\"solicitud\": \"nombrar_dispositivo\",\"nombre\": \"mi_n\",\"nodo\": \"/dev/nodos\", \"status\": 1,\"str_error\": \"\"}";
  return respuesta;
}
