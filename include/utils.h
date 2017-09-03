char *prueba();

// typedef enum {leer_archivo, escribir_archivo, nombrar_dispositivo} SOLICITUD; //solicitud solicitud = IMMEDIATE;
//
// typedef struct Dispositivo {
//  char *nombre;
//  char *vendor_device;
//  char *montaje;
//  char *nodo;
// }dispositivo;
//
// typedef struct ListarDispositivos {
//   SOLICITUD solicitud = leer_archivo;
//
// }listarDispositivos;


// usb (daemon)
/*
*  Lista todos los dispotivos usb
*
*  @name ListarDispositivosUsb - listar los dispositivos usb
*  @param { void }
*  @return {Array Dispositivo} dispositivos - Array de estructuras  dispositivo
*  @error {Array} - Array vacio (socket)
*/
// casos de fallo?


/*
*  Nombrar dispositivo usb
*
*  @name NombrarDispositivo dar un nombre a un usb
*  @param { char* } nuevo_nombre - nuevo nombre del dispositivo
*  @param { char* } nodo_dispositivo - npdo del dispositivo usb
*  @return { char* } estado - retornar char* EXITO (socket)
*  @error { char * } estado - retornar char* ERROR, mensaje error (socket)
*/
// casos de fallo?: nombre no valido, id dispositivo no existe


/*
*  Leer un archivo en usb
*
*  @name LeerArchivo - leer un archivo del usb
*  @param { char* } nombre_archivo - Nombre del archivo
*  @param { char* } nombre_dispositivo - Nombre del dispositivo a leer el archivo
*  @return { char* } contenido - contenido del dispositivo (socket)
*  @error { char* } ERROR, mensaje de error (socket)
*/
// casos fallo?: al leer el archivo, no existe el archivo, no permisos leer archivo, si no ha nombrado el dispositivo


/*
*  Escribir en archivo de usb
*
*  @name EscribirArchivo - Escribir en un archivo del usb
*  @param { char* } nombre_dispositivo - Nombre del dispositivo
*  @param { char* } nombre_archivo - Nombre del archivo
*  @param { int* } tamano_contenido
*  @param { char* } contenido - contenido que se desea guardar
*  @return { char* } EXITO - (socket)
*  @error { char* } ERROR, mensaje de error (socket)
*/
// casos fallo?: nombre mal, nombre archivo mal, tamano contenido diferente al contenido


// client => http_processing => json => socket_helper => daemon
// daemon => socket_helper => json => http_processing => client

// json
/*
*  JSON Listar todos los dispotivos usb
   NO lo necesito, solo es peticion get, lo paso directamente a socket_helper
   por el endpoint puedo saber que hacer
*  JSON Nombrar dispositivo usb
*
*  @name NombrarDispositivoJSON dar un nombre a un usb
*  @param { char* } nuevo_nombre - nuevo nombre del dispositivo
*  @param { char* } nodo_dispositivo - npdo del dispositivo usb
*  @return { char* } estado - retornar char* EXITO (socket)
*  @error { char * } estado - retornar char* ERROR, mensaje error (socket)
*/
// casos de fallo?: nombre no valido, id dispositivo no existe


// server
