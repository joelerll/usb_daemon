//Variable global
char json[50000];

void toJson();
char *getTipoSolicitud(char *jsonSolicitud);
char *getValuePorCampo(char *JSON, int nCampo);
char *jsonNombrarDipositivosRespuesta(char *solicitudNombrar,int status, char *nombre, char *nodo, char *stErr);