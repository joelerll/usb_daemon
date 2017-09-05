//Variable global
char json[50000];

void toJson();
char *getTipoSolicitud(char *jsonSolicitud);
char *getValuePorCampo(char *JSON, int nCampo);
char *jsonNombrarDipositivosRespuesta(char *solicitudNombrar,int status, char *nombre, char *nodo, char *stErr);
char *jsonEscribirRespuesta(char *solicitudEscribir, char *nombre, char * nombreArchivo, int status, char * stErr);
int getIntPorCampo(char *JSON, int nCampo);
char *jsonLeerArchivoRespuesta(char *solicitudLeer, char *nombre, char * nombreArchivo, char * contenido, int status, char * stErr);