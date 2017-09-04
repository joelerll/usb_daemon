
struct InfoUSB{
    char *usbDirMount;
    char *usbNodo;
    char *idVendor;
    char *idProduct;
    char *nombre;
    int estado;
}InfoUSB;

struct InfoUSB *crearInfoUsb(char *usbDirMount, char *usbNodo, char *idVendor, char *idProduct);
void listarDispositivos(int client_socket);
void nombrarDispositivo(int client_socket, char *JSONSolicitud);
void leerArchivo(int client_socket, char *JSONSolicitud);
void escribiArchivo(int client_socket, char *JSONSolicitud);