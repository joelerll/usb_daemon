

void *runUsbServer();
void analizarSolicitud(int client_socket, char *JSONSolicitud);
void doHilo();
void listarDispositivos(int client_socket);
void nombrarDispositivo(int client_socket, char *JSONSolicitud);
void leerArchivo(int client_socket, char *JSONSolicitud);
void escribiArchivo(int client_socket, char *JSONSolicitud);
void *enumerarDispositivos();
void doHiloActDispositivos();
